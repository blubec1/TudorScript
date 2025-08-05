#include<bits/stdc++.h>
#include<cstring>
#include<cstdio>
#include "Types.hpp"
using namespace std;

const int maxCharactersperLine = 100;
FILE* fptr;
const char* path;
char* buffer;

void Tokenize(string buffer, vector<string>& tokens)
{
    string token;
    istringstream stream(buffer);
    while (stream >> token) {
        tokens.push_back(token);
    }
}

int main(int argc, char *argv[])
{
    /*
    if(argc == 1)
    {
        cout<<"Insuficient arguments";
        return -2;
    }
    */
    vector<string> tokens;
    unordered_map<string, int> variables;
    buffer = new char[maxCharactersperLine];
    tokens.reserve(maxCharactersperLine);
    //path = argv[1];
    path = "test.tdsp";
    fptr = fopen(path, "r");

    if(!fptr)
    {
        cout<<"File doesn't exist";
        return -1;
    }
    //main loop function
    while(fgets(buffer,maxCharactersperLine,fptr))
    {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character if present
        buffer[strcspn(buffer, "\r")] = 0; // Remove carriage return
        tokens.clear();

        Tokenize(buffer, tokens);

        Type wordType = detType(tokens[0]);

        switch(wordType)
        {
            case KEYWORD:
                HandleKeyword(variables, tokens);
                break;
            /*    
            case VARIABLE:
                HandleVariable(token);  
                break;
             case CONSTANT:
                HandleConstant(token);
                break;
            */
            default:
                cout<<"Unknown type for word:"<<endl;
        }
    }
    fclose(fptr);

}
