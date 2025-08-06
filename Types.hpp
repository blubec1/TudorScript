#include<unordered_map>
#include<string>
#include<vector>
#include<functional>
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
    LABEL,
    GOTO,
    IFGOTO,
    EQ,
    LT,
    GT,
    LTE,
    GTE,
    NEQ,
    UNKNOWNKEYWORD
};
const string keywords[] = {"SET","ADD","PRINT","READ","ARRAY","SETINDEX","GETINDEX","LABEL","GOTO","IFGOTO","EQ","LT","GT","LTE","GTE","NEQ"};
const int nrOfKeywords = 16;
const string delimiter = " /n/t";

class Context
{
    public:
    int lineCounter = 0;
    unordered_map<string, int> variables;
    unordered_map<string, vector<int>> arrays;
    unordered_map<string, int> labels; // For future label handling
    vector<string> tokens;
    vector<vector<string>> lines; // To store lines of code if needed
};

Type detType(string word);
Keyword HandleKeyword(string token);

bool isKeyword(string word);
bool isVariable(string word);
bool isConstant(string word);

void HandleKeyword(Context& context);
void PreprocessKeywords(Context& context);
void HandleVariable(string token);
void HandleConstant(string token);

void SolveSET(Context& context);
void SolveADD(Context& context);
void SolvePRINT(Context& context);
void SolveREAD(Context& context);
void SolveARRAY(Context& context);
void SolveSETINDEX(Context& context);
void SolveGETINDEX(Context& context);
void SolveLABEL(Context& context);
void SolveGOTO(Context& context);
void SolveIFGOTO(Context& context);
void SolveOPERATOR(Context& context, std::function<int(int&, int&)> func);