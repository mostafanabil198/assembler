#include "Instructions.h"

Instructions::Instructions()
{
    label = "";
    operation= "";
    operand= "";
    error= "";
    op= "";
    adress = 0;
}

int Instructions::getAdress(){
    return adress;
}

string Instructions::getError(){
    return error;
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

string Instructions::getOP(){
    return error;
}

bool Instructions::getBase(){
    return base;
}

void Instructions::setBase(bool base){
    this->base = base;
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

void Instructions::setOperand(string operand){
    this->operand = operand;
}

void Instructions::setOp(string op){
    this->op = op;
}

void Instructions::setLabel(string label){
    this->label = label;
}
