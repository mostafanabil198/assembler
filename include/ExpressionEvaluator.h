#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H
#include <instructions.h>
#include <singleton.h>

class ExpressionEvaluator
{
    public:
        ExpressionEvaluator();
        pair<bool,string> checkOperand(Instructions& inst);
    protected:
    private:
        Singleton* tables;
        bool checkExist(string operand);
        bool isOperations(string operation);
        int get_priority(string operation);
        pair<bool,pair<int,string>>validateOperandsTypeEvaluation(pair<int,string>operandOne,
                                                pair<int,string>operandTwo,string operation);
};

#endif // EXPRESSIONEVALUATOR_H
