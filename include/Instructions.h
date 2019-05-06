#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <bits/stdc++.h>
using namespace std;
#include <string>




class Instructions
{
    public:
        int getAdress();
        string getOP();
        string getLabel();
        string getOperation();
        string getOperand();
        string getError();
        void setLabel(string label);
        void setError(string error);
        void setAdress(int adress);
        void setOperation(string operation);
        void setOperand(string operand);
        void setOp(string op);
        Instructions();
        bool getBase();
        void setBase(bool base);



    protected:

    private:
        int adress;
        string label;
        string operation;
        string operand;
        string error;
        string op;
        bool base;
};



#endif // INSTRUCTION_H
