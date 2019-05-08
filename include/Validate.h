#ifndef VALIDATE_H
#define VALIDATE_H
#include <Instructions.h>
#include <Singleton.h>


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


};

#endif // VALIDATE_H
