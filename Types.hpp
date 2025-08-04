#include<unordered_map>
enum Type {
    KEYWORD,
    VARIABLE,
    CONSTANT,
    UNKNOWN
};

enum Keyword{
    SET,
    ADD,
    PRINT,
    READ,
    UNKNOWNKEYWORD
};

constexpr char* delimiter = " /n/t";

Type detType(char* word);
Keyword HandleKeyword(char* token);
bool isKeyword(char* word);
bool isVariable(char* word);
bool isConstant(char* word);
void HandleKeyword(std::unordered_map<char*, int> variables, char* token);
void HandleVariable(char* token);
void HandleConstant(char* token);
void SolveSET(std::unordered_map<char*, int>& variables);
void SolveADD(std::unordered_map<char*, int>& variables);
void SolvePRINT(std::unordered_map<char*, int>& variables);
void SolveREAD(std::unordered_map<char*, int>& variables);