#ifndef ABSTRACTNUMBERPANE_H
#define ABSTRACTNUMBERPANE_H

template <typename T>
class AbstractNumberPane
{
public:
    AbstractNumberPane(T value){ this->value = value;}

    virtual void reconstructPage(){}

    virtual void display(T num){ this->value = num; }

    virtual const T& getValue(){ return this->value; }

protected:
    T value;
};

#endif // ABSTRACTNUMBERPANE_H
