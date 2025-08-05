#include "Types.hpp"
#include<bits/stdc++.h>
#include<cstring>
using namespace std;

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

void HandleKeyword(unordered_map<string, vector<int>>& arrays, unordered_map<string, int>& variables, vector<string>& tokens) {
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
        case ARRAY:
            SolveARRAY(arrays, tokens);
            break;
        case SETINDEX:
            SolveSETINDEX(arrays, variables, tokens);
            break;
        case GETINDEX:
            SolveGETINDEX(arrays, variables, tokens);
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

void SolveARRAY(unordered_map<string, vector<int>>& arrays, vector<string>& tokens)
{
    string arrayName = tokens[1];
    int size;
    try {
        size = stoi(tokens[2]);
    } catch (exception& e) {
        cout << "Error: Size is not a valid integer.\n";
        return;
    }

    arrays[arrayName] = vector<int>(size, 0); // Initialize array with zeros
}

void SolveSETINDEX(unordered_map<string, vector<int>>& arrays, unordered_map<string, int>& variables, vector<string>& tokens)
{
    string arrayName = tokens[1];
    int index;
    try {
        index = stoi(tokens[2]);
    } catch (exception& e) {
        cout << "Error: Index is not a valid integer.\n";
        return;
    }

    string value = tokens[3];
    
    if(arrays.find(arrayName) == arrays.end()) {
        cout << "Error: Array does not exist.\n";
        return;
    }
    
    if(index < 0 || index >= arrays[arrayName].size()) {
        cout << "Error: Index out of bounds.\n";
        return;
    }

    if(value.empty()) {
        cout << "Error: SETINDEX command requires a valid array name.\n";
        return;
    }

    if(isVariable(value) && variables.find(value) != variables.end())
    {
        arrays[arrayName][index] = variables[value];
        return;
    }
    else if(isConstant(value))
    {
        try{
            int ivalue = stoi(value);
            arrays[arrayName][index] = ivalue;
        }
        catch (exception& e) {
            cout << "Error: Value is not a valid integer.\n";
        }
        return;
    }
}

void SolveGETINDEX(unordered_map<string, vector<int>>& arrays, unordered_map<string, int>& variables, vector<string>& tokens)
{

    string arrayName = tokens[1];
    string variableName = tokens[2];
    int index;
    try {
        index = stoi(tokens[3]);
    } catch (exception& e) {
        cout << "Error: Index is not a valid integer.\n";
        return;
    }

    if(arrays.find(arrayName) == arrays.end()) {
        cout << "Error: Array does not exist.\n";
        return;
    }
    
    if(index < 0 || index >= arrays[arrayName].size()) {
        cout << "Error: Index out of bounds.\n";
        return;
    }

    variables[variableName] = arrays[arrayName][index];

}