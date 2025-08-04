#include "Types.hpp"
#include<bits/stdc++.h>
#include<cstring>
using namespace std;

const int nrOfKeywords = 4;
const char* keywords[] = {"SET","ADD","PRINT","READ"};

Type detType(char* word) {
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

bool isKeyword(char* word) {
    for (int i = 0; i < nrOfKeywords; ++i) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool isVariable(char* word) {
    if ('0' <= word[0] && word[0] <= '9') {
        return false;
    }
    for (int i = 1; i < strlen(word); ++i) {
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

bool isConstant(char* word) {
    for (int i = 0; i < strlen(word); ++i) {
        if(word[i] == '\n')
            continue;
        if (!('0' <= word[i] && word[i] <= '9')) {
            return false;
        }
    }
    return true;
}

Keyword FindKeyword(char* token) {
    for (int i = 0; i < nrOfKeywords; ++i) {
        if (strcmp(token, keywords[i]) == 0) {
            return (Keyword)i;
        }
    }
    return UNKNOWNKEYWORD;
}

void HandleKeyword(unordered_map<char*, int>& variables, char* token) {
    Keyword foundKeyword = FindKeyword(token);
    switch (foundKeyword) {
        case SET:
            SolveSET(variables);
            break;
        case ADD:
            SolveADD(variables);
            break;
        case PRINT:
            SolvePRINT(variables);
            break;
        case READ:
            SolveREAD(variables);
            break;
        default:
            cout << "Unknown keyword/n";
    }
}

void HandleVariable(char* token) {
    cout << "VARIABLE: " << token << endl;
}

void HandleConstant(char* token) {
    cout << "CONSTANT: " << token << endl;
}

void SolveSET(unordered_map<char*, int>& variables)
{
    char* variableName = strtok(NULL, delimiter);
    char* value = strtok(NULL, delimiter);

    if(value[strlen(variableName) - 1] == '\n') {
        value[strlen(variableName) - 1] = '\0'; 
    }

    if(variableName == NULL) {
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

void SolveADD(unordered_map<char*, int>& variables)
{
    char* variableName = strtok(NULL, delimiter);
    char* value = strtok(NULL, delimiter);

    if(value[strlen(variableName) - 1] == '\n') {
        value[strlen(variableName) - 1] = '\0'; 
    }

    if(variableName == NULL) {
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

void SolvePRINT(unordered_map<char*, int>& variables)
{
    char* variableName = strtok(NULL, delimiter);

    if(variableName[strlen(variableName) - 1] == '\n') {
        variableName[strlen(variableName) - 1] = '\0'; 
    }

    if(variableName == NULL) {
        cout << "Error: PRINT command requires a valid variable name.\n";
        return;
    }   
    cout<<variables[variableName]<<"\n";
    return;
}

void SolveREAD(unordered_map<char*, int>& variables)
{
    char* variableName = strtok(NULL, delimiter);

    if(variableName[strlen(variableName) - 1] == '\n') {
        variableName[strlen(variableName) - 1] = '\0'; 
    }
    
    if(variableName == NULL) {
        cout << "Error: READ command requires a valid variable name.\n";
        return;
    }
    int ivalue = 2;
    //cin>>ivalue;

    variables[variableName] = ivalue;
    cout<<variableName<<"g\n";
    return;
}