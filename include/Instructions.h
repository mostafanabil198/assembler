#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <bits/stdc++.h>
using namespace std;
#include <string>




class Instructions
{
    public:
        int getAdress();
        string getObjectCode();
        string getLabel();
        string getOperation();
        string getOperand();
        string getError();
        string getError2();
        void setLabel(string label);
        void setError(string error);
        void setError2(string error2);
        void setAdress(int adress);
        void setOperation(string operation);
        void setOperand(string operand);
        void setObjectCode(string op);
        Instructions();
        bool getBase();
        void setBase(bool base);
        string getBaseL();
        void  setBaseL(string baseL);



    protected:

    private:
        int adress;
        string label;
        string operation;
        string operand;
        string error;
        string objectCode;
        bool base;
        string error2;
        string baseL;
};



#endif // INSTRUCTION_H
