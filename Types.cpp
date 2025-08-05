#include "Types.hpp"
#include<bits/stdc++.h>
#include<cstring>
using namespace std;

const int nrOfKeywords = 4;
const char* keywords[] = {"SET","ADD","PRINT","READ"};

Type detType(string word) {
    if (isKeyword(word)) {
        return KEYWORD;
    } else if (isVariable(word)) {
        return VARIABLE;
    } else if (isConstant(word)) {
        return CONSTANT;
    } else {
        return Type::UNKNOWN;
    }
}

bool isKeyword(string word) {
    for (int i = 0; i < nrOfKeywords; ++i) {
        if (word == keywords[i]) {
            return true;
        }
    }
    return false;
}

bool isVariable(string word) {
    if ('0' <= word[0] && word[0] <= '9') {
        return false;
    }
    for (int i = 1; i < word.length(); ++i) {
        if(word[i] == '\n')
            continue;
        if (!('a' <= word[i] && word[i] <= 'z') &&
            !('A' <= word[i] && word[i] <= 'Z') &&
            !('0' <= word[i] && word[i] <= '9') &&
            word[i] != '_') {
            return false;
        }
    }
    return true;
}

bool isConstant(string word) {
    for (int i = 0; i < word.length(); ++i) {
        if(word[i] == '\n')
            continue;
        if (!('0' <= word[i] && word[i] <= '9')) {
            return false;
        }
    }
    return true;
}

Keyword FindKeyword(string token) {
    for (int i = 0; i < nrOfKeywords; ++i) {
        if (token== keywords[i]) {
            return (Keyword)i;
        }
    }
    return UNKNOWNKEYWORD;
}

void HandleKeyword(unordered_map<string, int>& variables, vector<string>& tokens) {
    Keyword foundKeyword = FindKeyword(tokens[0]);
    switch (foundKeyword) {
        case SET:
            SolveSET(variables, tokens);
            break;
        case ADD:
            SolveADD(variables, tokens);
            break;
        case PRINT:
            SolvePRINT(variables, tokens);
            break;
        case READ:
            SolveREAD(variables, tokens);
            break;
        default:
            cout << "Unknown keyword/n";
    }
}

void HandleVariable(string token) {
    cout << "VARIABLE: " << token << endl;
}

void HandleConstant(string token) {
    cout << "CONSTANT: " << token << endl;
}

void SolveSET(unordered_map<string, int>& variables, vector<string>& tokens)
{
    string variableName = tokens[1];
    string value = tokens[2];

    if(variableName.empty()) {
        cout << "Error: SET command requires a valid variable name.\n";
        return;
    }

    try{
        int ivalue = stoi(value);
        variables[variableName] = ivalue;
    }
    catch(exception& e) {
        cout << "Error: value is not an integer\n";
        return;
    }
    return;
}

void SolveADD(unordered_map<string, int>& variables, vector<string>& tokens)
{
    string variableName = tokens[1];
    string value = tokens[2];

    if(variableName.empty()) {
        cout << "Error: ADD command requires a valid variable name.\n";
        return;
    }
    if(isVariable(value))
    {
        variables[variableName] += variables[value];
    }
    else if(isConstant(value))
    {
        try {
            int ivalue = stoi(value);
            variables[variableName] += ivalue;
        } catch (exception& e) {
            cout << "Error: value is not an integer\n";
            return;
        }
    }
    else
    {
        cout << "Error: Invalid value for ADD command.\n";
        return;
    }
    return;
}

void SolvePRINT(unordered_map<string, int>& variables, vector<string>& tokens)
{
    string variableName = tokens[1];

    if(variableName.empty()) {
        cout << "Error: PRINT command requires a valid variable name.\n";
        return;
    }   
    cout<<variables[variableName]<<"\n";
    return;
}

void SolveREAD(unordered_map<string, int>& variables, vector<string>& tokens)
{
    string variableName = tokens[1];

    if(variableName.empty()) {
        cout << "Error: READ command requires a valid variable name.\n";
        return;
    }
    int ivalue;
    cin>>ivalue;

    variables[variableName] = ivalue;
    return;
}