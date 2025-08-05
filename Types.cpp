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

void PreprocessKeywords(Context& context) {
    Keyword foundKeyword = FindKeyword(context.tokens[0]);
    switch(foundKeyword) {
        case LABEL:
            SolveLABEL(context);
            break;
    }
}

void HandleKeyword(Context& context) 
{
    Keyword foundKeyword = FindKeyword(context.tokens[0]);
    switch (foundKeyword) {
        case SET:
            SolveSET(context);
            break;
        case ADD:
            SolveADD(context);
            break;
        case PRINT:
            SolvePRINT(context);
            break;
        case READ:
            SolveREAD(context);
            break;
        case ARRAY:
            SolveARRAY(context);
            break;
        case SETINDEX:
            SolveSETINDEX(context);
            break;
        case GETINDEX:
            SolveGETINDEX(context);
            break;
        case LABEL:
            // Labels are preprocessed and not handled here.
            break;
        case GOTO:
            SolveGOTO(context);
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

void SolveSET(Context& context)
{
    string variableName = context.tokens[1];
    string value = context.tokens[2];

    if(variableName.empty()) {
        cout << "Error: SET command requires a valid variable name.\n";
        return;
    }

    try{
        int ivalue = stoi(value);
        context.variables[variableName] = ivalue;
    }
    catch(exception& e) {
        cout << "Error: value is not an integer\n";
        return;
    }
    return;
}

void SolveADD(Context& context)
{
    string variableName = context.tokens[1];
    string value = context.tokens[2];

    if(variableName.empty()) {
        cout << "Error: ADD command requires a valid variable name.\n";
        return;
    }
    if(isVariable(value))
    {
        context.variables[variableName] += context.variables[value];
    }
    else if(isConstant(value))
    {
        try {
            int ivalue = stoi(value);
            context.variables[variableName] += ivalue;
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

void SolvePRINT(Context& context)
{
    string variableName = context.tokens[1];

    if(variableName.empty()) {
        cout << "Error: PRINT command requires a valid variable name.\n";
        return;
    }   
    cout<<context.variables[variableName]<<"\n";
    return;
}

void SolveREAD(Context& context)
{
    string variableName = context.tokens[1];

    if(variableName.empty()) {
        cout << "Error: READ command requires a valid variable name.\n";
        return;
    }
    int ivalue;
    cin>>ivalue;

    context.variables[variableName] = ivalue;
    return;
}

void SolveARRAY(Context& context)
{
    string arrayName = context.tokens[1];
    int size;
    try {
        size = stoi(context.tokens[2]);
    } catch (exception& e) {
        cout << "Error: Size is not a valid integer.\n";
        return;
    }

    context.arrays[arrayName] = vector<int>(size, 0); // Initialize array with zeros
}

void SolveSETINDEX(Context& context)
{
    string arrayName = context.tokens[1];
    int index;
    try {
        index = stoi(context.tokens[2]);
    } catch (exception& e) {
        cout << "Error: Index is not a valid integer.\n";
        return;
    }

    string value = context.tokens[3];
    
    if(context.arrays.find(arrayName) == context.arrays.end()) {
        cout << "Error: Array does not exist.\n";
        return;
    }
    
    if(index < 0 || index >= context.arrays[arrayName].size()) {
        cout << "Error: Index out of bounds.\n";
        return;
    }

    if(value.empty()) {
        cout << "Error: SETINDEX command requires a valid array name.\n";
        return;
    }

    if(isVariable(value) && context.variables.find(value) != context.variables.end())
    {
        context.arrays[arrayName][index] = context.variables[value];
        return;
    }
    else if(isConstant(value))
    {
        try{
            int ivalue = stoi(value);
            context.arrays[arrayName][index] = ivalue;
        }
        catch (exception& e) {
            cout << "Error: Value is not a valid integer.\n";
        }
        return;
    }
}

void SolveGETINDEX(Context& context)
{

    string arrayName = context.tokens[1];
    string variableName = context.tokens[2];
    int index;
    try {
        index = stoi(context.tokens[3]);
    } catch (exception& e) {
        cout << "Error: Index is not a valid integer.\n";
        return;
    }

    if(context.arrays.find(arrayName) == context.arrays.end()) {
        cout << "Error: Array does not exist.\n";
        return;
    }
    
    if(index < 0 || index >= context.arrays[arrayName].size()) {
        cout << "Error: Index out of bounds.\n";
        return;
    }

    context.variables[variableName] = context.arrays[arrayName][index];

}

void SolveLABEL(Context& context)
{
    string labelName = context.tokens[1];
    if(labelName.empty()) {
        cout << "Error: LABEL command requires a valid label name.\n";
        return;
    }
    context.labels[labelName] = context.lineCounter; // Store the line number for the label
}

void SolveGOTO(Context& context)
{
    string labelName = context.tokens[1];
    if(labelName.empty()) {
        cout << "Error: GOTO command requires a valid label name.\n";
        return;
    }

    context.lineCounter = context.labels[labelName]; // Jump to the line number of the label
}