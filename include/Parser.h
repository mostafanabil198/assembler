#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <Singleton.h>
#include <bits/stdc++.h>
#include <regex>
#include <Instructions.h>

using namespace std;

class Parser
{
    public:
        Parser();
        Instructions parse(string line);

    protected:

    private:
    // \s*(\.).*
        string comment = "\\s*(\\.).*";
        // \s*([A-Za-z0-9]+)\s+(\+?[A-Za-z0-9]+)\s+([^\s]+)\s*
        string label_with_operand = "\\s*([A-Za-z0-9]+)\\s+(\\+?[A-Za-z0-9]+)\\s+([^\\s]+)\\s*";
        // \s*(\+?[A-Za-z0-9]+)\s+([^\s]+)\s*
        string noLabel_with_operand = "\\s*(\\+?[A-Za-z0-9]+)\\s+([^\\s]+)\\s*";
        // \s*(([A-Za-z0-9]*)\s+)?(rsub|end)(\s+([A-Za-z0-9]*))?
        string rsub_end = "\\s*(([A-Za-z0-9]*)\\s+)?(rsub|end)(\\s+([A-Za-z0-9]*))?";
        //  \s*(([A-Za-z0-9]*)\s+)?(start)\s+([0-9a-fA-F]+)\s*
        string start = "\\s*(([A-Za-z0-9]*)\\s+)?(start)\\s+([0-9a-fA-F]+)\\s*";
        // [A-Za-z][A-Za-z0-9]*
        string label = "[A-Za-z][A-Za-z0-9]*";
        string labelInt = "[A-Za-z][A-Za-z0-9]*|[0-9]*|\s*";
        // ([#|@]?[A-Za-z][A-Za-z0-9]*)|([#|@]?[0-9]+)|([0-9]+)
        string single_operand =  "([#|@]?[A-Za-z][A-Za-z0-9]*)|([#|@]?[0-9]+)|([0-9]+)";
        // (([A-Za-z][A-Za-z0-9]*)|([0-9]+)|(#|@)?\*),x
        string indexed_addressing = "(([A-Za-z][A-Za-z0-9]*)|([0-9]+)|(#|@)?\\*),x";
        //  ([A-Za-z][A-Za-z0-9]*)((\+|-|\*|\/)([0-9]+|[A-Za-z][A-Za-z0-9]*))+
        string doulbe_operands = "([A-Za-z][A-Za-z0-9]*)((\\+|-|\\*|\\/)([0-9]+|[A-Za-z][A-Za-z0-9]*))+";
        // \s*(([A-Za-z0-9]+)\s+)?(shiftl|shiftr)\s+(([A-Za-z]),([0-9]+))\s*
        string shift = "\\s*(([A-Za-z0-9]+)\\s+)?(shiftl|shiftr)\\s+(([A-Za-z]),([0-9]+))\\s*";
        // \s*(([A-Za-z0-9]*)\s+)?(norm|sio|tio|fix|float|hio)\s*
        string format1 = "\\s*(([A-Za-z0-9]*)\\s+)?(norm|sio|tio|fix|float|hio)\\s*";
        // ([A-Za-z]),([A-Za-z])
        string format2_double_operands = "([A-Za-z][A-Za-z]?),([A-Za-z][A-Za-z]?)";
        // ([A-Za-z])
        string format2_single_operand = "([A-Za-z][A-Za-z]?)";
        // a|x|l|b|s|t|f
        string registers = "a|x|l|b|s|t|f|pc|sw";
        // (@|#)?([A-Za-z][A-Za-z0-9]*|[0-9]+)
        string equ_operand = "(@|#)?([A-Za-z][A-Za-z0-9]*|\\*|[0-9]+)";
        // (x'[a-f0-9]*')|(c'[^']*')
        string byte_operand = "=?(x'[a-f0-9]*')|=?(c'[^']*')";
        // =((c'[^']+')|(x'[a-f0-9]+'))
        string literals = "=((c'[^']+')|(x'[a-f0-9]+'))";

        bool checkLabel(string label);
        void checkOperand(string operand, Instructions& i);
        string hexaToInt(string hexa);
        Singleton* tables;



};

#endif // PARSER_H
