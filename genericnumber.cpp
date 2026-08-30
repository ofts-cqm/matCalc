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

GenericNumber::GenericNumber(GenericNumber &&other) noexcept
    : type(other.getType()), num(std::move(other.num)){}

GenericNumber::GenericNumber(const double &num)
    : type(NUMBER), num(num) {}

GenericNumber::GenericNumber(const Vector &num)
    : type(VECTOR), num(num) {}

GenericNumber::GenericNumber(const Matrix &num)
    : type(MATRIX), num(num) {}

GenericNumber::GenericNumber(const std::string &num)
    : type(LABEL), num(num) {}

GenericNumber::GenericNumber(const SpanSet &num)
    : type(SPAN_SET), num(num) {}

GenericNumber::GenericNumber(const EigenSpace &num)
    : type(EIGEN), num(num) {}

GenericNumber::GenericNumber(double &&num)
    : type(NUMBER), num(std::move(num)) {}

GenericNumber::GenericNumber(Vector &&num)
    : type(VECTOR), num(std::move(num)) {}

GenericNumber::GenericNumber(Matrix &&num)
    : type(MATRIX), num(std::move(num)) {}

GenericNumber::GenericNumber(std::string &&num)
    : type(LABEL), num(std::move(num)) {}

GenericNumber::GenericNumber(SpanSet &&num)
    : type(SPAN_SET), num(std::move(num)) {}

GenericNumber::GenericNumber(EigenSpace &&num)
    : type(EIGEN), num(std::move(num)) {}

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
    if (type.isEmpty()) throw std::invalid_argument("Missing number type");
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
            const int height = cache["height"].toInt(-1);
            const int width = cache["width"].toInt(-1);
            if (height < 0 || width < 0) throw std::invalid_argument("Invalid matrix dimensions");
            Matrix mat(height, width);
            QJsonArray arr = cache["mat"].toArray();
            if (arr.size() != height) throw std::invalid_argument("Invalid matrix row count");
            for (int i = 0; i < height; i++) {
                QJsonArray row = arr[i].toArray();
                if (row.size() != width) throw std::invalid_argument("Invalid matrix column count");
                mat[i] = getArray(std::move(row));
            }
            this->num = mat;
        }
        break;
    case 'S':
        this->type = SPAN_SET;
        {
            const int height = cache["height"].toInt(-1);
            const int width = cache["width"].toInt(-1);
            if (height < 0 || width < 0) throw std::invalid_argument("Invalid span-set dimensions");
            Matrix mat(height, width);
            QJsonArray arr = cache["mat"].toArray();
            if (arr.size() != height) throw std::invalid_argument("Invalid span-set row count");
            for (int i = 0; i < height; i++) {
                QJsonArray row = arr[i].toArray();
                if (row.size() != width) throw std::invalid_argument("Invalid span-set column count");
                mat[i] = getArray(std::move(row));
            }
            this->num = SpanSet(std::move(mat));
        }
        break;
    case 'I':
        this->type = EIGEN;
        {
            QJsonArray arr = cache["values"].toArray();
            std::vector<double> eigenValues(arr.size());
            for (int i = 0; i < arr.size(); i++) eigenValues[i] = arr[i].toDouble();
            // no need to restore eigen vectors because they are not displayed, and will be recalculated when restoring
            this->num = EigenSpace{eigenValues, std::vector<SpanSet>(arr.size(), SpanSet()), static_cast<int>(eigenValues.size()) };
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
    case EIGEN:
        return{
            { "type", "I" },
            { "values", getArray(this->getEigen().eigenValues) }
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

const EigenSpace &GenericNumber::getEigen() const {
    assert(this->type == EIGEN);
    return std::get<EigenSpace>(num);
}

const GenericNumber &GenericNumber::operator=(const GenericNumber &src){
    this->type = src.getType();
    this->num = src.num;
    return *this;
}

bool GenericNumber::hasValue() const{
    return this->type != EMPTY && this->type != UNKNOWN;
}
