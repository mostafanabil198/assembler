#include <iostream>
#include <regex>
#include <Parser.h>
#include <bits/stdc++.h>
#include <Files.h>
#include <Singleton.h>
#include <ObjectCodeHandler.h>
using namespace std;

int main()
{
    string in;
    getline (cin, in);
    smatch match;
    regex execute("pass1 (.+)");
    regex execute2("assemble (.+)");
    vector<string> result ;
    Singleton* tables = Singleton::getInstance();
    Files file;
    if(regex_match(in,match,execute) || regex_match(in,match,execute2)){
        tables->set_end(false);
        file.readFromFile(match.str(1));
        cout << endl << "------------ PASS ONE ------------" << endl;
       result = file.print(tables->getAllInstructions(),true);
        for(int i = 0; i < result.size(); i++){
            cout << result[i] + "\n";
        }

    }
     if (regex_match(in,match,execute2)){
        cout << endl << endl << "------------- PASS TWO ------------" << endl;
        ObjectCodeHandler oo;
        oo.generateObjectCode();
        result = file.print(tables->getAllInstructions(),false);
        for(int i = 0; i < result.size(); i++){
            cout << result[i] + "\n";
        }
        if(!tables->getError2()){
            cout << endl << endl << "-------------- OBJECT PROGRAM ------------" << endl;

            vector<string> aa = oo.getObjectProgram();
            for(int i = 0; i < aa.size(); i++){
                cout << aa[i] << endl;
            }
        }

    }

    cin >> in;
    return 0;
}
