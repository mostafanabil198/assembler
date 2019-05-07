#include "ExpressionEvaluator.h"
#include <iostream>
#include <Instructions.h>
#include <bits/stdc++.h>
#include <regex>
ExpressionEvaluator::ExpressionEvaluator()
{
    tables = Singleton::getInstance();
}
pair<bool,string> ExpressionEvaluator::checkOperand(Instructions& inst)
{
    string expression=inst.getOperand();
    // regex object.
    regex re("(([a-zA-Z][a-zA-Z0-9]*)|(\\+|\\-|\\*|\\/)|([0-9]+))");
    vector<string> expression_words;
    // finding all the match.
    for (sregex_iterator it = sregex_iterator(expression.begin(), expression.end(), re);
            it != sregex_iterator(); ++it)
    {
        {
            smatch match;
            match = *it;
            expression_words.push_back(match.str(0));
        }
        regex operations_regex("\\+|\\-|\\*|\\/");
        regex constants_regex("[0-9]+");
        //smatch match;
        vector <pair<int,string>>valueTypeExpression;
        for(int i=0; i<expression_words.size(); i++)
        {
            if(regex_match(expression_words[i],operations_regex) )
            {
                valueTypeExpression.push_back(make_pair(get_priority(expression_words[i]),expression_words[i]));
            }
            else if(regex_match(expression_words[i],constants_regex))
            {
                valueTypeExpression.push_back(make_pair(stoi(expression_words[i]),"constant"));

            }
            else if(checkExist(expression_words[i]))
            {
                valueTypeExpression.push_back(make_pair(tables->symbol_table_get(expression_words[i]),tables->symbol_table_get_type(expression_words[i])));

            }
            else
            {
                inst.setError("operand not predefined");
                pair<bool,string>ans=make_pair(false,"");
                return ans;
            }
        }
        stack<pair<int,string>>value;
        stack<pair<int,string>>operations;
        for(int i=0; i<valueTypeExpression.size(); i++)
        {
            if(isOperations(valueTypeExpression[i].second))
            {
                if(!operations.empty())
                {
                    while(valueTypeExpression[i].first<=operations.top().first)
                    {
                        pair<int,string>operandtwo=value.top();
                        value.pop();
                        pair<int,string>operandOne=value.top();
                        value.pop();
                        string operation=operations.top().second;
                        operations.pop();
                        pair<bool,pair<int,string>>evaluationResult=validateOperandsTypeEvaluation(operandOne,operandtwo,operation);
                        if(evaluationResult.first)
                        {
                            value.push(evaluationResult.second);
                        }
                        else
                        {
                            inst.setError("invalid expression on operands types");
                            pair<bool,string>ans=make_pair(false,"");
                            return ans;
                        }
                    }
                    operations.push(valueTypeExpression[i]);
                }
                else
                {
                    operations.push(valueTypeExpression[i]);
                }
            }
            else
            {
                value.push(valueTypeExpression[i]);
            }
        }
        while(!operations.empty())
        {
            pair<int,string>operandtwo=value.top();
            value.pop();
            pair<int,string>operandOne=value.top();
            value.pop();
            string operation=operations.top().second;
            operations.pop();
            pair<bool,pair<int,string>>evaluationResult=validateOperandsTypeEvaluation(operandOne,operandtwo,operation);
            if(evaluationResult.first)
            {
                value.push(evaluationResult.second);
            }
            else
            {
                inst.setError("invalid expression on operands types");
                pair<bool,string>ans=make_pair(false,"");
                return ans;
            }
        }
        if(value.size()!=1)
        {
            inst.setError("invalid expression");
            pair<bool,string>ans=make_pair(false,"");
            return ans;
        }
        pair<int,string>expressionValue=value.top();
        value.pop();
        inst.setObjectCode(to_string(expressionValue.first));
        pair<bool,string>ans=make_pair(true,expressionValue.second);
        return ans;

    }
}
bool ExpressionEvaluator::checkExist(string operand)
{
    return !(tables->symbol_table_contains(operand));
}
int ExpressionEvaluator::get_priority(string operation)
{
    if(operation=="*"||operation=="/") return 2;
    return 1;
}

bool ExpressionEvaluator::isOperations(string operation)
{
    regex operations_regex("\\+|\\-|\\*|\\/");
    return regex_match(operation,operations_regex);
}
pair<bool,pair<int,string>>ExpressionEvaluator::validateOperandsTypeEvaluation(pair<int,string>operandOne,
                         pair<int,string>operandTwo,string operation)
{

    if(operation ==  "*")
    {

        if(operandOne.second=="relocatable" ||operandTwo.second=="relocatable" )
        {
            pair<bool,pair<int,string>> answer=make_pair(false,make_pair(0,""));
            return answer;
        }
        pair<bool,pair<int,string>>answer=make_pair(true,make_pair(operandOne.first*operandTwo.first,"absolute"));
        return answer;
    }
    else if(operation ==  "/")
    {
        if(operandOne.second=="relocatable" ||operandTwo.second=="relocatable" )
        {
            pair<bool,pair<int,string>> answer=make_pair(false,make_pair(0,""));
            return answer;
        }
        pair<bool,pair<int,string>> answer=make_pair(true,make_pair(operandOne.first/operandTwo.first,"absolute"));
        return answer;

    }
    else if(operation ==  "+")
    {

    }

    else if(operation ==  "-")
    {



    }

}

