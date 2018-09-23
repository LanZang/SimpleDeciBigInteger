#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

#include "DecBigInteger.hh"
using namespace std;

const BigInteger fibonacci(const long long n){
    BigInteger a1(1);
    BigInteger a2(1);
    BigInteger t;
    for(long long i = 3; i < n + 1; i++){
        t = a1 + a2;
        a1 = a2;
        a2 = t;
    }
    return t;
}


int main(int argc, char** argv){
	long long n;
	if(argc > 1){
		n = atoll(argv[1]);
	}
	BigInteger fib = fibonacci(n);
	cout<<"The f(" << n <<") is " << fib<<endl;
	return 0;
}
