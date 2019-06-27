#include "bigint.h"

/**
 * @brief BigInt::BigInt
 * @param vIs
 * @param flag
 */
BigInt::BigInt(std::vector<int> vIs, int flag){
    this->numbers = vIs;
    this->signumber = flag;
}
/**
 * @public
 * @brief BigInt::BigInt
 */
BigInt::BigInt(){
    this->signumber = 0;
    this->numbers.push_back(0);
}

BigInt::BigInt(int *inArr, int size){
    if(inArr == nullptr || size < 0){
        this->signumber = 0;
        this->numbers.push_back(0);
    }else{
        int firstNumber = 0;
        if(*inArr < 0){
            this->signumber = -1;
            firstNumber = *inArr * -1;
        }else if(*inArr > 0){
            this->signumber = 1;
            firstNumber = *inArr;
        }else{
            this->signumber = 0;
            firstNumber = *inArr;
            size = -1;
        }
        this->numbers.push_back(firstNumber);
        for (int i = size - 1; i > 0; i++)
            this->numbers.push_back(inArr[i]);
    }
}

BigInt::BigInt(long long longInt){
    if(longInt < 0){
        this->signumber = -1;
        longInt = longInt * -1;
    }else if (longInt == 0) {
        this->signumber = 0;
        this->numbers.push_back(0);
    }else{
        this->signumber = 1;
    }

    while (longInt) {
        this->numbers.push_back(static_cast<int>(longInt % default_base));
        longInt /= default_base;
    }

}

BigInt::BigInt(std::vector<int> vints){
    this->signumber = *vints.begin() < 0 ? -1 : 1;
    this->numbers.assign(vints.begin(), vints.end());
}
BigInt::BigInt(std::string strInt):BigInt(strInt, BigInt::DEC){};

BigInt::BigInt(std::string strInt, int scale){
    if(strInt.length() == 0){
        this->signumber = 0;
        this->numbers.push_back(0);
    }else{
        switch (strInt[0]) {
            case '+':
                this->signumber = 1;
                break;
            case '-':
                this->signumber = -1;
                break;
            default:
                if(strInt[1] == '0') this->signumber = 0;
                else
                this->signumber = 1;
                break;

        }
    }
    // Only support dec
    assert(scale == BigInt::DEC);
    std::string newStr = (strInt[0] == '+' || strInt[0] == '-') ? strInt.substr(1) : strInt;
    int size = static_cast<int>(newStr.length());
    while(true){
        if(size <= 0) break;

        int num = 0;
        int prefix = 1;
        int length = 0;
        for (int i = size - 1; i >= 0 && i >= size - 9; i--) {
            assert(!(newStr[i] < '0' || newStr[i] > '9'));
            num += (newStr[i] - '0') * prefix;
            prefix *= 10;
            length++;
        }
        size -= length;
        this->numbers.push_back(num);
    }
}

BigInt BigInt::operator+(const BigInt &b) const{
    BigInt c = *this;
    c += b;
    return c;
}

BigInt BigInt::operator+(const long long &ll) const{
    BigInt c = *this;
    c += BigInt(ll);
    return c;
}
BigInt& BigInt::operator+=(const BigInt &b){
    // 2 + (-3) or -2 + 3
    if(this->signumber * b.signumber == -1 && !fromSub){
        fromAdd = true; //true
        return *this -= b;
    }
    // -2 + (-3) = -(2 + 3)
    if(this->signumber == -1 && b.signumber == -1) this->signumber = -1;

    if(this->signumber == 0
            || b.signumber == 0) this->signumber = 1;
    std::vector<int>::iterator iIter = numbers.begin();
    std::vector<int>::const_iterator bIter = b.numbers.cbegin();

    int sum = 0;
    while (iIter != numbers.end() || bIter != b.numbers.cend()) {
        if(iIter != numbers.end()){
            sum += *iIter;
        }else{
            numbers.push_back(0);
            iIter = numbers.end() - 1; //complete
        }

        if(bIter != b.numbers.cend()){
            sum += *bIter;
            bIter++;
        }

        *iIter = sum % BigInt::default_base;
        iIter++;
        sum /= BigInt::default_base;
    }

    if(sum){
        numbers.push_back(1);
    }

    fromSub = false;
    return *this;
}

BigInt& BigInt::operator+=(const long long &ll){
    return *this += BigInt(ll);
}

BigInt BigInt::operator-(const BigInt &b) const{
    BigInt c = *this;
    c -= b;
    return c;
}

BigInt BigInt::operator-(const long long &ll) const{
    BigInt c = *this;
    c -= BigInt(ll);
    return c;
}
BigInt& BigInt::operator-=(const BigInt &b){
    // 2 - (-3) or -2 - 3
    if(this->signumber * b.signumber == -1 && !fromAdd){
        fromSub = true;
        return *this += b;
    }
    int preProcess = compare(*this, b);
    std::vector<int> temp1 = this->numbers, temp2 = b.numbers;
    if(preProcess == 0) { // 2 - 2 or -2 - (-2)
        this->signumber = 0;
        this->numbers.clear();
        this->numbers.push_back(0);
        return *this;
    }else if(preProcess == -1) { // 2 - 3 or -2 + 3
        temp1 = b.numbers;
        temp2 = this->numbers;
        if(this->signumber == -1 && absCompare(*this, b) < 0) this->signumber = 1;
        else this->signumber = -1;
    }
    std::vector<int>::iterator iIter = temp1.begin();
    std::vector<int>::const_iterator bIter = temp2.cbegin();

    this->numbers.clear();
    int dif = 0;
    while(iIter != temp1.end() || bIter != temp2.cend()){
        if(iIter != temp1.end()){
            dif += *iIter;
            iIter++;
        }

        if(bIter != temp2.cend()){
            dif -= *bIter;
            bIter++;
        }

        if(dif < 0){
            this->numbers.push_back(dif + BigInt::default_base);
            dif = -1;
        }else{
            this->numbers.push_back(dif % BigInt::default_base);
            dif /= BigInt::default_base; //must be zero.
        }
    }



    // split zero of head like 0000012312312
    if(this->numbers.size() > 0){
        do{
            iIter = this->numbers.end() - 1;
            if(*iIter == 0) this->numbers.pop_back();
            else break;
        }while (this->numbers.size() > 1);
    }

    fromAdd = false;
    return *this;
}

BigInt& BigInt::operator-=(const long long &ll){
    return *this -= BigInt(ll);
}

BigInt BigInt::operator*(const BigInt &b) const{
    BigInt c = *this;
    c *= b;
    return c;
}

BigInt BigInt::operator*(const long long & ll)const{
    BigInt c = *this;
    c *= BigInt(ll);
    return c;
}

BigInt& BigInt::operator*=(const BigInt &b){
    this->signumber *= b.signumber;
    if(!this->signumber){ // 0 * x
        this->numbers.clear();
        this->numbers.push_back(0);
        return *this;
    }

    std::vector<int>::const_iterator bIter = b.numbers.begin();
    std::vector<int>::const_iterator mIter;
    std::vector<int> temp;
    //std::vector<int>::iterator tIter = temp.begin();

    BigInt bTemp(0);
    bTemp.signumber = 1;


    //O(n2)
    for (; bIter != b.numbers.end(); bIter++) {
        int sum = 0;
        temp.clear();
        for (int i = 0; i < bIter - b.numbers.begin(); i++) {
            temp.push_back(0);
        }
        for(mIter = this->numbers.begin(); mIter != this->numbers.end(); mIter++){
            long long s = static_cast<long long>(*mIter) * static_cast<long long>(*bIter);
            int result = (s + sum) % BigInt::default_base;
            temp.push_back(result);
            sum = (s + sum) / BigInt::default_base;
        }
        if(sum != 0){
            temp.push_back(sum);
        }
        BigInt s (temp , 1);
        bTemp += s;
    }
    this->numbers.clear();
    this->numbers.assign(bTemp.numbers.begin(), bTemp.numbers.end());
    return *this;
}

BigInt& BigInt::operator*=(const long long &ll){
    return *this *= BigInt(ll);
}

BigInt BigInt::operator/(const BigInt &b) const{
    BigInt c = *this;
    c /= b;
    return c;
}

BigInt BigInt::operator/(const long long &ll) const{
    BigInt c = *this;
    c /= BigInt(ll);
    return c;
}
BigInt & BigInt::operator/=(const BigInt &b){
    assert(b.signumber != 0); // 1 / 0 is invalid.
    if(this->signumber == 0 || *this <= b){ // 0 / n or a / b (a < b)
        this->numbers.clear();
        this->signumber = 0;
        this->numbers.push_back(0);
        return *this;
    }

    int flag = this->signumber * b.signumber;
    this->signumber = 1;

    //copy b to temp
    BigInt temp;
    temp.signumber = 1;
    temp.numbers.assign(b.numbers.begin(), b.numbers.end());

    BigInt s;
    s.signumber = 1;
    s.numbers.clear();
    s.numbers.push_back(1);
    //pre-process

    std::string thisString = this->toString();
    std::string bString = temp.toString();

    unsigned long long subSize = thisString.size() - bString.size();
    s <<= subSize;
    BigInt temp1 = temp << subSize;

    BigInt sTemp = s;
    //clear s
    s.numbers.clear();
    s.numbers.push_back(0);
    if(*this == temp1){
        this->numbers.clear();
        this->numbers.assign(s.numbers.begin(), s.numbers.end());
        return *this;
    }else if (*this > temp1) {
        while (*this > BigInt(0) ) {
            *this -= temp1;
            s += sTemp;
        }
        *this += temp1;
        s -= sTemp;
        sTemp >>= 1;
        temp1 >>= 1;
    }else {
        s >>= 1;
        temp1 >>= 1;
        sTemp >>= 1;
    }

    while (true) {
        thisString = this->toString();
        bString = temp.toString();

        if(thisString.size() <= bString.size() && *this <= b){
            if(*this == b){
                s += 1;
                *this -= b;
            }
            break;
        }

        while(this->signumber > 0) {
            *this -= temp1;
            s += sTemp;
        }
        if(!this->signumber){ break;};
        *this += temp1;
        s -= sTemp;
        temp1 >>= 1;
        sTemp >>= 1;
    }

    // do optimizing
    /*
    s.numbers.clear();

    for(int i = 1; i < this->numbers.size() - b.numbers.size(); i++)
        s.numbers.push_back(0);
    if(this->numbers.size() != b.numbers.size()){
        if(*(this->numbers.end() - 1) >= *(b.numbers.end() - 1)){
            s.numbers.push_back(0);
            long radix = 1;
            while (*(this->numbers.end() - 1) >= radix * *(b.numbers.end() - 1)) {
                radix *= 10;
            }
            radix /= 10;
            s.numbers.push_back(static_cast<int>(radix));
        }else if(*(this->numbers.end() - 1) < *(b.numbers.end() - 1)) {
            long radix = 1;
            while (*(b.numbers.end() - 1) * radix <= BigInt::default_base) {
                qDebug()<<(*(b.numbers.end() - 1) * radix);
                radix *= 10;
            }
            radix /= 10;
            s.numbers.push_back(static_cast<int>(radix));
        }
    }
    BigInt s1 = s * temp;
    *this -= s1;

    while (this->signumber == 1) {
        *this -= temp;
        s += BigInt(1);
    }

    s-= BigInt(1);
    */
    this->signumber = flag;
    this->numbers.clear();
    this->numbers.assign(s.numbers.begin(), s.numbers.end());

    return *this;
}

BigInt & BigInt::operator/=(const long long &ll){
    return *this /= BigInt(ll);
}

BigInt  BigInt::divide2(){
    std::vector<int>::iterator iter;
    std::vector<int> temp;
    int pre = 0;
    for (iter = this->numbers.begin(); iter != this->numbers.end(); iter++) {
        long long  result = static_cast<long long>(*iter) * 500000000 + static_cast<long long>(pre);
        temp.push_back(result % BigInt::default_base);
        pre = result / BigInt::default_base;
    }

    if(pre != 0){

        temp.push_back(pre);
    }

    this->numbers.assign(temp.begin() + 1, temp.end());


    return *this;
}
//Mod fetching remainder.

BigInt BigInt::operator%(const BigInt & b) const{
    BigInt c = *this;
    c %= b;
    return c;
}

BigInt & BigInt::operator%=(const BigInt &b){
    assert(b.signumber > 0);

    if(*this < b){
        return *this;
    }
    //copy b to temp
    BigInt temp;
    temp.signumber = 1;
    temp.numbers.assign(b.numbers.begin(), b.numbers.end());
    if(this->signumber == -1){
        //TODO
    }

    int flag = this->signumber * b.signumber;
    this->signumber = 1;



    BigInt s;
    s.signumber = 1;
    s.numbers.clear();
    s.numbers.push_back(1);
    //pre-process

    std::string thisString = this->toString();
    std::string bString = temp.toString();


    if(*this < b) return *this;
    unsigned long long subSize = thisString.size() - bString.size();
    s <<= subSize;
    BigInt temp1 = temp << subSize;

    BigInt sTemp = s;
    //clear s
    s.numbers.clear();
    s.numbers.push_back(0);
    if(*this == temp1){
        this->numbers.clear();
        this->signumber = 0;
        this->numbers.assign(s.numbers.begin(), s.numbers.end());
        return *this;
    }else if (*this > temp1) {
        while (*this > 0 ) {
            *this -= temp1;
            s += sTemp;
        }
        *this += temp1;
        s -= sTemp;
        temp1 >> 1;
        sTemp >>= 1;
    }else {
        s >>= 1;
        temp1 >>= 1;
        sTemp >>= 1;
    }

    while (true) {
        thisString = this->toString();
        bString = temp.toString();

        if(thisString.size() <= bString.size() && *this < b){
            if(*this == b){
                s += 1;
                *this -= b;
            }
            break;
        }

        while(this->signumber > 0) {
            *this -= temp1;
            s += sTemp;
        }
        if(!this->signumber){ s += 1; break;}
        *this += temp1;
        s -= sTemp;
        temp1 >>= 1;
        sTemp >>= 1;
    }
    if(this->numbers.size() == 1 && *this->numbers.begin() == 0) this->signumber = 0;
    else this->signumber = flag;
    return *this;
}
BigInt BigInt::operator%(const long long &ll) const{
    BigInt c = *this;
    c %= ll;
    return c;
}

BigInt & BigInt::operator%=(const long long &ll){
    return *this %= BigInt(ll);
}

int BigInt::mod2(){
    return *this->numbers.begin() % 2;
}
BigInt BigInt::operator<<(const unsigned long long ll){
    BigInt s = *this;
    std::string s1 = s.toString();
    for (unsigned long long i = 0; i < ll; i++) {
        s1.append("0");
    }
    return BigInt(s1);
}

BigInt &BigInt::operator<<=(const unsigned long long ll){
    BigInt s = *this<<ll;
    this->numbers.assign(s.numbers.begin(), s.numbers.end());
    return *this;
}

BigInt BigInt::operator>>(const unsigned long long ll){
    BigInt s = *this;
    std::string s1 = s.toString();
    s1 = s1.substr(0, s1.length() - ll);
    return BigInt(s1);
}

BigInt& BigInt::operator>>=(const unsigned long long ll){
    BigInt s = *this >> ll;
    this->numbers.clear();
    this->numbers.assign(s.numbers.begin(), s.numbers.end());
    return *this;
}
//Pow

BigInt BigInt::pow(const unsigned long long ll){
    if(ll == 0 && this->signumber != 0){ // n^0, n != 0
        this->signumber = 1;
        this->numbers.clear();
        this->numbers.push_back(1);
        return *this;
    }

    if(signumber == 0){  // 0^n
        this->signumber = 0;
        this->numbers.clear();
        this->numbers.push_back(0);
        return *this;
    }

    BigInt s(1);
    BigInt base = *this;
    unsigned long long copyLl = ll;

    while(copyLl != 0){
        if(copyLl & 0x01 != 0) s *= base;
        base *= base;
        copyLl >>= 1;
    }
    return s;
}

//Compare

bool BigInt::operator<(const BigInt b){
    return compare(*this, b) == -1;
}

bool BigInt::operator<=(const BigInt b){
    return compare(*this, b) <= 0;
}

bool BigInt::operator==(const BigInt b){
    return compare(*this, b) == 0;
}

bool BigInt::operator>=(const BigInt b){
    return compare(*this, b) >= 0;
}

bool BigInt::operator>(const BigInt b){
    return  compare(*this, b) > 0;
}
bool BigInt::operator!=(const BigInt b){
    return compare(*this, b) != 0;
}

std::string BigInt::toString(){
    std::string s;
    if(this->signumber == -1) s.append("-");else if(this->signumber == 1) s.append("+"); else return std::string("0");
    std::string temp;
    std::vector<int>::reverse_iterator iter = this->numbers.rbegin();
    for (; iter != this->numbers.rend(); iter++) {
        std::string toString = std::to_string(*iter);
        std::string s1;
        for (unsigned long long  i = 0; i < 9 - toString.length(); i++) {
            s1.append("0");
        }
        s1.append(toString);
        temp.append(s1);
    }
    unsigned long long i = 0;
    for (; i < temp.length() && temp[i] == '0'; i++);
    return s.append(temp.substr(i));
}

BigInt & BigInt::operator++(){
    return *this += 1;
}

BigInt & BigInt::operator--(){
    return *this -= 1;
}
/**
 * compare two BigInts
 * @brief BigInt::compare
 * @param bInt1
 * @param bInt2
 * @return 1 is bInt1 > bIn2, 0 is bInt1 == bInt2, 1 is bInt1 < bInt2
 */
int BigInt::compare(const BigInt bInt1, const BigInt bInt2){
    std::vector<int>::const_iterator bInt1Iter = bInt1.numbers.cbegin();
    std::vector<int>::const_iterator bInt2Iter = bInt2.numbers.cbegin();

    // 2324 > -24  -234 < 24
    if(bInt1.signumber * bInt2.signumber <= -1){
       return bInt1.signumber > bInt2.signumber ? 1 : -1;
    }
    if(bInt1.signumber * bInt2.signumber == 0){
        if(bInt1.signumber == bInt2.signumber) return 0;
        return bInt1.signumber > bInt2.signumber ? 1 : -1;
    }
    int dif = 0;
    int zf = 0;
    while (bInt1Iter != bInt1.numbers.cend() || bInt2Iter != bInt2.numbers.cend()) {
        if(bInt1Iter != bInt1.numbers.cend()){
            dif += *bInt1Iter;
            bInt1Iter++;
        }

        if(bInt2Iter != bInt2.numbers.cend()){
            dif -= *bInt2Iter;
            bInt2Iter++;
        }
        zf -= dif;
        zf %= BigInt::default_base;
        dif = (dif < 0) ? -1 : 0;
        if(dif < -1 * BigInt::default_base) break;
    }
    return dif < 0 ? -1 : (zf == 0 ? 0 : 1);
}

int BigInt::absCompare(const BigInt a, const BigInt b){
    BigInt tempA = a;
    BigInt tempB = b;
    tempA.signumber = 1;
    tempB.signumber = 1;
    return compare(tempA, tempB);
}


int BigInt::getNumbersLength(){
    return static_cast<int>(this->numbers.size());
}


std::vector<int> BigInt::getNumbers(){
    return this->numbers;
}
