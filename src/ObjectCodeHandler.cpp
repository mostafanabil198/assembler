#include "ObjectCodeHandler.h"
#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include <Instructions.h>
#include <Singleton.h>
#include <string>


using namespace std;


ObjectCodeHandler::ObjectCodeHandler()
{
    tables = Singleton::getInstance();
}

void ObjectCodeHandler::generateObjectCode()
{
    string tRecord = "";
    string startA = "";
    vector<Instructions> instructions = tables->getAllInstructions();
    for(int i=0; i<instructions.size(); i++)
    {
        if(instructions[i].getError() != "" || instructions[i].getOperation() == "end" || instructions[i].getOperation() == "resb" ||instructions[i].getOperation() == "resw")
        {
            if(instructions[i].getOperation() == "end"){
                    string record = "E";
                    if(tables->symbol_table_contains(instructions[i].getLabel())){
                            record+= "000001";
                    } else {
                        int ad = tables->symbol_table_get(instructions[i].getLabel());
                        std::string out_string;
                        std::stringstream ss;
                        ss << ad;
                        out_string = ss.str();
                        while(out_string.length() < 6){
                            out_string = "0" + out_string;
                        }
                        record += out_string;
                    }
                tables->setEndRecord(record);
            }

            if((instructions[i].getOperation() == "resw" || instructions[i].getOperation() == "resb") && tRecord.length() > 0) {
                tables->addTRecord(startA,tRecord);
                tRecord = "";
            }
            continue;
        }
        if(instructions[i].getOperation() == "start"){
            string record = "H" + instructions[i].getLabel();
            while(record.length() < 7){
                record += " ";
            }
            record += "^" + instructions[i].getOperand();
            tables->setHeaderRecord(record);
        }
        int format = tables->operationFormat(instructions[i].getOperation());
        switch(format)
        {
        case 1:
        {
            instructions[i].setObjectCode(tables->getOpCode(instructions[i].getOperation()));
            if(tRecord.length() + tables->getOpCode(instructions[i].getOperation()).length() <= 60){
                    if(tRecord.length() == 0){
                        startA = to_hexa(instructions[i].getAdress());
                    }
                tRecord += tables->getOpCode(instructions[i].getOperation());
            } else {
                tables->addTRecord(startA,tRecord);
                tRecord = "";
            }
        }
        break;
        case 2:
        {

            //vector<string> result;
            //boost::split(result, instructions[i].getOperand(), boost::is_any_of(","));
            string objectCode = tables->getOpCode(instructions[i].getOperation());


            string double_operands = "([A-Za-z][A-Za-z]?),([A-Za-z][A-Za-z]?)";
            string single_operand = "([A-Za-z][A-Za-z]?)";
            smatch match;
            regex single_operand_regex(single_operand,regex_constants::icase);
            regex double_operands_regex(double_operands,regex_constants::icase);
            string operands = instructions[i].getOperand();
            if(regex_match(operands,match,double_operands_regex))
            {
                objectCode += tables->getRegesterCode(match.str(1));
                objectCode += tables->getRegesterCode(match.str(2));
            }
            else
            {
                objectCode += tables->getRegesterCode(instructions[i].getOperand());
                objectCode += "0";
            }

            instructions[i].setObjectCode(objectCode);
            if(tRecord.length() + objectCode.length() <= 60){
                if(tRecord.length() == 0){
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            } else {
                tables->addTRecord(startA,tRecord);
                tRecord = "";
            }
        }
        break;
        case 3:
        {

            string opCodeH = tables->getOpCode(instructions[i].getOperation());
            string opCodeB = hex_str_to_bin_str(opCodeH);
            opCodeB = opCodeB.substr(0, 6);
            string n = "0";
            string i1 = "0";
            string operand;
            if (instructions[i].getOperand().find("#") != std::string::npos)
            {
                i1 = "1";
                operand = instructions[i].getOperand().substr(1, instructions[i].getOperand().length()-1);
            }
            else if (instructions[i].getOperand().find("@") != std::string::npos)
            {
                operand = instructions[i].getOperand().substr(1, instructions[i].getOperand().length()-1);
                n = "1";
            }
            else
            {
                operand = instructions[i].getOperand();
                i1 = "1";
                n = "1";
            }
            opCodeB+= n;
            opCodeB+= i1;
            string x = "0";
            string b = "0";
            string p = "0";
            string e = "0";
            if (instructions[i].getOperand().find(",x") != std::string::npos)
            {
                x = "1";
                operand = operand.substr(0, instructions[i].getOperand().length()-2);
            }
            int TA;
            if(isdigit(operand[0]))
            {
                TA = std::stoi( operand );
            }
            else
            {
                TA = tables->symbol_table_get(operand);
            }



            int PC = instructions[i+1].getAdress();
            if((TA - PC) > 2047 || (TA - PC) < -2048)
            {
                if(!instructions[i].getBase())
                {
                    p="1";
                    continue;
                    instructions[i].setError2("Displacement out of range");
                }
                else
                {
                    b="1";
                    int B1;
                    if(isdigit(instructions[i].getBaseL()[0]))
                    {
                        B1 = std::stoi( instructions[i].getBaseL() );
                    }
                    else
                    {
                        // msh 3arf mfrod a handle dol azai lw fe m3 base @ aw # aw kda
                        if (instructions[i].getBaseL().find("#") != std::string::npos)
                        {
                            operand = instructions[i].getBaseL().substr(1, instructions[i].getBaseL().length()-1);
                        }
                        else if (instructions[i].getBaseL().find("@") != std::string::npos)
                        {
                            operand = instructions[i].getBaseL().substr(1, instructions[i].getBaseL().length()-1);
                        }
                        else
                        {
                            operand = instructions[i].getBaseL();
                        }
                        B1 = tables->symbol_table_get(operand);
                    }

                    if((TA-B1) < 0 || (TA-B1) > 4059) //base variable
                    {
                        continue;
                        instructions[i].setError2("Displacement out of range");
                    }
                    else
                    {
                        TA=TA-B1; //base variable

                    }
                }
            }
            else
            {
                TA=TA-PC;
                p="1";
            }
            opCodeB+=x;
            opCodeB+=b;
            opCodeB+=p;
            opCodeB+=e;
            opCodeB+=toBinary(TA);
            string objectCode = bin_str_to_hex_str(opCodeB);
            instructions[i].setObjectCode(objectCode);

            if(tRecord.length() + objectCode.length() <= 60){
                if(tRecord.length() == 0){
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            } else {
                tables->addTRecord(startA,tRecord);
                tRecord = "";
            }

        }
        break;
        case 4:
        {
            string opCodeH = tables->getOpCode(instructions[i].getOperation());
            string opCodeB = hex_str_to_bin_str(opCodeH);
            opCodeB = opCodeB.substr(0, 6);
            string n = "0";
            string i1 = "0";
            string operand;
            if (instructions[i].getOperand().find("#") != std::string::npos)
            {
                i1 = "1";
                operand = instructions[i].getOperand().substr(1, instructions[i].getOperand().length()-1);
            }
            else if (instructions[i].getOperand().find("@") != std::string::npos)
            {
                operand = instructions[i].getOperand().substr(1, instructions[i].getOperand().length()-1);
                n = "1";
            }
            else
            {
                operand = instructions[i].getOperand();
                i1 = "1";
                n = "1";
            }
            opCodeB+= n;
            opCodeB+= i1;
            string x = "0";
            string b = "0";
            string p = "0";
            string e = "1";

            if (instructions[i].getOperand().find(",x") != std::string::npos)
            {
                x = "1";
                operand = operand.substr(0, instructions[i].getOperand().length()-2);
            }
            int TA;
            if(isdigit(operand[0]))
            {
                TA = std::stoi( operand );
            }
            else
            {
                TA = tables->symbol_table_get(operand);
            }

            opCodeB+=x;
            opCodeB+=b;
            opCodeB+=p;
            opCodeB+=e;
            opCodeB+=toBinary(TA);
            string objectCode = bin_str_to_hex_str(opCodeB);
            instructions[i].setObjectCode(objectCode);

            if(tRecord.length() + objectCode.length() <= 60){
                if(tRecord.length() == 0){
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            } else {
                tables->addTRecord(startA,tRecord);
                tRecord = "";
            }
        }
        break;
        default:
            break;
        }
    }
    tables->setAllInstructions(instructions);
}

string ObjectCodeHandler::to_hexa(int ad){
    std::stringstream sstream;
    sstream << std::hex << ad;
    return sstream.str();
}

const char* ObjectCodeHandler::hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'A':
        return "1010";
    case 'B':
        return "1011";
    case 'C':
        return "1100";
    case 'D':
        return "1101";
    case 'E':
        return "1110";
    case 'F':
        return "1111";
    }
}

string ObjectCodeHandler::hex_str_to_bin_str(const std::string& hex)
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
        bin += hex_char_to_bin(hex[i]);
    return bin;
}









const char* ObjectCodeHandler::bin_char_to_hex(string c)
{
    // TODO handle default / error
    if(c == "0000") return "0";
    else if(c == "0001") return "1";
    else if(c == "0010") return "2";
    else if(c == "0011") return "3";
    else if(c == "0100") return "4";
    else if(c == "0101") return "5";
    else if(c == "0110") return "6";
    else if(c == "0111") return "7";
    else if(c == "1000") return "8";
    else if(c == "1001") return "9";
    else if(c == "1010") return "A";
    else if(c == "1011") return "B";
    else if(c == "1100") return "C";
    else if(c == "1101") return "D";
    else if(c == "1110") return "E";
    else if(c == "1111") return "F";
}


string ObjectCodeHandler::bin_str_to_hex_str(const std::string& bin)
{
    // TODO use a loop from <algorithm> or smth
    std::string hex;
    for(unsigned i = 0; i != bin.length(); i+=4)
    {
        hex += bin_char_to_hex(bin.substr(i, 4));
    }
    return hex;
}


string ObjectCodeHandler::toBinary(int n)
{
    string r;
    while(n!=0)
    {
        r=(n%2==0 ?"0":"1")+r;
        n/=2;
    }
    while(r.length() < 12)
    {
        r = "0" + r;
    }
    return r;
}
