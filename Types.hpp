#include<unordered_map>
#include<string>
#include<vector>
using std::string;
using std::vector;
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

const string delimiter = " /n/t";

Type detType(string word);
Keyword HandleKeyword(string token);

bool isKeyword(string word);
bool isVariable(string word);
bool isConstant(string word);

void HandleKeyword(std::unordered_map<string, int>& variables, vector<string>& tokens);
void HandleVariable(string token);
void HandleConstant(string token);

void SolveSET(std::unordered_map<string, int>& variables, vector<string>& tokens);
void SolveADD(std::unordered_map<string, int>& variables, vector<string>& tokens);
void SolvePRINT(std::unordered_map<string, int>& variables, vector<string>& tokens);
void SolveREAD(std::unordered_map<string, int>& variables, vector<string>& tokens);