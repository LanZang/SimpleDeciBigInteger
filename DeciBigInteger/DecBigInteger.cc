#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

#include "DecBigInteger.hh"

using namespace std;

//The constructors
BigInteger::BigInteger(){
    cap = fixSegIncrement;
    size = 1;
    pdigits = new int[fixSegIncrement];
    for(int i = 0; i < cap; i++){
        pdigits[i] = 0;
    }
}
BigInteger::BigInteger(const int &i){
    cap = fixSegIncrement;
    pdigits = new int[fixSegIncrement];
    size = 1;
	for(int i = 1; i < cap; i++){
        pdigits[i] = 0;
	}
    pdigits[0] = i;
}

//The copy constructor
BigInteger::BigInteger(const BigInteger & bi){
    pdigits = new int[bi.cap];
    size = bi.size;
    cap = bi.cap;
    for(int i = 0; i < cap; i++){
        pdigits[i] = bi.pdigits[i];
    }
}
BigInteger::~BigInteger(){
    delete[] pdigits;
    pdigits = NULL;
    cap = size = 0;
}

BigInteger&
BigInteger::operator=(const BigInteger & o){
    if(this != &o){
        if(pdigits != NULL)
            delete[] pdigits;
        cap = o.cap;
        size = o.size;
        pdigits = new int[cap];
        for(int i = 0; i < cap; i++){
            pdigits[i] = o.pdigits[i];
        }
    }
    return *this;
}

void
BigInteger::resizeTo(int ncap){
    if(ncap > cap){
        int *npdigits = new int[ncap];
        for(int i = 0; i < size; i++){
            npdigits[i] = pdigits[i];
        }
        for(int i = size; i < ncap; i++){
            npdigits[i] = 0;
        }
        if(pdigits != NULL)
            delete[] pdigits;
        pdigits = npdigits;
        cap = ncap;
    }
    return;
}

void
BigInteger::incrSize(int n){
    resizeTo(size + n);
}

BigInteger operator +(const BigInteger& o1, const BigInteger& o2){
    int oflow = 0;
    int max_size = o1.size;
    BigInteger total(o1);
    if(o2.size > o1.size){
        max_size = o2.size;
    }
    if(o2.cap > o1.cap){
        total.resizeTo(o2.cap);
    }
    for(int i = 0; i < max_size; i++){
        int o1v = 0;
        int o2v = 0;
        if(i < o1.size){
            o1v = o1.pdigits[i];
        }
        if(i < o2.size){
            o2v = o2.pdigits[i];
        }
        int v = o1v + o2v + oflow;
        //printf("operator(): i=%d: %d + %d + %d = %d\n", i, o1v, o2v,  oflow, v);
        oflow = 0;
        if(v > highSegDecValue){
            oflow = v / highSegDecValue;
            v -= highSegDecValue * oflow;
        }
        total.pdigits[i] = v;
        total.size = i + 1;
    }
    if(oflow > 0){
        int osize = total.size;
        if(total.size >= total.cap){
            total.incrSize(fixSegIncrement);
        }
        total.pdigits[osize] = oflow;
        total.size++;
    }
    //cout << o1 <<" + " << o2 <<" = " << total <<endl;
    return total;
}

ostream& operator<<(ostream& os, const BigInteger& o){
    bool first = true;
    for(int i = o.size; i > 0; i--){
        if(first){
            if(i == 1){
                os << o.pdigits[i - 1];
            }else if(o.pdigits[i - 1] > 0){
                first = false;
                os << o.pdigits[i - 1] << separator;
            }
        }else{
            if(i == 1){
                os << setfill('0') << setw(fixSegDigits) << o.pdigits[i - 1];
            }else{
                os << setfill('0') << setw(fixSegDigits) << o.pdigits[i - 1] << separator;
            }
        }
    }
    return os;
}
