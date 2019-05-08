#include <iostream>
#include <bits/stdc++.h>
#include <Singleton.h>
#include <string>
using namespace std;
/**
 * Singleton instance.
 */
Singleton *Singleton::instance = 0;

/**
 * Constructs directive table.
 */
Singleton::Singleton()
{
    initTables();

}

/**
 * Gets the singleton instance of directive table.
 * @return [instance to directive table].
 */
Singleton *Singleton::getInstance()
{
    if (instance == 0)
        instance = new Singleton();
    return instance;
}


void Singleton::initTables()
{

    endb = false;
    error = false;
    error2 = false;

    //DIRECTIVES
    dirTable["start"]= "";
    dirTable["byte"]= "";
    dirTable["word"]= "";
    dirTable["resb"]= "";
    dirTable["resw"]= "";
    dirTable["equ"]= "";
    dirTable["end"]= "";
    dirTable["org"]= "";
    dirTable["ltorg"]= "";
    dirTable["use"]= "";
    dirTable["base"]= "";
    dirTable["nobase"]= "";

    operationsWithLiterals["lda"] = 3;
    operationsWithLiterals["ldch"] = 1;
    operationsWithLiterals["td"] = 1;
    operationsWithLiterals["rd"] = 1;
    operationsWithLiterals["comp"] = 3;
    operationsWithLiterals["add"] = 3;
    operationsWithLiterals["sub"] = 3;
    operationsWithLiterals["wd"] = 1;
    operationsWithLiterals["mul"] = 3;
    operationsWithLiterals["div"] = 3;
    operationsWithLiterals["byte"] = 0;
    operationsWithLiterals["lds"] = 3;
    operationsWithLiterals["ldt"] = 3;
    operationsWithLiterals["ldx"] = 3;
    operationsWithLiterals["+lda"] = 3;
    operationsWithLiterals["+ldch"] = 1;
    operationsWithLiterals["+td"]= 1;
    operationsWithLiterals["+rd"] = 1;
    operationsWithLiterals["+comp"] = 3;
    operationsWithLiterals["+add"] = 3;
    operationsWithLiterals["+sub"] = 3;
    operationsWithLiterals["+wd"] = 1;
    operationsWithLiterals["+mul"] = 3;
    operationsWithLiterals["+div"] = 3;
    operationsWithLiterals["+lds"] = 3;
    operationsWithLiterals["+ldt"] = 3;
    operationsWithLiterals["+ldx"] = 3;





    operations["add"]= make_pair(3,"18");
    operations["+add"]=make_pair(3,"18");
    operations["addr"]=make_pair(2,"90");
    operations["addf"]=make_pair(3,"58");
    operations["+addf"]=make_pair(4,"58");
    operations["and"]=make_pair(3,"40");
    operations["+and"]=make_pair(4,"40");
    operations["clear"]=make_pair(2,"b4");
    operations["comp"]=make_pair(3,"28");
    operations["+comp"]=make_pair(4,"28");
    operations["compf"]=make_pair(3,"88");
    operations["+compf"]=make_pair(4,"88");
    operations["compr"]=make_pair(2,"a0");
    operations["div"]=make_pair(3,"24");
    operations["+div"]=make_pair(4,"24");
    operations["divf"]=make_pair(3,"64");
    operations["+divf"]=make_pair(4,"64");
    operations["divr"]=make_pair(2,"9c");
    operations["fix"]=make_pair(1,"c0");
    operations["float"]=make_pair(1,"c4");
    operations["hio"]=make_pair(1,"f4");
    operations["j"]=make_pair(3,"3c");
    operations["+j"]=make_pair(4,"3c");
    operations["jeq"]=make_pair(3,"30");
    operations["+jeq"]=make_pair(4,"30");
    operations["jgt"]=make_pair(3,"34");
    operations["+jgt"]=make_pair(4,"34");
    operations["jlt"]=make_pair(3,"38");
    operations["+jlt"]=make_pair(4,"38");
    operations["jsub"]=make_pair(3,"48");
    operations["+jsub"]=make_pair(4,"48");
    operations["lda"]=make_pair(3,"00");
    operations["+lda"]=make_pair(4,"00");
    operations["ldb"]=make_pair(3,"68");
    operations["+ldb"]=make_pair(4,"68");
    operations["ldch"]=make_pair(3,"50");
    operations["+ldch"]=make_pair(4,"50");
    operations["ldf"]=make_pair(3,"70");
    operations["+ldf"]=make_pair(4,"70");
    operations["ldl"]=make_pair(3,"08");
    operations["+ldl"]=make_pair(4,"08");
    operations["lds"]=make_pair(3,"6c");
    operations["+lds"]=make_pair(4,"6c");
    operations["ldt"]=make_pair(3,"74");
    operations["+ldt"]=make_pair(4,"74");
    operations["ldx"]=make_pair(3,"04");
    operations["+ldx"]=make_pair(4,"04");
    operations["lps"]=make_pair(3,"d0");
    operations["+lps"]=make_pair(4,"d0");
    operations["mul"]=make_pair(3,"20");
    operations["+mul"]=make_pair(4,"20");
    operations["mulf"]=make_pair(3,"60");
    operations["+mulf"]=make_pair(4,"60");
    operations["mulr"]=make_pair(2,"98");
    operations["or"]=make_pair(3,"44");
    operations["+or"]=make_pair(4,"44");
    operations["rd"]=make_pair(3,"d8");
    operations["+rd"]=make_pair(4,"d8");
    operations["norm"]=make_pair(1,"c8");
    operations["rmo"]=make_pair(2,"ac");
    operations["rsub"]=make_pair(3,"4c");
    operations["+rsub"]=make_pair(4,"4c");
    operations["shiftl"]=make_pair(2,"a4");
    operations["shiftr"]=make_pair(2,"a8");
    operations["sio"]=make_pair(1,"f0");
    operations["ssk"]=make_pair(3,"ec");
    operations["+ssk"]=make_pair(4,"ec");
    operations["sta"]=make_pair(3,"0c");
    operations["+sta"]=make_pair(4,"0c");
    operations["stb"]=make_pair(3,"78");
    operations["+stb"]=make_pair(4,"78");
    operations["stch"]=make_pair(3,"54");
    operations["+stch"]=make_pair(4,"54");
    operations["stf"]=make_pair(3,"80");
    operations["+stf"]=make_pair(4,"80");
    operations["sti"]=make_pair(3,"d4");
    operations["+sti"]=make_pair(4,"d4");
    operations["stl"]=make_pair(3,"14");
    operations["+stl"]=make_pair(4,"14");
    operations["sts"]=make_pair(3,"7c");
    operations["+sts"]=make_pair(4,"7c");
    operations["stsw"]=make_pair(3,"e8");
    operations["+stsw"]=make_pair(4,"e8");
    operations["stt"]=make_pair(3,"84");
    operations["+stt"]=make_pair(4,"84");
    operations["stx"]=make_pair(3,"10");
    operations["+stx"]=make_pair(4,"10");
    operations["sub"]=make_pair(3,"1c");
    operations["+sub"]=make_pair(4,"1c");
    operations["subf"]=make_pair(3,"5c");
    operations["+subf"]=make_pair(4,"5c");
    operations["td"]=make_pair(3,"e0");
    operations["+td"]=make_pair(4,"e0");
    operations["tix"]=make_pair(3,"2c");
    operations["+tix"]=make_pair(4,"2c");
    operations["wd"]=make_pair(3,"dc");
    operations["+wd"]=make_pair(4,"dc");
    operations["subr"]=make_pair(2,"94");
    operations["svc"]=make_pair(2,"b0");
    operations["tio"]=make_pair(1,"f8");
    operations["tixr"]=make_pair(2,"b8");

    //ASCII CODEEEEEEEEEEEEEEEEEEEEEEEEEES
    asciiTable['0'] = "30";
    asciiTable['1'] = "31";
    asciiTable['2'] = "32";
    asciiTable['3'] = "33";
    asciiTable['4'] = "34";
    asciiTable['5'] = "35";
    asciiTable['6'] = "36";
    asciiTable['7'] = "37";
    asciiTable['8'] = "38";
    asciiTable['9'] = "39";

    asciiTable['A'] = "41";
    asciiTable['B'] = "42";
    asciiTable['C'] = "43";
    asciiTable['D'] = "44";
    asciiTable['E'] = "45";
    asciiTable['F'] = "46";
    asciiTable['G'] = "47";
    asciiTable['H'] = "48";
    asciiTable['I'] = "49";
    asciiTable['J'] = "4A";
    asciiTable['K'] = "4B";
    asciiTable['L'] = "4C";
    asciiTable['M'] = "4D";
    asciiTable['N'] = "4E";
    asciiTable['O'] = "4F";
    asciiTable['P'] = "50";
    asciiTable['Q'] = "51";
    asciiTable['R'] = "52";
    asciiTable['S'] = "53";
    asciiTable['T'] = "54";
    asciiTable['U'] = "55";
    asciiTable['V'] = "56";
    asciiTable['W'] = "57";
    asciiTable['X'] = "58";
    asciiTable['Y'] = "59";
    asciiTable['Z'] = "5A";

    asciiTable['a'] = "61";
    asciiTable['b'] = "62";
    asciiTable['c'] = "63";
    asciiTable['d'] = "64";
    asciiTable['e'] = "65";
    asciiTable['f'] = "66";
    asciiTable['g'] = "67";
    asciiTable['h'] = "68";
    asciiTable['i'] = "69";
    asciiTable['j'] = "6A";
    asciiTable['k'] = "6B";
    asciiTable['l'] = "6C";
    asciiTable['m'] = "6D";
    asciiTable['n'] = "6E";
    asciiTable['o'] = "6F";
    asciiTable['p'] = "70";
    asciiTable['q'] = "71";
    asciiTable['r'] = "72";
    asciiTable['s'] = "73";
    asciiTable['t'] = "74";
    asciiTable['u'] = "75";
    asciiTable['v'] = "76";
    asciiTable['w'] = "77";
    asciiTable['x'] = "78";
    asciiTable['y'] = "79";
    asciiTable['z'] = "7A";

    regesters["a"] = 0 ;
    regesters["x"] = 1 ;
    regesters["l"] = 2 ;
    regesters["b"] = 3 ;
    regesters["s"] = 4 ;
    regesters["t"] = 5 ;
    regesters["f"] = 6 ;
    regesters["pc"] = 8 ;
    regesters["sw"] = 9 ;


}



unordered_map<string,pair<int,string>> Singleton::getOperations()
{

    return operations;
}

bool Singleton::symbol_table_contains(string label)
{
    return symbol_table.find(label) == symbol_table.end();
}


int Singleton::literalOperationsSize(string operation){
    if(operationsWithLiterals.find(operation) == operationsWithLiterals.end()){
        return -1;
    }
    return operationsWithLiterals[operation];

}

string Singleton::convertToAscii(string s){
    string ascii;
    for(int i = 0; i < s.size(); i++){
            ascii += asciiTable[s[i]];
        }
    return ascii;
}

void Singleton::covertLiteralsToHexa(string literal){
    Instructions instruction;
    string data = literal.substr(3, literal.size()-4) ;
    string hexa = "";
    if(literal[1] == 'c'){
        for(int i = 0; i < data.size(); i++){
            hexa += asciiTable[data[i]];
        }
        instruction.setAdress(data.size());
    } else {
        hexa = data;
        instruction.setAdress(data.size()/2);
    }
    if(literals1.find(hexa) == literals1.end()){
        instruction.setLabel(hexa);
        instruction.setOperation("LITERAL");
        instruction.setOperand("***");
        addLiteral(instruction);
        literals1[hexa] = make_pair(literal,instruction.getAdress());
    }
    //std::stringstream sss;
    //sss << "  " << literal << "  " << literals1[literal];
    //cout << sss.str() << endl;
}

int Singleton::getLiteralAddress(string literal){

    return literals1[getLiteralsToHexa(literal)].second;
}

void Singleton::setLiteralAddress(string hexa, int address){
    literals1[hexa].second = address;
}


string Singleton::getLiteralsToHexa(string literal){
    string data = literal.substr(3, literal.size()-4) ;
    string hexa = "";
    if(literal[1] == 'c'){
        for(int i = 0; i < data.size(); i++){
            hexa += asciiTable[data[i]];
        }
    } else {
        hexa = data;
    }
    return hexa;
}



bool Singleton::getError2(){
    return error2;
}
void Singleton::setError2(bool error2){
    this->error2 = error2;
}
bool Singleton::get_end(){
    return endb;
}

void Singleton::set_end(bool endbool){
    endb = endbool;
}

bool Singleton::get_error(){
    return error;
}
    void Singleton::set_error(bool errorb){
        error = errorb;
    }


bool Singleton::dirTable_contains(string dir)
{
    return dirTable.find(dir) == dirTable.end();
}

int Singleton::operationFormat(string operation){
    if(operations.find(operation) == operations.end()){
        return -1;
    } else {
        return operations[operation].first;
    }
}

string Singleton::getOpCode(string operation){
        return operations[operation].second;
}


void Singleton::symbol_table_add(string label, int value, string type)
{
    symbol_table[label]=make_pair(value,type);
}

string Singleton::asciiTable_getValue(char letter)
{
    return asciiTable[letter];
}




int Singleton::symbol_table_get(string label)
{
    return symbol_table[label].first;
}

unordered_map<string,pair<int,string>> Singleton::get_symbol_table(){
    return symbol_table;
}



void Singleton::addLiteral(Instructions i)
{
    deque<Instructions>::iterator itr;
    bool found = false;
    for(itr=literals.begin(); itr!=literals.end(); ++itr)
    {
        string x=itr->getLabel();
        if(x==i.getLabel())
        {
            found=true;
        }
    }
    if(!found)
    {
        literals.push_back(i);
    }
}
bool Singleton::isLiteralEmpty()
{
    return literals.empty();
}


    void Singleton::setHeaderRecord(string record){
        this->headerRecord = record;
    }
    void Singleton::setEndRecord(string record){
        this->endRecord = record;
    }
    string Singleton::getHeaderRecord(){
        return headerRecord;
    }
    string Singleton::getEndRecord(){
        return endRecord;
    }

Instructions Singleton::getLiteral()
{
    Instructions i = literals.front();
    literals.pop_front();
    return i;
}

string Singleton::symbol_table_get_type(string symbol){
    return symbol_table[symbol].second;
}


void Singleton::addInstruction(Instructions i)
{
    allInstructions.push_back(i);
}

void Singleton::setAllInstructions(vector<Instructions> instructions){
    this->allInstructions = instructions;

}

Instructions Singleton::getInstruction(int i)
{
    return allInstructions[i];
}

vector<Instructions> Singleton::getAllInstructions(){
    return allInstructions;
}


int Singleton::getRegesterCode(string regester){
    return regesters[regester];
}

vector<pair<string,string>> Singleton::getTextRecords(){
    return textRecords;
}
void Singleton::addTRecord(string ad, string objectCodes){
    textRecords.push_back(make_pair(ad,objectCodes));
}


/**
 * Checks if directive table contains a certain directive (case insensitive).
 * @param  directive [Directive to be checked for the bottom of its existence in this futile universe.]
 * @return           [True if directive table contains this directive.]
 */

