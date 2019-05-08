#include <Validate.h>
#include <Singleton.h>
#include <bits/stdc++.h>
using namespace std;
#include <string>

Validate::Validate()
{
    tables = Singleton::getInstance();
    format = tables->getOperations();
    int aa = format.size();
    //cout << format["sta"].first;
}

void Validate::table(Instructions i)
{
    regex exp_Regex(doulbe_operands);
    bool literals = false;

    if(i.getError() == "")
    {
        if(i.getLabel().size() <= 8 || i.getLabel()[0] == '.')
        {
            if(!start)
            {
                if(i.getLabel()[0] == '.')
                {
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                }
                else if(i.getOperation() == "start")
                {
                    istringstream iss (hexaToInt(i.getOperand()));
                    iss >> add;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                }
                else if(format.find(i.getOperation()) != format.end())
                {
                    add = 0;
                    start = true;
                    i.setBase(base);
                    i.setBaseL(baseLabel);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        if(tables->symbol_table_contains(i.getLabel()))
                        {
                            tables->symbol_table_add(i.getLabel(),add,"relocatable");
                        }
                    }

                    add = add + format[i.getOperation()].first;
                }
                else if(i.getOperation() == "word")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        if(tables->symbol_table_contains(i.getLabel()))
                        {
                            tables->symbol_table_add(i.getLabel(),add,"relocatable");
                        }
                    }
                    add = add + 3;
                }

                else if(i.getOperation() == "byte")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        if(tables->symbol_table_contains(i.getLabel()))
                        {
                            tables->symbol_table_add(i.getLabel(),add,"relocatable");
                        }
                    }
                    if(i.getOperand()[0] == 'x')
                    {
                        if((i.getOperand().size() - 3) % 2 == 0)
                        {
                            add += (i.getOperand().size() - 3)/2;
                        }
                        else
                        {
                            i.setError("Wrong Hexadecimal input must be even number of bits");
                        }
                    }
                    else if(i.getOperand()[0] == 'c')
                    {
                        add += (i.getOperand().size() - 3);
                    }
                    else if(i.getOperand()[0] == '=' && i.getOperand()[1] == 'x')
                    {
                        if((i.getOperand().size() - 4) % 2 == 0)
                        {
                            add += (i.getOperand().size() - 4)/2;
                        }
                        else
                        {
                            i.setError("Wrong Hexadecimal input must be even number of bits");
                        }
                    }
                    else if(i.getOperand()[0] == '=' && i.getOperand()[1] == 'c')
                    {
                        add += (i.getOperand().size() - 4);
                    }
                    else
                    {
                        i.setError("Wrong operand");
                    }
                }
                else if(i.getOperation() == "resw")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        if(tables->symbol_table_contains(i.getLabel()))
                        {
                            tables->symbol_table_add(i.getLabel(),add,"relocatable");
                        }
                    }
                    int num = 0;
                    istringstream iss (i.getOperand());
                    iss >> num;
                    add = add + 3*num;
                }
                else if(i.getOperation() == "resb")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        if(tables->symbol_table_contains(i.getLabel()))
                        {
                            tables->symbol_table_add(i.getLabel(),add,"relocatable");
                        }
                    }
                    int num = 0;
                    istringstream iss (i.getOperand());
                    iss >> num;
                    add = add + 1*num;
                }
                else if(i.getOperation() == "equ")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        if(tables->symbol_table_contains(i.getLabel()))
                        {
                            if(i.getOperand() == "*" || i.getOperand() == "@*" || i.getOperand() == "#*")
                            {
                                tables->symbol_table_add(i.getLabel(),add,"relocatable");
                            }
                            else if(isdigit(i.getOperand()[0]))
                            {
                                int num = 0;
                                istringstream iss (i.getOperand());
                                iss >> num;
                                tables->symbol_table_add(i.getLabel(),num,"absolute");
                            }
                            else if(i.getOperand()[0] == '#' || i.getOperand()[0] == '@')
                            {
                                string r = i.getOperand().substr(1, i.getOperand().size() -1);
                                if(isdigit(r[0]))
                                {
                                    int num = 0;
                                    istringstream iss (r);
                                    iss >> num;
                                    tables->symbol_table_add(i.getLabel(),num,"absolute");
                                }
                                else
                                {
                                    if(!tables->symbol_table_contains(r))
                                    {
                                        tables->symbol_table_add(i.getLabel(),tables->symbol_table_get(r),"relocatable");
                                    }
                                    else
                                    {
                                        i.setError("wrong label");
                                    }
                                }
                            }
                            else if(regex_match(i.getOperand(), exp_Regex))
                            {
                                // expretion
                                pair<bool, string> result = evalutor.checkOperand(i);
                                if(result.first)
                                {
                                   int objectCodevalue=stoi(i.getObjectCode());
                                        if(objectCodevalue<0){
                                            i.setError("address can't be negative");
                                        }else{
                                        tables->symbol_table_add(i.getLabel(),stoi(i.getObjectCode()),result.second);
                                        }
                                }
                            }
                            else if(isalpha(i.getOperand()[0]))
                            {
                                if(!tables->symbol_table_contains(i.getOperand()))
                                {
                                    tables->symbol_table_add(i.getLabel(),tables->symbol_table_get(i.getOperand()),"relocatable");
                                }
                                else
                                {
                                    i.setError("wrong label");
                                }
                            }
                        }
                        else
                        {
                            i.setError("wrong label");
                        }
                    }
                    else
                    {
                        i.setError("empty label");
                    }
                }
                else if(i.getOperation() == "org")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() == "")
                    {
                        if(i.getOperand()[0] == '@' || i.getOperand()[0] == '#')
                        {
                            string r = i.getOperand().substr(1, i.getOperand().size() -1);
                            if(!tables->symbol_table_contains(r))
                            {
                                add = tables->symbol_table_get(r);
                            }
                            else
                            {
                                i.setError("wrong label");
                            }
                        }
                        else if(regex_match(i.getOperand(), exp_Regex))
                        {
                            // expretion
                            pair<bool, string> result = evalutor.checkOperand(i);
                            if(result.first)
                            {
                                if(result.second == "relocatable")
                                {
                                   int objectCodevalue=stoi(i.getObjectCode());
                                        if(objectCodevalue<0){
                                            i.setError("address can't be negative");
                                        }else{
                                        add = stoi(i.getObjectCode());
                                        }
                                }
                                else
                                {
                                    i.setError("wrong operand type");
                                }
                            }
                        }

                        else
                        {
                            if(!tables->symbol_table_contains(i.getOperand()))
                            {
                                add = tables->symbol_table_get(i.getOperand());
                            }
                            else
                            {
                                i.setError("wrong label");
                            }
                        }
                    }
                    else
                    {
                        i.setError("cannot have a label");
                    }
                }
                else if(i.getOperation() == "ltorg")
                {
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setAdress(add);
                    i.setBase(base);
                    literals = true;
                    if(i.getLabel() !="")
                    {
                        i.setError("cannot have a label");
                    }
                }
                else if(i.getOperation() == "base")
                {
                    baseLabel = i.getOperand();
                    add = 0;
                    base = true;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        i.setError("cannot have a label");
                    }
                }
                else if (i.getOperation() == "nobase")
                {
                    baseLabel = "";
                    base = false;
                    add = 0;
                    start = true;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                    if(i.getLabel() != "")
                    {
                        i.setError("cannot have a label");
                    }
                    else if(i.getOperand() != "")
                    {
                        i.setError("cannot have operand");
                    }
                }
                else if(i.getOperation() == "use")
                {
                    start = true;
                    add = 0;
                    i.setBaseL(baseLabel);
                    i.setBase(base);
                    i.setAdress(add);
                }
                else
                {
                    i.setError("wrong operation");
                    i.setBase(base);
                    i.setBaseL(baseLabel);
                    i.setAdress(add);
                }
            }
            else
            {
                if(!end)
                {
                    if(i.getLabel()[0] == '.')
                    {
                        i.setBase(base);
                        i.setBaseL(baseLabel);
                        i.setAdress(add);
                    }
                    else if(i.getOperation()=="end")
                    {
                        end = true;
                        literals = true;
                        tables->set_end(true);
                        i.setBase(base);
                        i.setBaseL(baseLabel);
                        i.setAdress(add);
                    }
                    else if(format.find(i.getOperation()) != format.end())
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);

                        if(i.getLabel() != "")
                        {
                            if(tables->symbol_table_contains(i.getLabel()))
                            {
                                tables->symbol_table_add(i.getLabel(),add,"relocatable");
                                add = add + format[i.getOperation()].first;
                            }
                            else
                            {
                                i.setError("label name already exist");
                            }
                        }
                        else
                            add = add + format[i.getOperation()].first;
                    }
                    else if(i.getOperation() == "word")
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        if(i.getLabel() != "")
                        {
                            if(tables->symbol_table_contains(i.getLabel()))
                            {
                                tables->symbol_table_add(i.getLabel(),add,"relocatable");
                                add = add +3;
                            }
                            else
                            {
                                i.setError("label name already exist");
                            }
                        }
                        else
                            add = add + 3;
                    }
                    else if(i.getOperation() == "byte")
                    {
                        bool byte = true;
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        i.setAdress(add);
                        if(i.getLabel() != "")
                        {
                            if(tables->symbol_table_contains(i.getLabel()))
                            {
                                tables->symbol_table_add(i.getLabel(),add,"relocatable");
                            }
                            else
                            {
                                byte = false;
                                i.setError("label name already exist");
                            }
                        }
                        if(i.getOperand()[0] == 'x' && byte)
                        {
                            if((i.getOperand().size() - 3) % 2 == 0)
                            {
                                add += (i.getOperand().size() - 3)/2;
                            }
                            else
                            {
                                i.setError("Wrong Hexadecimal input must be even number of bits");
                            }
                        }
                        else if(i.getOperand()[0] == 'c' && byte)
                        {
                            add += (i.getOperand().size() - 3);
                        }
                        else if(i.getOperand()[0] == '=' && i.getOperand()[1] == 'x' && byte)
                        {
                            if((i.getOperand().size() - 4) % 2 == 0)
                            {
                                add += (i.getOperand().size() - 4)/2;
                            }
                            else
                            {
                                i.setError("Wrong Hexadecimal input must be even number of bits");
                            }
                        }
                        else if(i.getOperand()[0] == '=' && i.getOperand()[1] == 'c' && byte)
                        {
                            add += (i.getOperand().size() - 4);
                        }
                        else if(byte)
                        {
                            i.setError("Wrong operand");
                        }
                    }
                    else if(i.getOperation() == "resw")
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        if(i.getLabel() != "")
                        {
                            if(tables->symbol_table_contains(i.getLabel()))
                            {
                                tables->symbol_table_add(i.getLabel(),add,"relocatable");
                                int num = 0;
                                istringstream iss (i.getOperand());
                                iss >> num;
                                add = add + 3*num;

                            }
                            else
                            {
                                i.setError("label name already exist");
                            }
                        }
                        else
                        {
                            int num = 0;
                            istringstream iss (i.getOperand());
                            iss >> num;
                            add = add + 3*num;
                        }
                    }
                    else if(i.getOperation() == "resb")
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        if(i.getLabel() != "")
                        {
                            if(tables->symbol_table_contains(i.getLabel()))
                            {
                                tables->symbol_table_add(i.getLabel(),add,"relocatable");
                                int num = 0;
                                istringstream iss (i.getOperand());
                                iss >> num;
                                add = add + 1*num;

                            }
                            else
                            {
                                i.setError("label name already exist");
                            }
                        }
                        else
                        {
                            int num = 0;
                            istringstream iss (i.getOperand());
                            iss >> num;
                            add = add + 1*num;
                        }
                    }
                    else if(i.getOperation() == "equ")
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        if(i.getLabel() != "")
                        {
                            if(tables->symbol_table_contains(i.getLabel()))
                            {
                                if(i.getOperand() == "*" || i.getOperand() == "@*" || i.getOperand() == "#*")
                                {
                                    tables->symbol_table_add(i.getLabel(),add,"relocatable");
                                }
                                else if(isdigit(i.getOperand()[0]))
                                {
                                    int num = 0;
                                    istringstream iss (i.getOperand());
                                    iss >> num;
                                    tables->symbol_table_add(i.getLabel(),num,"absolute");
                                }
                                else if(i.getOperand()[0] == '#' || i.getOperand()[0] == '@')
                                {
                                    string r = i.getOperand().substr(1, i.getOperand().size() -1);
                                    if(isdigit(r[0]))
                                    {
                                        int num = 0;
                                        istringstream iss (r);
                                        iss >> num;
                                        tables->symbol_table_add(i.getLabel(),num,"absolute");
                                    }
                                    else
                                    {
                                        if(!tables->symbol_table_contains(r))
                                        {
                                            tables->symbol_table_add(i.getLabel(),tables->symbol_table_get(r),"relocatable");
                                        }
                                        else
                                        {
                                            i.setError("wrong label");
                                        }
                                    }
                                }
                                else if(regex_match(i.getOperand(), exp_Regex))
                                {
                                    // expretion
                                    pair<bool, string> result = evalutor.checkOperand(i);
                                    if(result.first)
                                    {
                                        int objectCodevalue=stoi(i.getObjectCode());
                                        if(objectCodevalue<0){
                                            i.setError("address can't be negative");
                                        }else{
                                        tables->symbol_table_add(i.getLabel(),stoi(i.getObjectCode()),result.second);
                                        }
                                    }
                                }

                                else if(isalpha(i.getOperand()[0]))
                                {
                                    if(!tables->symbol_table_contains(i.getOperand()))
                                    {
                                        tables->symbol_table_add(i.getLabel(),tables->symbol_table_get(i.getOperand()),"relocatable");
                                    }
                                    else
                                    {
                                        i.setError("wrong label");
                                    }
                                }
                            }
                            else
                            {
                                i.setError("wrong label");
                            }
                        }
                        else
                        {
                            i.setError("empty label");
                        }
                    }
                    else if(i.getOperation() == "org")
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        if(i.getLabel() == "")
                        {
                            if(i.getOperand()[0] == '@' || i.getOperand()[0] == '#')
                            {
                                string r = i.getOperand().substr(1, i.getOperand().size() -1);
                                if(!tables->symbol_table_contains(r))
                                {
                                    add = tables->symbol_table_get(r);
                                }
                                else
                                {
                                    i.setError("wrong label");
                                }
                            }
                            else if(regex_match(i.getOperand(), exp_Regex))
                            {
                                // expretion
                                pair<bool, string> result = evalutor.checkOperand(i);
                                if(result.first)
                                {
                                    if(result.second == "relocatable")
                                    {
                                        int objectCodevalue=stoi(i.getObjectCode());
                                        if(objectCodevalue<0){
                                            i.setError("address can't be negative");
                                        }else{
                                        add = stoi(i.getObjectCode());
                                        }
                                    }
                                    else
                                    {
                                        i.setError("wrong operand type");
                                    }
                                }
                            }

                            else
                            {
                                if(!tables->symbol_table_contains(i.getOperand()))
                                {
                                    add = tables->symbol_table_get(i.getOperand());
                                }
                                else
                                {
                                    i.setError("wrong label");
                                }
                            }
                        }
                        else
                        {
                            i.setError("cannot have a label");
                        }
                    }
                    else if(i.getOperation() == "ltorg")
                    {
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        // literals = true;

                        if(i.getLabel() !="")
                        {
                            i.setError("cannot have a label");
                        }
                        else
                            literals = true;



                    }
                    else if(i.getOperation() == "base")
                    {
                        baseLabel = i.getOperand();
                        base = true;
                        i.setBase(base);
                        i.setBaseL(baseLabel);
                        i.setAdress(add);
                        if(i.getLabel() != "")
                        {
                            i.setError("cannot have a label");
                        }
                    }
                    else if (i.getOperation() == "nobase")
                    {
                        baseLabel = "";
                        base = false;
                        i.setBaseL(baseLabel);
                        i.setBase(base);
                        i.setAdress(add);
                        if(i.getLabel() != "")
                        {
                            i.setError("cannot have a label");
                        }
                        else if(i.getOperand() != "")
                        {
                            i.setError("cannot have operand");
                        }
                    }
                    else if(i.getOperation() == "use")
                    {
                        i.setAdress(add);
                        i.setBase(base);
                        i.setBaseL(baseLabel);
                    }

                    else
                    {
                        i.setAdress(add);
                        i.setBase(base);
                        i.setBaseL(baseLabel);
                        i.setError("wrong operation");
                    }
                }
                else
                {
                    if(i.getLabel()[0] == '.')
                    {
                        i.setBase(base);
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                    }
                    else
                    {
                        i.setBase(base);
                        i.setAdress(add);
                        i.setBaseL(baseLabel);
                        i.setError("cannot write under end");
                    }
                }
            }
        }
        else
        {
            i.setError("label cannot be this name");
            i.setAdress(add);
            i.setBaseL(baseLabel);
            i.setBase(base);
        }
    }
    else
    {
        i.setBase(base);
        i.setBaseL(baseLabel);
        i.setAdress(add);
    }
    tables->addInstruction(i);
    if(literals)
    {
        while(!tables->isLiteralEmpty())
        {
            Instructions literal = tables->getLiteral();
            int increment = literal.getAdress();
            literal.setAdress(add);
            tables->setLiteralAddress(literal.getLabel(),add);
            add += increment;
            tables->addInstruction(literal);

        }
    }
}

string Validate::hexaToInt(string hexa)
{
    int i, r, len, hex = 0;
    len = hexa.length();
    for (i = 0; hexa[i] != '\0'; i++)
    {
        len--;
        if(hexa[i] >= '0' && hexa[i] <= '9')
            r = hexa[i] - 48;
        else if(hexa[i] >= 'a' && hexa[i] <= 'f')
            r = hexa[i] - 87;
        else if(hexa[i] >= 'A' && hexa[i] <= 'F')
            r = hexa[i] - 55;
        hex += r * pow(16,len);
    }

    return to_string(hex);

}

