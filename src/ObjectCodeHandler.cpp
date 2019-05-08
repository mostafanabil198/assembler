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
        string op = instructions[i].getOperation();
        if(instructions[i].getError() != "" || op == "end" || op == "org" || op == "resb" || op == "resw" || op == "equ" || op == "ltorg" || op == "base" || op == "nobase")
        {
            if(instructions[i].getOperation() == "end")
            {
                string record = "E^";
                if(tables->symbol_table_contains(instructions[i].getLabel()))
                {
                    record+= "000001";
                }
                else
                {
                    int ad = tables->symbol_table_get(instructions[i].getLabel());
                    std::string out_string;
                    std::stringstream ss;
                    ss << ad;
                    out_string = ss.str();
                    while(out_string.length() < 6)
                    {
                        out_string = "0" + out_string;
                    }
                    record += out_string;
                }
                tables->setEndRecord(record);
            }

            if((op == "resw" || op == "resb" || op == "org") && tRecord.length() > 0)
            {
                tables->addTRecord(startA,tRecord);
                tRecord = "";
                startA = "";
            }
            continue;
        }

        if(instructions[i].getOperation() == "byte")
        {
            string objectCode;
            if(instructions[i].getOperand().find("x'") != std::string::npos)
            {
                objectCode = instructions[i].getOperand().substr(2, instructions[i].getOperand().length()-3);
            }
            else
            {
                string objectCodeC = instructions[i].getOperand().substr(2, instructions[i].getOperand().length()-3);
                objectCode = tables->convertToAscii(objectCodeC);
            }
            instructions[i].setObjectCode(objectCode);
            if(tRecord.length() + objectCode.length() <= 60)
            {
                if(tRecord.length() == 0)
                {
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            }
            else
            {
                tables->addTRecord(startA,tRecord);
                tRecord = objectCode;
                startA = to_hexa(instructions[i].getAdress());
            }
            continue;
        }
        else if(instructions[i].getOperation() == "word")
        {
            string objectCodeC = instructions[i].getOperand();
            string objectCode;
            string nums = "[0-9]+";
            regex numsR(nums,regex_constants::icase);
            if(regex_match(objectCodeC,numsR))
            {
                objectCode = tables->convertToAscii(objectCodeC);
                while(objectCode.length() < 6)
                {
                    objectCode = "0" + objectCode;
                }
            }
            else
            {
                objectCode = "000000";
            }
            instructions[i].setObjectCode(objectCode);
            if(tRecord.length() + objectCode.length() <= 60)
            {
                if(tRecord.length() == 0)
                {
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            }
            else
            {
                tables->addTRecord(startA,tRecord);
                tRecord = objectCode;
                startA = to_hexa(instructions[i].getAdress());
            }
            continue;
        }


//---------------------------------
// lsa fl start fadl a5r goz2 azwdo fl record ali hwa l size bta3 l object code kolo
        if(instructions[i].getOperation() == "start")
        {
            string record = "H^" + instructions[i].getLabel();
            while(record.length() < 7)
            {
                record += " ";
            }
            string o = instructions[i].getOperand();
            while(o.length() < 6){
                o = "0" + o;
            }
            record += "^" + o + "^";
            tables->setHeaderRecord(record);
        }

        int format = tables->operationFormat(instructions[i].getOperation());
        switch(format)
        {
        case 1:
        {
            instructions[i].setObjectCode(tables->getOpCode(instructions[i].getOperation()));
            if(tRecord.length() + tables->getOpCode(instructions[i].getOperation()).length() <= 60)
            {
                if(tRecord.length() == 0)
                {
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += tables->getOpCode(instructions[i].getOperation());
            }
            else
            {
                tables->addTRecord(startA,tRecord);
                tRecord = tables->getOpCode(instructions[i].getOperation());
                startA = to_hexa(instructions[i].getAdress());
            }
        }
        break;
        case 2:
        {
            string objectCode = tables->getOpCode(instructions[i].getOperation());
            string double_operands = "([A-Za-z][A-Za-z]?),([A-Za-z][A-Za-z]?)";
            string single_operand = "([A-Za-z][A-Za-z]?)";
            smatch match;
            regex single_operand_regex(single_operand,regex_constants::icase);
            regex double_operands_regex(double_operands,regex_constants::icase);
            string operands = instructions[i].getOperand();
            if(regex_match(operands,match,double_operands_regex))
            {

                std::stringstream ss;
                ss << tables->getRegesterCode(match.str(1));
                objectCode += ss.str();
                std::stringstream ss1;
                ss1 << tables->getRegesterCode(match.str(2));
                objectCode += ss1.str();
            }
            else
            {
                std::stringstream ss;
                ss << tables->getRegesterCode(instructions[i].getOperand());
                objectCode += ss.str();
                objectCode += "0";
            }

            instructions[i].setObjectCode(objectCode);
            if(tRecord.length() + objectCode.length() <= 60)
            {
                if(tRecord.length() == 0)
                {
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            }
            else
            {
                tables->addTRecord(startA,tRecord);
                tRecord = objectCode;
                startA = to_hexa(instructions[i].getAdress());
            }
        }
        break;
        case 3:
        {
            if(instructions[i].getOperation() == "rsub")
            {
                string objectCode = "4F0000";
                instructions[i].setObjectCode(objectCode);
                if(tRecord.length() + objectCode.length() <= 60)
                {
                    if(tRecord.length() == 0)
                    {
                        startA = to_hexa(instructions[i].getAdress());
                    }
                    tRecord += objectCode;
                }
                else
                {
                    tables->addTRecord(startA,tRecord);
                    tRecord = objectCode;
                    startA = to_hexa(instructions[i].getAdress());
                }
                continue;
            }
            bool numb = false;
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
                numb = true;
                TA = std::stoi( operand );
            }
            else
            {
                numb = false;
                TA = tables->symbol_table_get(operand);
            }



            int PC = instructions[i+1].getAdress();
            if(!(i1 == "1" && n == "0" && numb))
            {
                if((TA - PC) > 2047 || (TA - PC) < -2048)
                {
                    if(!instructions[i].getBase())
                    {
                        p="1";
                        //  cout << instructions[i].getAdress() << " " << instructions[i].getLabel() << "  " << instructions[i].getOperation() << "  " << instructions[i].getOperand() << endl;
                        instructions[i].setError2("Displacement out of range");
                        continue;
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
                            instructions[i].setError2("Displacement out of range");
                            continue;
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
            }
            opCodeB+=x;
            opCodeB+=b;
            opCodeB+=p;
            opCodeB+=e;
            opCodeB+=toBinary(twos(TA,12));
            // cout << "3 " << TA << " " << toBinary(twos(TA,12)) << endl;
            string objectCode = bin_str_to_hex_str(opCodeB);

            std::stringstream sss;
            sss << "n:" << n << "  i:" << i1 << "  x:" << x << "  b:" << b << "  p:" << p << "  e:" << e;
            instructions[i].setNixbpe(sss.str());
            //objectCode= "n:" + n + "i:" + i + "x:" + x + "b:" + b + "e:" + e + "  " + objectCode;
            //instructions[i].setObjectCode(objectCode);

            instructions[i].setObjectCode(objectCode);
            if(tRecord.length() + objectCode.length() <= 60)
            {
                if(tRecord.length() == 0)
                {
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            }
            else
            {
                tables->addTRecord(startA,tRecord);
                tRecord = objectCode;
                startA = to_hexa(instructions[i].getAdress());
            }

        }
        break;
        case 4:
        {
            if(instructions[i].getOperation() == "+rsub")
            {
                string objectCode = "4F000000";
                instructions[i].setObjectCode(objectCode);
                if(tRecord.length() + objectCode.length() <= 60)
                {
                    if(tRecord.length() == 0)
                    {
                        startA = to_hexa(instructions[i].getAdress());
                    }
                    tRecord += objectCode;
                }
                else
                {
                    tables->addTRecord(startA,tRecord);
                    tRecord = objectCode;
                    startA = to_hexa(instructions[i].getAdress());
                }
                continue;
            }

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
            string xx = toBinary(twos(TA,20));
            while(xx.length() < 20)
            {
                xx = "0" + xx;
            }
            opCodeB+= xx;
            //cout << "4 " << TA << " " << toBinary(twos(TA,20)) << " " << opCodeB << endl;
            string objectCode = bin_str_to_hex_str(opCodeB);
            std::stringstream sss;
            sss << "n:" << n << "  i:" << i1 << "  x:" << x << "  b:" << b << "  p:" << p << "  e:" << e;
            instructions[i].setNixbpe(sss.str());
            instructions[i].setObjectCode(objectCode);

            if(tRecord.length() + objectCode.length() <= 60)
            {
                if(tRecord.length() == 0)
                {
                    startA = to_hexa(instructions[i].getAdress());
                }
                tRecord += objectCode;
            }
            else
            {
                tables->addTRecord(startA,tRecord);
                tRecord = objectCode;
                startA = to_hexa(instructions[i].getAdress());
            }
        }
        break;
        default:
            break;
        }
    }
    tables->setAllInstructions(instructions);
    if(tRecord.length() > 0)
    {
        tables->addTRecord(startA,tRecord);
    }
}



vector<string> ObjectCodeHandler::getObjectProgram(){
    vector<string> objectProgram;
    string record;
    int programL = 0;
    vector<pair<string,string>> textRecords = tables->getTextRecords();
    for(int i = 0; i < textRecords.size(); i++){
        record = "T";
        string startAd = textRecords[i].first;
        while(startAd.length() < 6){
            startAd = "0" + startAd;
        }
        programL += textRecords[i].second.length();
        string recordL = to_hexa(textRecords[i].second.length());
        record += "^" + startAd + "^" + recordL + "^" + textRecords[i].second;
        objectProgram.push_back(record);
    }
    objectProgram.push_back(tables->getEndRecord());
    string programLH = to_hexa(programL);
    record = tables->getHeaderRecord();
    while(programLH.length() < 6){
        programLH = "0" + programLH;
    }
    record+= programLH;
    objectProgram.insert(objectProgram.begin(),record);

    return objectProgram;
}


string ObjectCodeHandler::to_hexa(int ad)
{
    std::stringstream sstream;
    sstream << std::hex << ad;
    return sstream.str();
}

const char* ObjectCodeHandler::hex_char_to_bin(char c)
{
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

int ObjectCodeHandler::twos(int num, int bits)
{
    if(num >= 0)
        return num;
    num = abs(num);
    int t = 0;
    int start = 1;
    int result = 0;
    while(num)
    {
        int d = num % 2;
        num /= 2;
        if(!d)
            result += start;
        start *= 2;
        t++;
    }
    while(t < bits)
    {
        t++;
        result += start;
        start *= 2;
    }
    return result+1;
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


