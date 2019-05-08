#include "Instructions.h"

Instructions::Instructions()
{
    label = "";
    operation= "";
    operand= "";
    error= "";
    objectCode = "";
    adress = 0;
}

int Instructions::getAdress(){
    return adress;
}

string Instructions::getError(){
    return error;
}
string Instructions::getError2(){
    return error2;
}

string Instructions::getLabel(){
    return label;
}

string Instructions::getOperand(){
    return operand;
}

string Instructions::getOperation(){
    return operation;
}

string Instructions::getObjectCode(){
    return objectCode;
}

bool Instructions::getBase(){
    return base;
}

void Instructions::setBase(bool base){
    this->base = base;
}

string Instructions::getBaseL(){
    return baseL;
}

void Instructions::setBaseL(string baseL){
    this->baseL = baseL;
}


void Instructions::setAdress(int adress){
    this->adress = adress;
}

void Instructions::setOperation(string operation){
    this->operation = operation;
}

void Instructions::setError(string error){
    this->error = error;
}
void Instructions::setError2(string error){
    this->error2 = error;
}

void Instructions::setOperand(string operand){
    this->operand = operand;
}

void Instructions::setObjectCode(string opeeee){
    this->objectCode = opeeee;
}

void Instructions::setLabel(string label){
    this->label = label;
}

void Instructions::setNixbpe(string nixbpe){
    this->nixbpe = nixbpe;
}
string Instructions::getNixbpe(){
        return nixbpe;
}

