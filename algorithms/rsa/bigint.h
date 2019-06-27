#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <vector>

#include <QDebug>
#include <QString>
class BigInt
{
public:
    //Constructors
    BigInt();
    BigInt(int*, int);
    BigInt(std::string);
    BigInt(std::string, int);
    BigInt(long long);
    BigInt(std::vector<int>);

    static const int DEC = 10;


    /** begin future **/
    static const int OCT = 8;
    static const int BIN = 2;
    static const int HEX = 16;
    /** end future **/

    /** main methods **/

    //Add
    BigInt operator+(BigInt const &) const;
    BigInt operator+(long long const &) const;
    BigInt & operator+=(BigInt const &);
    BigInt & operator+=(long long const &);

    //Substrcat
    BigInt operator-(BigInt const &)const;
    BigInt operator-(long long const &) const;
    BigInt & operator-=(BigInt const &);
    BigInt & operator-=(long long const &);

    //Multiple
    BigInt operator*(BigInt const &)const;
    BigInt operator*(long long const&)const;
    BigInt & operator*=(BigInt const &);
    BigInt & operator*=(long long const&);

    //Divide
    BigInt operator/(BigInt const &)const;
    BigInt operator/(long long const &) const;
    BigInt & operator/=(BigInt const &);
    BigInt & operator/=(long long const &);

    //Divide 2: / 2
    BigInt  divide2();
    //Pow
    BigInt pow(unsigned long long const);

    //Mod
    BigInt operator%(BigInt const &)const;
    BigInt &operator%=(BigInt const &);
    BigInt operator%(long long const &)const;
    BigInt & operator%=(long long const &);

    int mod2();
    //Compare
    bool operator<(BigInt const);
    bool operator<=(BigInt const);
    bool operator==(BigInt const);
    bool operator>=(BigInt const);
    bool operator>(BigInt const);
    bool operator!=(BigInt const);

    //Or

    //Nor

    //And

    //Shift
    //Note: shift operation is not real 'shift' in binary => 10000 -> (>> 2) -> 100
    BigInt operator<<(unsigned long long const);
    BigInt& operator<<=(unsigned long long const);

    BigInt operator>>(unsigned long long const);
    BigInt& operator>>=(unsigned long long const);

    BigInt& operator++();
    BigInt& operator--();

    std::string toString();

    int getNumbersLength();
    std::vector<int> getNumbers();
private:

    //Constructors
    BigInt(std::vector<int>, int);
    std::vector<int> numbers;

    int signumber; // -1 for negative, 1 for positive, 0 is zero.

    static const int default_base = 1000000000; // dec_base;


    static const int dec_dase = 1000000000; // dec_base, 10 of 10




    bool fromSub = false;
    bool fromAdd = false;

    static int compare(BigInt const, BigInt const);
    static int absCompare(BigInt const, BigInt const);

    /** begin future **/
    int base;

    static const int bin_base = 0xfffffff; // bin_base, 56 of 2
    static const int hex_base = 0xffffff; // hex_base,  7 of 16
    static const int oct_base = 0x3fffffff; // otc_base, 10 of 8
    /** end future **/

};

#endif // BIGINT_H
