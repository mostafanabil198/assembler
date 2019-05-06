#ifndef SINGLETON_H
#define SINGLETON_H
#include <iostream>
#include <Instructions.h>

using namespace std;

class Singleton {

  public:

    static Singleton *getInstance();
    bool contains(std::string symbol);
    void addSymbol();
    unordered_map<string,pair<int,string>> getOperations();
    bool symbol_table_contains(string label);
    void symbol_table_add(string label, int value, string type);
    int symbol_table_get(string label);
    string asciiTable_getValue(char letter);

    void addLiteral(Instructions i);
    bool isLiteralEmpty();
    Instructions getLiteral();

    void addInstruction(Instructions i);
    Instructions getInstruction(int i);
    vector<Instructions> getAllInstructions();
    bool dirTable_contains(string dir);
    int literalOperationsSize(string operation);
    void covertLiteralsToHexa(string literal);
    void set_end(bool endbool);
    bool get_end();
    bool get_error();
    void set_error(bool errorb);
    unordered_map<string,pair<int,string>> get_symbol_table();
    int operationFormat(string operation);



private:
Singleton();
    string toUpper(string*);
    static Singleton *instance;
    unordered_map<string,string> dirTable;
    unordered_map<string,int> operationsWithLiterals;
    unordered_map<string,pair<int,string>> operations;
    unordered_map<string,pair<int,string>> symbol_table;
    unordered_map<char,string> asciiTable;
    deque<Instructions> literals;
    vector<Instructions> allInstructions;
    bool error;
    bool endb;




    void initTables();
};

#endif
