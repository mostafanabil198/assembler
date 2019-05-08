#ifndef FILES_H
#define FILES_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Instructions.h>
#include <Parser.h>
#include <Singleton.h>
#include <Validate.h>
using namespace std;

class Files
{
    public:
        Files();
        void readFromFile(string fileName);
        vector<string> print(vector<Instructions> given, bool pass1);
    protected:

    private:
        Parser parse;
        Validate validator;
        Singleton* tables;


};

#endif // FILES_H
