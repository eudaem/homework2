/*
 * core.cpp
 * author:
 *   PB16120853  赵瑞
 *   JL17110067  隆晋威
 * date:
 *  2018/4/5
 */ 

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <cstring>
#include <cstdio>
#include <list>
#include <tuple>

using namespace std;

enum ASTNodeType {TYPE_ADD,TYPE_MINUS,TYPE_MUL,TYPE_DIV,TYPE_POWER,TYPE_FRACTION,TYPE_DOUBLE};

struct ASTNode {
    ASTNodeType type;
    union {
        fraction frac;
        double real;
        pair<shared_ptr<ASTNode>,shared_ptr<ASTNode>> node;                
    } data;
};


shared_ptr<ASTNode> parse(const char* p) {
    
}

struct token { 
    bool is_operator;
    int l,r;

    token(){}
    token(bool is_operator,int l,int r){
        this->is_operator = is_operator;
        this->l = l;
        this->r = r;
    }
};

struct Tokenizer{
    char* str;
    list<token> tokens;

    const char* operators = "()+-*/^\0"
    bool is_operator(char ch){
        char* p = operators;
        while(*p){
            if(*p==ch) return true;
            p++;
        }
        return false;
    }

    void tokenize() const{
        int pos=0;
        while(str[pos]) {
            if(is_operator(str[pos])){
                tokens.append(token{true,pos,pos+1});
            }else if(str[pos]>='0' && str[pos]<='9'){
                
            }

            pos++;
        }
    }
};

void Calc(const string& in) {

}

// for unit test
int main()
{

}