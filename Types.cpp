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
    if(!isAlphaOrUnderscore(word[0])) {
        return false;
    }
    for (int i = 1; i < word.length(); ++i) {
        if (!isAlphaOrUnderscore(word[i]) && !isDigit(word[i])) {
            return false;
        }
    }
    return true;
}

bool isConstant(string word) {
    for (int i = 0; i < word.length(); ++i) {
        if (!isDigit(word[i]) && !(word[i] == '-' && i == 0)) {
            return false;
        }
    }
    return true;
}

bool isAlphaOrUnderscore(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
}

bool isDigit(char c)
{
    return '0' <= c && c <= '9';
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
        case IFGOTO:
            SolveIFGOTO(context);
            break;
        case ADD:
            SolveOPERATOR(context, [](int& a, int& b) { return a + b; });
            break;
        case EQ:
            SolveOPERATOR(context, [](int& a, int& b) { return a == b; });
            break;
        case LT:
            SolveOPERATOR(context, [](int& a, int& b) { return a < b; });
            break;
        case GT:
            SolveOPERATOR(context, [](int& a, int& b) { return a > b; });
            break;
        case LTE:
            SolveOPERATOR(context, [](int& a, int& b) { return a <= b; });
            break;
        case GTE:
            SolveOPERATOR(context, [](int& a, int& b) { return a >= b; });
            break;
        case NEQ:
            SolveOPERATOR(context, [](int& a, int& b) { return a != b; });
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
    if(isConstant(value)) {
        try{
            int ivalue = stoi(value);
            context.variables[variableName] = ivalue;
        }
        catch(exception& e) {
            cout << "Error: value is not an integer\n";
            return;
        }
    }
    else if(isVariable(value) && context.variables.find(value) != context.variables.end()) {
        context.variables[variableName] = context.variables[value];
    }
    else {
        cout << "Error: Invalid value for SET command.\n";
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
    if(isConstant(context.tokens[2]))
    {
        try {
            index = stoi(context.tokens[2]);
        } catch (exception& e) {
            cout << "Error: Index is not a valid integer.\n";
            return;
        }
    }
    else if(isVariable(context.tokens[2]) && context.variables.find(context.tokens[2]) != context.variables.end())
    {
        index = context.variables[context.tokens[2]];
    }
    else
    {
        cout << "Error: Index is not a validvariable.\n";
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

    if(isConstant(context.tokens[3]))
    {
        try {
            index = stoi(context.tokens[3]);
        } catch (exception& e) {
            cout << "Error: Index is not a valid integer.\n";
            return;
        }
    }
    else if(isVariable(context.tokens[3]) && context.variables.find(context.tokens[3]) != context.variables.end())
    {
        index = context.variables[context.tokens[3]];
    }
    else
    {
        cout << "Error: Index is not a validvariable.\n";
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
/*
IFGOTO <variable> <label>  
GT
GTE
LT
LTE
*/
void SolveIFGOTO(Context& context)
{
    string variableName = context.tokens[1];
    string labelName = context.tokens[2];

    if(variableName.empty()) {
        cout << "Error: IFGOTO command requires a valid variable name.\n";
        return;
    }
    if(labelName.empty()) {
        cout << "Error: IFGOTO command requires a valid label name.\n";
        return;
    }
    if(context.variables.find(variableName) == context.variables.end()) {
        cout << "Error: Variable does not exist.\n";
        return;
    }
    if(context.labels.find(labelName) == context.labels.end()) {
        cout << "Error: Label does not exist.\n";
        return;
    }
    if(context.variables[variableName] > 0)
    {
        context.lineCounter = context.labels[labelName]; // Jump to the line number of the label
    }
}
void SolveOPERATOR(Context& context, std::function<int(int&, int&)> func)
{
    string resultVar = context.tokens[1];
    string varA = context.tokens[2];
    string varB = context.tokens[3];

    int valueA, valueB;

    if(!isVariable(resultVar)) {
        cout << "Error: OPERATOR command requires valid variable names.\n";
        return;
    }

    if(isVariable(varA))
    {
        if(context.variables.find(varA) == context.variables.end()) {
            cout << "Error: First variable does not exist.\n";
            return;
        }
        valueA = context.variables[varA];
    }
    else if(isConstant(varA))
    {
        try {
            valueA = stoi(varA);
        } catch (exception& e) {
            cout << "Error: First variable is not a valid integer.\n";
            return;
        }
    }
    else
    {
        cout << "Error: First variable is not valid.\n";
        return;
    }

    if(isVariable(varB))
    {
        if(context.variables.find(varB) == context.variables.end()) {
            cout << "Error: First variable does not exist.\n";
            return;
        }
        valueB = context.variables[varB];
    }
    else if(isConstant(varB))
    {
        try {
            valueB = stoi(varB);
        } catch (exception& e) {
            cout << "Error: Second variable is not a valid integer.\n";
            return;
        }
    }
    else
    {
        cout << "Error: Second variable is not valid.\n";
        return;
    }

    context.variables[resultVar] = func(valueA, valueB);
}