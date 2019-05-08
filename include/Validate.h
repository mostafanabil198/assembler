#ifndef VALIDATE_H
#define VALIDATE_H
#include <Instructions.h>
#include <Singleton.h>
#include <ExpressionEvaluator.h>


class Validate
{
public:
    int add = 0;
    bool start = false;
    bool end = false;
    bool base = false;
    string baseLabel = "";
    int count = 0;
    unordered_map<string,pair<int,string>> format2;
    Validate();
    void table(Instructions i);




protected:

private:
    Singleton* tables;
    unordered_map<string,pair<int,string>> format;
    string hexaToInt(string hexa);
    string doulbe_operands = "([A-Za-z][A-Za-z0-9]*)((\\+|\\-|\\*|\\/)([0-9]+|[A-Za-z][A-Za-z0-9]*))+";
    ExpressionEvaluator evalutor;


};

#endif // VALIDATE_H
