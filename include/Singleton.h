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
    void setAllInstructions(vector<Instructions> instructions);
    bool dirTable_contains(string dir);
    int literalOperationsSize(string operation);
    void covertLiteralsToHexa(string literal);
    void set_end(bool endbool);
    bool get_end();
    bool get_error();
    void set_error(bool errorb);
    unordered_map<string,pair<int,string>> get_symbol_table();
    int operationFormat(string operation);
    string getOpCode(string operation);
    int getRegesterCode(string regester);
    void setHeaderRecord(string record);
    void setEndRecord(string record);
    string getHeaderRecord();
    string getEndRecord();
    vector<pair<string,string>> getTextRecords();
    void addTRecord(string ad, string objectCodes);




private:
Singleton();
    string toUpper(string*);
    static Singleton *instance;
    unordered_map<string,string> dirTable;
    unordered_map<string,int> operationsWithLiterals;
    unordered_map<string,pair<int,string>> operations;
    unordered_map<string,pair<int,string>> symbol_table;
    unordered_map<char,string> asciiTable;
    unordered_map<string,int> regesters;
    deque<Instructions> literals;
    vector<Instructions> allInstructions;
    string headerRecord;
    string endRecord;
    bool error;
    bool endb;
    vector<pair<string,string>> textRecords;



    void initTables();
};

#endif
