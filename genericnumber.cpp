#include "genericnumber.h"
#include "numbers/spanset.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <cassert>

const GenericNumber GenericNumber::unknown = GenericNumber();

GenericNumber::GenericNumber()
    : type(UNKNOWN) {}

GenericNumber::GenericNumber(const GenericNumber &other)
    : type(other.getType()), num(other.num){}

GenericNumber::GenericNumber(GenericNumber &&other)
    : type(other.getType()), num(std::move(other.num)){}

GenericNumber::GenericNumber(const double &num)
    : num(num), type(NUMBER) {}

GenericNumber::GenericNumber(const Vector &num)
    : num(num), type(VECTOR) {}

GenericNumber::GenericNumber(const Matrix &num)
    : num(num), type(MATRIX) {}

GenericNumber::GenericNumber(const std::string &num)
    : num(num), type(LABEL) {}

GenericNumber::GenericNumber(const SpanSet &num)
    : num(num), type(SPAN_SET) {}

GenericNumber::GenericNumber(double &&num)
    : num(std::move(num)), type(NUMBER) {}

GenericNumber::GenericNumber(Vector &&num)
    : num(std::move(num)), type(VECTOR) {}

GenericNumber::GenericNumber(Matrix &&num)
    : num(std::move(num)), type(MATRIX) {}

GenericNumber::GenericNumber(std::string &&num)
    : num(std::move(num)), type(LABEL) {}

GenericNumber::GenericNumber(SpanSet &&num)
    : num(std::move(num)), type(SPAN_SET) {}

std::vector<double> getArray(QJsonArray &&array){
    std::vector<double> arr(array.size());
    for (int i = 0; i < array.size(); i++) arr[i] = array[i].toDouble();
    return arr;
}

QJsonArray getArray(const Vector &vector){
    QJsonArray arr;
    for (const double &d : vector) arr.push_back(d);
    return arr;
}

QJsonArray get2DArray(const Matrix &mat){
    QJsonArray arr;
    for (const Vector &v : mat) arr.push_back(getArray(v));
    return arr;
}

GenericNumber::GenericNumber(const QJsonObject &cache){
    QString type = cache["type"].toString();
    switch (type[0].toLatin1()){
    case 'N':
        this->type = NUMBER;
        this->num = cache["number"].toDouble();
        break;
    case 'V':
        this->type = VECTOR;
        this->num =  Vector(getArray(cache["vec"].toArray()));
        break;
    case 'M':
        this->type = MATRIX;
        {
            Matrix mat(cache["height"].toInt(), cache["width"].toInt());
            QJsonArray arr = cache["mat"].toArray();
            for (int i = 0; i < mat.getHeight(); i++) mat[i] = getArray(arr[i].toArray());
            this->num = mat;
        }
        break;
    case 'S':
        this->type = SPAN_SET;
        {
            Matrix mat(cache["height"].toInt(), cache["width"].toInt());
            QJsonArray arr = cache["mat"].toArray();
            for (int i = 0; i < mat.getHeight(); i++) mat[i] = getArray(arr[i].toArray());
            this->num = SpanSet(std::move(mat));
        }
        break;
    case 'L':
        this->type = LABEL;
        this->num = cache["label"].toString().toStdString();
        break;
    case 'E':
        this->type = EMPTY;
        break;
    default:
        throw std::invalid_argument("Unknown Number Type:" + type.toStdString());
    }
}

QJsonObject GenericNumber::toJson() const{
    switch (this->type){

    case NUMBER:
        return { { "type", "N" }, { "number", this->getDouble() } };
    case VECTOR:
        return { { "type", "V" }, { "vec", getArray(this->getVector())} };
    case MATRIX:
        return
        {
            { "type", "M" },
            { "height", getMatrix().getHeight()},
            { "width", getMatrix().getWidth()},
            { "mat", get2DArray(getMatrix()) }
        };
    case SPAN_SET:
        return
        {
            { "type", "S" },
            { "height", getMatrix().getHeight()},
            { "width", getMatrix().getWidth()},
            { "mat", get2DArray(getMatrix()) }
        };
    case LABEL:
        return { { "type", "L" }, { "label", this->getLabel().c_str() } };
    case UNKNOWN:
    case EMPTY:
        return { { "type", "E" } };
        break;
    }
}

NumberType GenericNumber::getType() const {
    return this->type;
}

const double &GenericNumber::getDouble() const {
    assert(this->type == NUMBER);
    return std::get<double>(num);
}

const Vector &GenericNumber::getVector() const {
    assert(this->type == VECTOR);
    return std::get<Vector>(num);
}

const Matrix &GenericNumber::getMatrix() const {
    if (this->type == SPAN_SET) return getSpanSet().asMatrix();
    assert(this->type == MATRIX);
    return std::get<Matrix>(num);
}

const std::string &GenericNumber::getLabel() const {
    assert(this->type == LABEL);
    return std::get<std::string>(num);
}

const SpanSet &GenericNumber::getSpanSet() const {
    assert(this->type == SPAN_SET);
    return std::get<SpanSet>(num);
}

const GenericNumber &GenericNumber::operator=(const GenericNumber &src){
    this->type = src.getType();
    this->num = src.num;
    return *this;
}

bool GenericNumber::hasValue() const{
    return this->type != EMPTY && this->type != UNKNOWN;
}
