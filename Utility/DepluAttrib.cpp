#include "DepluAttrib.h"
#include <memory>
#include <iostream>
#include <sstream>

DepluAttrib::DepluAttrib(QObject *parent) : QObject(parent){
}

void DepluAttrib::set(QString value)
{
    this->value = std::move("\'" + value + "\'");
}

void DepluAttrib::set(int value)
{
    this->value.setNum(value);
}

void DepluAttrib::set(long value)
{
    this->value.setNum(value);
}

void DepluAttrib::set(float value)
{
    this->value.setNum(value);
}

void DepluAttrib::set(double value)
{
    this->value.setNum(value);
}

void DepluAttrib::set(bool value)
{
    if(value){
        this->value = "true";
    }
    else{
        this->value = "false";
    }
}

void DepluAttrib::set(DepluValue value)
{
    if(value == DepluValue::Null){
        this->value = "null";
    }
    else{
        this->value = "_";
    }
}

bool DepluAttrib::isBool()
{
    if(this->value == "true" || this->value == "false"){
        return true;
    }
    return false;
}

bool DepluAttrib::isString()
{
    if(
        (this->value.at(0) == '\'' && this->value.at((this->value.size() - 1)) == '\'') ||
        (this->value.at(0) == '\"' && this->value.at((this->value.size() - 1)) == '\'')
    ){
       return true;
    }
    return false;
}

bool DepluAttrib::isFloat()
{
    std::istringstream iss(value.toStdString());
    float tmp;
    iss >> std::noskipws >> tmp; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool DepluAttrib::isDouble()
{
    std::istringstream iss(value.toStdString());
    double tmp;
    iss >> std::noskipws >> tmp; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool DepluAttrib::isInt()
{
    std::istringstream iss(value.toStdString());
    int tmp;
    iss >> std::noskipws >> tmp; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool DepluAttrib::isLong()
{
    std::istringstream iss(value.toStdString());
    long tmp;
    iss >> std::noskipws >> tmp; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool DepluAttrib::isNull()
{
    if(this->value == "null"){
        return true;
    }
    return false;
}

bool DepluAttrib::isEmpty()
{
    if(this->value == "_"){
        return true;
    }
    return false;
}

