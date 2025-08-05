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
    Context context;
    buffer = new char[maxCharactersperLine];
    context.tokens.reserve(maxCharactersperLine);
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
        context.tokens.clear();

        Tokenize(buffer, context.tokens);

        Type wordType = detType(context.tokens[0]);
        HandleKeyword(context);
    }
    fclose(fptr);

}
