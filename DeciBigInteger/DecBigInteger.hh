/**
 * The header file for definition of DecBigInteger class
 */
#ifndef __DECBIGINTEGER_H_INCLUDED__
#define __DECBIGINTEGER_H_INCLUDED__

#include <string>
#include <iostream>

//Internal use of constants;
//We will use 16 int in arrays to store the number.
//This could be expanded in needs, also 16 ints.
const int fixSegIncrement = 16;
//Consider of the target machine word size(64bits) and human readability
//We will use 10^8 to be stored in the segments (For decimal purpose)
const int highSegDecValue = 100000000;
const int fixSegDigits = 8;
const std::string separator = ",";

class BigInteger{
public:
    BigInteger();
    BigInteger(const int &i);
    BigInteger(const BigInteger & bi);
    ~BigInteger();

    BigInteger& operator=(const BigInteger & o);
    
    friend std::ostream& operator <<(std::ostream& os, const BigInteger& o);
    friend BigInteger operator +(const BigInteger& o1, const BigInteger& o2);

protected:
    void resizeTo(int nsize);
    void incrSize(int n);

protected:
    //The arrays to store the real number. The number stores in the reverse order.
    // i.e. the smaller address stores the smaller parts of the digits.
    // e.g. if the number is 1234567890123456
    //      pdigits[0] = 90123456
    //      pdigits[1] = 12345678
    int *pdigits;
    int size;
    int cap; //The capacity
};


#endif //__DECBIGINTEGER_H_INCLUDED__
