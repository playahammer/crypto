#ifndef BASE64_H
#define BASE64_H

typedef unsigned int u_int24_t; // 24 bits a group

#define BASE6BITS 0x3F // 6bits
#define BASE8BITS 0xFF // 8bits

#include <iostream>
#include <string>

using namespace std;

string base64encode(string);

string base64decode(string);

static int getindexbychar(char);

#endif // !BASE64_H