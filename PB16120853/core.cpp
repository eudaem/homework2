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
#include <limits.h>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

/*
 * fraction 
 */
class fraction;
bool is_bad_value(const fraction& x);
bool is_bad_value(const double& x);

class fraction {
private:
    long gcd(long u, long v) {
        if (!(u&&v)) {
            return 1;
        }
        while (v != 0){
            long r = u % v;
            u = v;
            v = r;
        }
        return u;
    }
public:
	long numerator, denominator;

	fraction(long m = 1, long n = 1) {
		this->numerator = m;
		this->denominator = n;
	}

	void reduction() {
		long x = gcd(this->numerator, this->denominator);
		this->numerator /= x;
		this->denominator /= x;
		if (this->denominator < 0) {
			this->numerator *= -1;
			this->denominator *= -1;
		}
		if (!this->numerator) {
			this->denominator = 1;
		}
		if (!this->denominator) {
			this->numerator = 1;
		}
		return;
	}

	fraction operator + (const fraction x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.denominator + this->denominator * x.numerator;
		result.denominator = this->denominator * x.denominator;
		result.reduction();
		return result;
	}


	fraction operator - (const fraction& x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.denominator - this->denominator * x.numerator;
		result.denominator = this->denominator * x.denominator;
		result.reduction();
		return result;
	}

	fraction operator * (const fraction& x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.numerator;
		result.denominator = this->denominator * x.denominator;
		result.reduction();
		return result;
	}

	fraction operator / (const fraction& x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;
		fraction result;
		result.numerator = this->numerator * x.denominator;
		result.denominator = this->denominator * x.numerator;
		result.reduction();
		return result;
	}

	fraction operator ^ (fraction x) const {
		if (is_bad_value(*this))return *this;
		if (is_bad_value(x))return x;

		x.reduction();
		if (x.denominator != 1) {
			fraction bad_value;
			bad_value.numerator = 1;
			bad_value.denominator = 0;
			return bad_value;
		}
		long index = x.numerator;

		fraction result;
		result.numerator = powl(this->numerator, abs(index));
		result.denominator = powl(this->denominator, abs(index));
		if (index < 0) {
			long temp;
			temp = result.numerator;
			result.numerator = result.denominator;
			result.denominator = temp;
		}
		result.reduction();
		return result;
	}
};

/*
 * unit test for fraction
 */
void fraction_test() {
	fraction a(1, 0), b(0, 1), c(2, 3), d(5, 6), e(8, 4), g(18, 9);
	fraction x;
	x = a + b;
	x = a * b;
	x = a - b;
	x = a / b;
	x = a / c;
	x = a + c;
	x = a * c;
	x = a - c;
	x = b + c;
	x = b - c;
	x = b * c;
	x = b / c;
	x = c * d;
	x = c / d;
	x = c + d;
	x = c - d;
	x = a ^ b;
	x = a ^ c;
	x = a ^ d;
	x = a ^ e;
	x = a ^ g;
	x = b ^ c;
	x = b ^ a;
	x = b ^ d;
	x = b ^ e;
	x = b ^ g;
	x = e * g;
	x = e - g;
	x = e + g;
	x = e / g;
}

/*
 * is_bad_value
 */
bool is_bad_value(const fraction& x) {
	if (!x.denominator) {
		return true;
	}
	else {
		return false;
	}
}

bool is_bad_value(const double& x) {
	if (isnan(x) || isfinite(x) || isinf(x)) {
		return true;
	}
	else {
		return false;
	}
}

/*
 * AST
 */
enum ASTNodeType {TYPE_ADD=0,TYPE_MINUS=1,TYPE_MUL=2,TYPE_DIV=3,TYPE_POWER=4,TYPE_FRACTION=5,TYPE_DOUBLE=6};

struct ASTNode {
    ASTNodeType type;
    union {
        fraction frac;
        double real;
        pair<ASTNode*,ASTNode*> node;                
    } data;

    ASTNode(){
        type = TYPE_DOUBLE;
        data.real = 0;
    }

    ~ASTNode(){
        if(type!=TYPE_FRACTION&&type!=TYPE_DOUBLE){
            delete data.node.first;
            delete data.node.second;
        }
    }
};


/*
 * settings and random ast
 */ 
struct settings {
    int max_opearators=5;
    long max_range=1000;
    long max_num = 50;
    int precision=2;
    bool has_fraction=true;
    bool has_real=true;
};
enum cal_mode{MODE_FRACTION,MODE_REAL};
settings global_setting;

inline ASTNode* random_value(cal_mode mode){
    ASTNode* node = new ASTNode();
    switch(mode){
        case MODE_FRACTION:
            node->type = TYPE_FRACTION;
            node->data.frac = fraction(rand()%global_setting.max_num);
            break;

        case MODE_REAL:
			// todo: precision
	        node->type = TYPE_DOUBLE;
            node->data.real = (rand()/(double)RAND_MAX)*global_setting.max_num;
            break;
    }
    return node;
}

ASTNode* random_ast(cal_mode mode){
    int n = rand()%(global_setting.max_opearators-2)+2;
	ASTNode* num1 = random_value(mode);
	for(int i=0;i<n;i++){
		ASTNode* num2 = random_value(mode);
		if(rand()%2) swap(num1,num2);
		int r = rand()%17;
		ASTNode* new_node = new ASTNode();

		if(r==16){
			if(mode==MODE_FRACTION) num2->data.frac = fraction(rand()%2+1); 
			else num2->data.real = rand()%2+2;

			new_node->type = TYPE_POWER;
			new_node->data.node = make_pair(num1,num2);
		}else{
			new_node->type = (ASTNodeType)(r/4);			
			new_node->data.node = make_pair(num1,num2);
		}

		num1 = new_node;
	}
	return num1;
}

/*
 * Tokenizer
 */
enum token_type{TOKEN_OPERATOR,TOKEN_INT,TOKEN_DOUBLE};
struct token { 
    token_type type;
    int l,r;

    token(){}
    token(token_type type,int l,int r){
        this->type = type;
        this->l = l;
        this->r = r;
    }
};

struct Tokenizer {
    const char* str;
    list<token> tokens;

    Tokenizer(){}
    Tokenizer(const char* s){
        str = s;
    }   

    const char* operators = "()+-*/^\0";

    bool is_operator(char ch) const{
        const char* p = operators;
        while(*p){
            if(*p==ch) return true;
            p++;
        }
        return false;
    }

    bool tokenize(){
        int pos=0;
        while(str[pos]) {
            if(is_operator(str[pos])){
                tokens.push_back(token{TOKEN_OPERATOR,pos,pos+1});
                pos++;
            } else if(str[pos]>='0' && str[pos]<='9'){
                int front = pos+1;
                while(str[front]>='0' && str[front]<='9') front++;
                
                if(str[front]=='.'){
                    front++;
                    while(str[front]>='0' && str[front]<='9') front++;
                    tokens.push_back(token{TOKEN_DOUBLE,pos,front});
                }else{
                    tokens.push_back(token{TOKEN_INT,pos,front});
                }
                pos=front;
            } else if(str[pos]==' ' || str[pos]=='\t') {
                pos++;
            } else {
                return false;
            }
        }
        return true;
    }
};

/*
 * Parser
 */
struct Parser {
    Tokenizer token;
    shared_ptr<ASTNode> root;

    Parser(char*s){
        token = Tokenizer(s);
    }
};


ASTNode* calc_asttree(ASTNode* root) {
	ASTNode* result = new ASTNode();
	result->type = TYPE_FRACTION;
	result->data.frac;
	ASTNode* temp_a = new ASTNode();
	ASTNode* temp_b = new ASTNode();
	switch (root->type) {
	case TYPE_FRACTION:
		result->type = TYPE_FRACTION;
		result->data.frac = root->data.frac;
		break;
	case TYPE_DOUBLE:
		result->type = TYPE_DOUBLE;
		result->data.real = root->data.real;
	case TYPE_ADD:
		temp_a = calc_asttree(root->data.node.first);
		temp_b = calc_asttree(root->data.node.second);
		if (temp_a->type == TYPE_FRACTION && temp_b->type == TYPE_FRACTION) {
			result->type = TYPE_FRACTION;
			result->data.frac = temp_a->data.frac + temp_b->data.frac;

		}
		else {
			result->type = TYPE_DOUBLE;
			result->data.real = temp_a->data.real + temp_b->data.real;
		}
		break;
	case TYPE_MINUS:
		temp_a = calc_asttree(root->data.node.first);
		temp_b = calc_asttree(root->data.node.second);
		if (temp_a->type == TYPE_FRACTION && temp_b->type == TYPE_FRACTION) {
			result->type = TYPE_FRACTION;
			result->data.frac = temp_a->data.frac - temp_b->data.frac;

		}
		else {
			result->type = TYPE_DOUBLE;
			result->data.real = temp_a->data.real - temp_b->data.real;
		}
		break;
	case TYPE_MUL:
		temp_a = calc_asttree(root->data.node.first);
		temp_b = calc_asttree(root->data.node.second);
		if (temp_a->type == TYPE_FRACTION && temp_b->type == TYPE_FRACTION) {
			result->type = TYPE_FRACTION;
			result->data.frac = temp_a->data.frac * temp_b->data.frac;

		}
		else {
			result->type = TYPE_DOUBLE;
			result->data.real = temp_a->data.real * temp_b->data.real;
		}
		break;
	case TYPE_DIV:
		temp_a = calc_asttree(root->data.node.first);
		temp_b = calc_asttree(root->data.node.second);
		if (temp_a->type == TYPE_FRACTION && temp_b->type == TYPE_FRACTION) {
			result->type = TYPE_FRACTION;
			result->data.frac = temp_a->data.frac / temp_b->data.frac;

		}
		else {
			result->type = TYPE_DOUBLE;
			result->data.real = temp_a->data.real / temp_b->data.real;
		}
		break;
	case TYPE_POWER:
		temp_a = calc_asttree(root->data.node.first);
		temp_b = calc_asttree(root->data.node.second);
		if (temp_a->type == TYPE_FRACTION && temp_b->type == TYPE_FRACTION) {
			result->type = TYPE_FRACTION;
			result->data.frac = temp_a->data.frac ^ temp_b->data.frac;

		}
		else {
			result->type = TYPE_DOUBLE;
			result->data.real = powl(temp_a->data.real, temp_b->data.real);
		}
		break;
	}
	return result;
}




// for unit test
int main() {

}