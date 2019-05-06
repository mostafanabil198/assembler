#include "Parser.h"
#include <iostream>

#include <bits/stdc++.h>
#include <regex>
Parser::Parser()
{
    tables = Singleton::getInstance();
}


Instructions Parser::parse(string line)
{
    //INSTRUCTION REGEX
    regex comment_regex(comment,regex_constants::icase);
    regex start_regex(start,regex_constants::icase);
    regex shift_regex(shift,regex_constants::icase);
    regex rsub_end_regex(rsub_end,regex_constants::icase);
    regex format1_regex(format1,regex_constants::icase);
    regex label_with_operand_regex(label_with_operand,regex_constants::icase);
    regex noLabel_with_operand_regex(noLabel_with_operand,regex_constants::icase);
    regex registers_regex(registers,regex_constants::icase);
    regex byte_operand_regex(byte_operand,regex_constants::icase);

    Instructions i ;
    smatch match;

    if(regex_match(line,match,comment_regex))
    {
        i.setLabel(line);
    }
    else if(regex_match(line,match,start_regex))
    {
        if(!checkLabel(match.str(2)))
        {
            i.setError("Wrong Label Name Stick with naming convention please.");
        }
        i.setLabel(match.str(2));
        i.setOperation(match.str(3));
        i.setOperand(match.str(4));
    }
    else if(regex_match(line,match,shift_regex))
    {
        if(!checkLabel(match.str(2)))
        {
            i.setError("Wrong Label Name Stick with naming convention please.");
        }
        i.setLabel(match.str(2));
        i.setOperation(match.str(3));
        i.setOperand(match.str(4));
        if(!regex_match(match.str(5),registers_regex))
        {
            string s = i.getError();
            s.append(" | Wrong register name");
            i.setError(s);
        }
    }
    else if(regex_match(line,match,rsub_end_regex) && match.str(3) == "rsub")
    {
            if(!checkLabel(match.str(2)))
            {
                i.setError("Wrong Label Name Stick with naming convention please.");
            }
            i.setLabel(match.str(2));
            i.setOperation(match.str(3));
            i.setOperand(match.str(5));
            regex labelIntRegex(labelInt);
            if (!(regex_match(match.str(5),labelIntRegex) || match.str(5) == "")){
                i.setError("WRONG OPERAND WITH RSUB");
            }

    }
    else if(regex_match(line,match,format1_regex))
    {
        if(!checkLabel(match.str(2)))
        {
            i.setError("Wrong Label Name Stick with naming convention please.");
        }
        i.setLabel(match.str(2));
        i.setOperation(match.str(3));
    }
    else if(regex_match(line,match,label_with_operand_regex))
    {
        if(!checkLabel(match.str(1)))
        {
            i.setError("Wrong Label Name Stick with naming convention please.");
        }
        i.setLabel(match.str(1));

        i.setOperation(match.str(2));
        i.setOperand(match.str(3));
        if(match.str(2) == "equ"){
            regex equ_operand_regex(equ_operand,regex_constants::icase);
            if(!regex_match(match.str(3),equ_operand_regex)){
               i.setError("invalid operand");
               }
        } else if (match.str(2) == "byte"){
            if(!regex_match(match.str(3),byte_operand_regex)){

               i.setError("invalid operand");
               }
        } else{
            checkOperand(match.str(3),i);
        }
    }
    else if(regex_match(line,match,noLabel_with_operand_regex))
    {

        i.setOperation(match.str(1));
        i.setOperand(match.str(2));
        if(match.str(1) == "org"){
            regex org_operand_regex("(#|@)?" + label,regex_constants::icase);
            if(!regex_match(match.str(2),org_operand_regex)){
               i.setError("invalid operand");
               }
        }else{
            checkOperand(match.str(2),i);
        }
    }
    else if(regex_match(line,match,rsub_end_regex))
    {
        if(!checkLabel(match.str(2)))
        {
            i.setError("Wrong Label Name Stick with naming convention please.");
        }
        i.setLabel(match.str(2));
        i.setOperation(match.str(3));
        i.setOperand(match.str(5));
        checkOperand(match.str(5),i);
    }
    else
    {
        i.setLabel(line);
        i.setError("Wrong Input Line");
    }
    return i;



}

bool Parser::checkLabel(string label)
{
    regex label_regex(label,regex_constants::icase);
    return regex_match(label,label_regex);
}

void Parser::checkOperand(string operand, Instructions& i)
{
    // check 3la l operand regex
    // w b3den lw fe error a3mlo lw mfish 5las
    // ana 3mlt set fo2 ll operand b nfs l 7aga 3adi fa mt3mlsh set

    //OPERANDS REGEX
    smatch match;
    regex format2_single_operand_regex(format2_single_operand,regex_constants::icase);
    regex format2_double_operands_regex(format2_double_operands,regex_constants::icase);
    regex indexed_addressing_regex(indexed_addressing,regex_constants::icase);
    regex single_operand_regex(single_operand,regex_constants::icase);
    regex doulbe_operands_regex(doulbe_operands,regex_constants::icase);
    regex label_regex(label,regex_constants::icase);


    regex registers_regex(registers,regex_constants::icase);
    regex literals_regex(literals,regex_constants::icase);


    if(regex_match(operand,literals_regex)){
            int numOfBytes = tables->literalOperationsSize(i.getOperation());
        if (numOfBytes != -1){
            if(operand[1] == 'c'){
                if (operand.size() - 4 != numOfBytes){
                    i.setError("Wrong literal length");
                } else {
                    tables->covertLiteralsToHexa(operand);
                }

            } else {
                if (operand.size() - 4 != numOfBytes * 2){
                    i.setError("Wrong literal length");
                }
                else {
                    tables->covertLiteralsToHexa(operand);
                }
            }
        } else if (i.getOperation() == "byte"){
        }


        else {
            i.setError("unsuitable operation with literal");
        }

    }

    else if(i.getOperation() == "resb" || i.getOperation() == "resw"){
            regex resOperand("[0-9]+");
        if(!regex_match(operand,resOperand)){
            i.setError("Wrong Operand Type");
        }
    }
    else if (i.getOperation() == "end"){
        if(!(regex_match(operand,label_regex) || operand == "")){
           i.setError("address expression is not relocatable");
        }
    }
    else if(regex_match(operand,match,format2_single_operand_regex) && tables->operationFormat(i.getOperation()) == 2 && (i.getOperation() == "clear" || i.getOperation() == "svc" || i.getOperation() == "tixr") ){
        if(!regex_match(operand,registers_regex)){
            i.setError("Wrong Register Name");
        }
    } else if(regex_match(operand,match,format2_double_operands_regex) && tables->operationFormat(i.getOperation()) == 2 ){
        if(!regex_match(match.str(1),registers_regex) || !regex_match(match.str(2),registers_regex) ){
            i.setError("Wrong Register Name");
        }
    }

    else if(operand == "*" || operand == "#*" || operand == "@*" || regex_match(operand,indexed_addressing_regex) || (regex_match(operand, single_operand_regex) || (regex_match(operand, doulbe_operands_regex))))
    {
        if(tables->operationFormat(i.getOperation()) == 2){
            i.setError("Invalid Operand");
        }
    }
    else{
            i.setError("Invalid Operand");
    {

}
    }
}


string Parser::hexaToInt(string hexa){
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
