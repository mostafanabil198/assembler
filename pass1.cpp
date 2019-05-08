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
    if(regex_match(in,match,execute)){
        Singleton* tables = Singleton::getInstance();
        tables->set_end(false);
        Files file;
        file.readFromFile(match.str(1));
        vector<string> result = file.print(tables->getAllInstructions());
        for(int i = 0; i < result.size(); i++){
            cout << result[i] + "\n";
        }
    }
    cout << endl << endl;
    ObjectCodeHandler oo;
    vector<string> aa = oo.getObjectProgram();
    for(int i = 0; i < aa.size(); i++){
        cout << aa[i] << endl;
    }

    cin >> in;



    return 0;
}
