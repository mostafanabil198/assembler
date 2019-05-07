#ifndef OBJECTCODEHANDLER_H
#define OBJECTCODEHANDLER_H
#include "ObjectCodeHandler.h"
#include <bits/stdc++.h>
#include <iostream>
#include <Singleton.h>
#include <string>


using namespace std;


class ObjectCodeHandler
{
    public:
        ObjectCodeHandler();
        void generateObjectCode();
    protected:

    private:
    Singleton* tables;
    string hex_str_to_bin_str(const std::string& hex);
    const char* hex_char_to_bin(char c);
    const char* bin_char_to_hex(string c);
    string bin_str_to_hex_str(const std::string& bin);
    string toBinary(int n);
    string to_hexa(int ad);

};



#endif // OBJECTCODEHANDLER_H
