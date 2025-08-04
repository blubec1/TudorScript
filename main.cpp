#include<bits/stdc++.h>
#include<cstring>
#include<cstdio>
#include "Types.hpp"
using namespace std;

const int nrOfCharactersperLine = 100;
FILE* fptr;
char* path;
char buffer[nrOfCharactersperLine];
unordered_map<char* , int> variables;

int main(int argc, char *argv[])
{
    /*
    if(argc == 1)
    {
        cout<<"Insuficient arguments";
        return -2;
    }
    */

    //path = argv[1];
    path = "test.tdsp";
    fptr = fopen(path, "r");
    
    if(!fptr)
    {
        cout<<"File doesn't exist";
        return -1;
    }

    //main loop function
    while(fgets(buffer,nrOfCharactersperLine,fptr) != NULL)
    {

        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character if present
        buffer[strcspn(buffer, "\r")] = 0; // Remove carriage return
        char* token;
        token = strtok(buffer, delimiter);

        while(token != NULL)
        {
            Type wordType = detType(token);

            switch(wordType)
            {
                case KEYWORD:
                    HandleKeyword(variables, token);
                    break;
                case VARIABLE:
                    HandleVariable(token);  
                    break;
                case CONSTANT:
                    HandleConstant(token);
                    break;
                default:
                    cout<<"Unknown type for word:"<<token<<endl;
            }
            token = strtok(NULL, delimiter);
        }
        cout<<"\n";
    }

}