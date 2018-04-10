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
#include <sstream>

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

struct ASTNode;

union NodeData{
    fraction frac;
    double real;
    pair<ASTNode*,ASTNode*> node;

    NodeData(){
        real=0;
    }
};

struct ASTNode {
    ASTNodeType type;
    NodeData data;

    ASTNode(){
        type = TYPE_DOUBLE;
    }

    ~ASTNode(){
        if(type!=TYPE_FRACTION&&type!=TYPE_DOUBLE) {
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
            node->type = TYPE_DOUBLE;
            double base = pow(10,node->precision);
            node->data.real = floor((rand()/(double)RAND_MAX)*global_setting.max_num*base)/base;
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
            if(mode==MODE_FRACTION) num2->data.frac = fraction(rand()%4+1);
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
            break;
        case TYPE_ADD:
            temp_a = calc_asttree(root->data.node.first);
            temp_b = calc_asttree(root->data.node.second);
            if (temp_a->type == TYPE_FRACTION && temp_b->type == TYPE_FRACTION) {
                result->type = TYPE_FRACTION;
                result->data.frac = temp_a->data.frac + temp_b->data.frac;

            }
            else {
                result->type = TYPE_DOUBLE;
                double a, b;
                if(temp_a->type == TYPE_FRACTION) {
                    a = (double)temp_a->data.frac.numerator / (double)temp_a->data.frac.denominator;
                } else if(temp_a->type == TYPE_DOUBLE){
                    a = temp_a->data.real;
                }
                if(temp_b->type == TYPE_FRACTION) {
                    b = (double)temp_b->data.frac.numerator / (double)temp_b->data.frac.denominator;
                } else if(temp_b->type == TYPE_DOUBLE){
                    b = temp_b->data.real;
                }
                result->data.real = a + b;
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
                double a, b;
                if(temp_a->type == TYPE_FRACTION) {
                    a = (double)temp_a->data.frac.numerator / (double)temp_a->data.frac.denominator;
                } else if(temp_a->type == TYPE_DOUBLE){
                    a = temp_a->data.real;
                }
                if(temp_b->type == TYPE_FRACTION) {
                    b = (double)temp_b->data.frac.numerator / (double)temp_b->data.frac.denominator;
                } else if(temp_b->type == TYPE_DOUBLE){
                    b = temp_b->data.real;
                }
                result->data.real = a - b;
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
                double a, b;
                if(temp_a->type == TYPE_FRACTION) {
                    a = (double)temp_a->data.frac.numerator / (double)temp_a->data.frac.denominator;
                } else if(temp_a->type == TYPE_DOUBLE){
                    a = temp_a->data.real;
                }
                if(temp_b->type == TYPE_FRACTION) {
                    b = (double)temp_b->data.frac.numerator / (double)temp_b->data.frac.denominator;
                } else if(temp_b->type == TYPE_DOUBLE){
                    b = temp_b->data.real;
                }
                result->data.real = a * b;
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
                double a, b;
                if(temp_a->type == TYPE_FRACTION) {
                    a = (double)temp_a->data.frac.numerator / (double)temp_a->data.frac.denominator;
                } else if(temp_a->type == TYPE_DOUBLE){
                    a = temp_a->data.real;
                }
                if(temp_b->type == TYPE_FRACTION) {
                    b = (double)temp_b->data.frac.numerator / (double)temp_b->data.frac.denominator;
                } else if(temp_b->type == TYPE_DOUBLE){
                    b = temp_b->data.real;
                }
                result->data.real = a / b;
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
                double a, b;
                if(temp_a->type == TYPE_FRACTION) {
                    a = (double)temp_a->data.frac.numerator / (double)temp_a->data.frac.denominator;
                } else if(temp_a->type == TYPE_DOUBLE){
                    a = temp_a->data.real;
                }
                if(temp_b->type == TYPE_FRACTION) {
                    b = (double)temp_b->data.frac.numerator / (double)temp_b->data.frac.denominator;
                } else if(temp_b->type == TYPE_DOUBLE){
                    b = temp_b->data.real;
                }
                result->data.real = powl(a, b);
            }
            break;
    }
    delete temp_a;
    delete temp_b;
    return result;
}

void ast_output(ASTNode* root){
    stringstream ss;
    switch(root->type){
        case TYPE_FRACTION:
            ss<<root->data.frac.numerator;
            if(root->data.frac.denominator!=1){
                ss<<"/"<<root->data.frac.denominator;
            }
            break;
        case TYPE_DOUBLE:
            break;
        default:

            break;
    }
}

// todo
void Setting(){

}

// Calc()
map<string,string> table;
string Calc(){

}

// for unit test
int main() {

    auto x = random_ast(MODE_REAL);
    auto res = calc_asttree(x);
    cout<<res->data.real<<endl;

    return 0;
}
