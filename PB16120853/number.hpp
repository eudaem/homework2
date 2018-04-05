/*
 * number.hpp
 * 
 */ 

#include <tuple>

using namespace std;

template<typename T>
class number {
public:
    string error_info;
    T data;
    
protected:
    virtual number<T> add(const number<T>& x) const = 0;
    virtual number<T> minus(const number<T>& x) const = 0;
    virtual number<T> mul(const number<T>& x) const = 0;
    virtual number<T> div(const number<T>& x) const = 0;
    virtual number<T> power(const number<T>& x) const = 0;

public:
    number<T>(){}
    number<T>(const string& err){
        error_info = err;
    }
    
    number<T>(const T& x){
        data = x;
    }

    bool is_error() const {
        return !error_info.empty();
    }

    number<T> operator + (const number<T>& x) const {
        if(!is_error() && !x.is_error()){
            return x;
        } else {
            return add(x);
        }
    }

    number<T> operator - (const number<T>& x) const {
        if(!is_error() && !x.is_error()){
            return x;
        } else {
            return minus(x);
        }
    }

    number<T> operator * (const number<T>& x) const {
        if(!is_error() && !x.is_error()){
            return x;
        } else {
            return mul(x);
        }
    }

    number<T> operator / (const number<T>& x) const {
        if(!is_error() && !x.is_error()){
            return x;
        } else {
            return div(x);
        }
    }

    number<T> operator + (const number<T>& x) const {
        if(!is_error() && !x.is_error()){
            return x;
        } else {
            return add(x);
        }
    }

    bool operator == (const number<T>& x) const {
        return data == x.data;
    }
};


struct number_fraction:public number<pair<long,long>>{
    using base = number<pair<long,long>>;

    number_fraction div(const number_fraction x) const {
        if(x.data._1 == 0){
            return base("div 0");
        } else {
            auto t = make_pair(data._1 * x.data._2 , data_2 * x.data_1);

            return base(t);
        }
    }
};


struct number_double:public number<double> {
    
};