#include<unordered_map>
#include<string>
#include<vector>
using std::string;
using std::vector;
using std::unordered_map;
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
    ARRAY,
    SETINDEX,
    GETINDEX,
    UNKNOWNKEYWORD
};
const string keywords[] = {"SET","ADD","PRINT","READ","ARRAY","SETINDEX","GETINDEX"};
const int nrOfKeywords = 8;
const string delimiter = " /n/t";

class Context
{
    public:
    unordered_map<string, int> variables;
    unordered_map<string, vector<int>> arrays;
    vector<string> tokens;
};

Type detType(string word);
Keyword HandleKeyword(string token);

bool isKeyword(string word);
bool isVariable(string word);
bool isConstant(string word);

void HandleKeyword(Context& context);
void HandleVariable(string token);
void HandleConstant(string token);

void SolveSET(Context& context);
void SolveADD(Context& context);
void SolvePRINT(Context& context);
void SolveREAD(Context& context);
void SolveARRAY(Context& context);
void SolveSETINDEX(Context& context);
void SolveGETINDEX(Context& context);