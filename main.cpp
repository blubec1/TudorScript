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
    //read everything into lines
    while(fgets(buffer,maxCharactersperLine,fptr))
    {
        Tokenize(buffer, context.tokens);
        PreprocessKeywords(context);
        context.lines.push_back(context.tokens);
        context.tokens.clear();
        context.lineCounter++;
    }

    context.lineCounter = 0; // Reset line counter for processing
    while(context.lineCounter < context.lines.size())
    {
        context.tokens = context.lines[context.lineCounter];
        if(context.tokens.empty()) continue; // Skip empty lines
        Type wordType = detType(context.tokens[0]);
        HandleKeyword(context);
        context.lineCounter++;
    }
    fclose(fptr);

}
