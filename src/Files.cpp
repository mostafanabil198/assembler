#include "Files.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Instructions.h>
#include <ObjectCodeHandler.h>
using namespace std;

Files::Files()
{
    tables = Singleton::getInstance();
}

void Files::readFromFile(string fileName)
{
    //vector<string> file;
    ifstream inputFile (fileName);
    string line;
    if (inputFile.is_open())
    {
        while ( getline (inputFile,line) )
        {
            //cout << line + "\n";
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            Instructions instruction = parse.parse(line);
            //cout << instruction.getAdress() + " " + instruction.getLabel() + " " + instruction.getOperation() + " " + instruction.getOperand() + "\n" + instruction.getError() + "\n";
            validator.table(instruction);


        }
        inputFile.close();
        ObjectCodeHandler o;
        o.generateObjectCode();

    }
    else
    {
        cout << "Unable to open file";
    }
}
vector<string> Files::print(vector<Instructions> given, bool pass1)
{
    vector<string> answer;
    if(!pass1 && tables->get_error()){
        return answer;
    }
    string l= "Address ";

    if(!pass1){
        l.append("Obj code  ");
    }
    l.append("label  operation operand");
    answer.push_back(l);
    for(int i=0; i<given.size(); i++)
    {
        std::stringstream sstream;
        sstream << std::hex << given[i].getAdress();
        std::string address = sstream.str();
        string label=given[i].getLabel();
        string operation=given[i].getOperation();
        string operand=given[i].getOperand();
        string line;
        string objectCode = given[i].getObjectCode();
        string nixbbe = given[i].getNixbpe();
        string err2 = given[i].getError2();
        while(address.size()<6)
        {
            address.insert(0,"0");
        }
        line.append(address);
        string spaces;
        if(!pass1){
            if(!pass1 && err2 != ""){
                answer.push_back("----------" + err2 + "--------------");
            }
            answer.push_back(nixbbe);
            spaces = "  ";
            spaces.append(objectCode);
            while(spaces.size() < 11){
                spaces.append(" ");
            }
        line.append(spaces);
        }

        spaces=" ";
        spaces.append(label);
        while(spaces.size()<10)
        {
            spaces.append(" ");
        }
        line.append(spaces);
        spaces="";
        spaces.append(operation);
        while(spaces.size()<8)
        {
            spaces.append(" ");
        }
        line.append(spaces);
        line.append(operand);

        answer.push_back(line);
        string err=given[i].getError();
        if(err!="")
        {
            tables->set_error(true);
            answer.push_back("----------" + err + "--------------");
        }
        if(!pass1 && err2 != ""){
            answer.push_back("----------" + err2 + "--------------");
        }
        if(!pass1){
            answer.push_back("");
        }
        if(operation == "end")
        {
            while(!tables->isLiteralEmpty())
            {
                Instructions literal = tables->getLiteral();
                std::stringstream sstream1;
                sstream1 << std::hex << literal.getAdress();
                std::string address1 = sstream1.str();
                string label1=literal.getLabel();
                string operation1=literal.getOperation();
                string operand1=literal.getOperand();
                string line1;
                while(address1.size()<6)
                {
                    address1.insert(0,"0");
                }
                line1.append(address1);
                string spaces1=" ";
                spaces1.append(label1);
                while(spaces1.size()<10)
                {
                    spaces1.append(" ");
                }
                line1.append(spaces1);
                spaces1="";
                spaces1.append(operation1);
                while(spaces1.size()<8)
                {
                    spaces1.append(" ");
                }
                line1.append(spaces1);
                line1.append(operand1);
                answer.push_back(line1);

            }
        }
    }
    if(!tables->get_end())
    {
        answer.push_back("error!! end must be exist");
        tables->set_error(true);
    }

    if(!tables->get_error() && pass1){
        answer.push_back("\n\n\n");
    answer.push_back("------------------ SYMBOL TABLE ----------------------\n\n");

    unordered_map<string,pair<int,string>> symbol_table = tables->get_symbol_table();
    unordered_map<string,pair<int,string>>::iterator itr;
    for(itr=symbol_table.begin();itr!=symbol_table.end();++itr){
       string record = "             ";
       record += itr->first + "   ";
       stringstream ss;
        ss << itr->second.first;
       record += ss.str();
       record += "   ";
       record += itr->second.second + "   ";
        answer.push_back(record);
    }
    }





    return answer;
}
