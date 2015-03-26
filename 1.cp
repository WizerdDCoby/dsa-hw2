//
//  bigintegerforbinary.cpp
//  hw1_7_1
//
//  Created by Martina Wei on 2015/3/20.
//  Copyright (c) 2015年 Martina Wei. All rights reserved.
//
#include <iostream>
#include <sstream>
#include <vector>
#include "biginteger_for_binary.h"

BigInteger::BigInteger(const int& a){
    int temp= a;
    while (temp > 99) {
        num.push_back(temp%100);
        temp=temp-(temp%100);
        temp=temp/100;
    }
    
    num.push_back(temp);
}

BigInteger::BigInteger(const std::string& s){
    int n1,n2;
    int i= (s.size()-1);
    while (i>=0){
        std::stringstream s1;
        s1 << s[i];
        s1 >> n1;
        i--;
        if (i >= 0) {
            std::stringstream s2;
            s2 << s[i];
            s2 >> n2;
            num.push_back(n2*10+n1);
            i--;
        }else{
            num.push_back(n1);
        }
    }

}

BigInteger::BigInteger(const BigInteger& a){ num = a.num; }

BigInteger::~BigInteger(){}

bool BigInteger:: operator < (const BigInteger& n)const {
    
    bool x;
    BigInteger c= (*this);
    BigInteger d= n;
    //a<b; copy c=a b=d
    
    //clear 0 before the real number of c
    for (auto it = c.num.rbegin(); it!=c.num.rend(); it++){
        if ((*it)!=0 ) {
            break;
        }else{
            c.num.pop_back();
        }
    }
    //clear 0 before the real number of d
    for (auto it = d.num.rbegin(); it!=d.num.rend(); it++){
        if ((*it)!=0 ) {
            break;
        }else{
            d.num.pop_back();
        }
    }
    
    
    int idx=c.num.size();
    int idy=d.num.size();
    
    
    if(c.num.size()<d.num.size()){
        x= true;
    }
    else if (c.num.size()==d.num.size()){
        
        for (int i = 1; i <=c.num.size(); i++){
            if ((c.num[idx-i])!=d.num[idx-i]){
                if(c.num[idx-i]<d.num[idx-i])
                    x=true;
                else
                    x=false;
            }
            break;
        }
    }
    return x;
    /*bool x;
    int idx=this->num.size();
    int idy=n.num.size();
    if(idx<idy){
        x= true;
    }
    else if (idx == idy){
    
        for (int i = 1; i <=idy; i++){
            if ((this->num[idx-i])!=n.num[idx-i]){
                if(this->num[idx-i]<n.num[idx-i])
                    x=true;
                else
                    x=false;
                //std::cout << this->num[i]<<" "<<x<<std::endl;
            }
            break;
        }
    }
    return x;*/
}


const BigInteger BigInteger:: operator-(const BigInteger& n) const{
    //copy this and n
    std::vector<int> a,b;
    a = this->num;
    b = n.num;
    
    auto it1 = this->num.begin();
    auto it2 = n.num.begin();
    
    BigInteger ans;
    
    int temp;
    int minus = 0;
    
    
    while (it1!=this->num.end()) {
        if (it2 == n.num.end()){
            temp = (*it1)+minus;
            if (temp<0){
                temp += 100;
                ans.num.push_back(temp);
                minus = -1;
            }else{
                ans.num.push_back(temp);
                minus = 0;
            }
            it1++;
        }else{
            temp = (*it1)-(*it2)+minus;
            if ( temp<0 ){
                temp += 100;
                ans.num.push_back(temp);
                minus = -1;
            }else{
                ans.num.push_back(temp);
                minus = 0;
            }
            it1++;
            it2++;
        }
        
    }
    
    //clear 0 before real number
    for (auto it = ans.num.rbegin(); it!=ans.num.rend(); it++){
        if ((*it)!=0 ) {
            return ans;
        }else if (((*it) ==0) && (it != ans.num.rend()-1)){
            ans.num.pop_back();
        }
    }

    return ans;
}

const BigInteger BigInteger:: operator*(const BigInteger& n) const{
    BigInteger ans;
    int x=this->num.size();
    int y=n.num.size();
    ans.num = std::vector<int>(x+y+1,0);
    //std::cout <<x<<y<<std::endl;
    int temp=0;
    
    //Biginteger*Biginteger
    for (int i=0; i!=x; i++){
        for (int j=0; j!=y; j++){
            ans.num[i+j]+=(this->num[i])*n.num[j];
        }
    }
    
    //if >100 ;move to next
    for (int i=0; i!=ans.num.size();i++){
        ans.num[i]+=temp;
        if (ans.num[i]>99){
            temp=ans.num[i]/100;
            ans.num[i]=ans.num[i]%100;
            //std::cout<< temp<<std::endl;
        }else
            temp=0;
    }
    
    //clear 00
    for (auto it = ans.num.rbegin(); it!=ans.num.rend(); it++){
        if ((*it)!=0 ) {
            return ans;
        }else{
            ans.num.pop_back();
            }
    }
    return ans;
}



BigInteger& BigInteger:: operator *=(int x){
    int shan = 0;
    BigInteger ans;
    ans = *this;
    ans.num.push_back(0);
    
    //BIginteger*int
    for (auto iter = ans.num.begin(); iter!=ans.num.end(); iter++)
    {(*iter)*= x;}
    
    
    //if >100 ;move to next
    for (int i=0; i<=ans.num.size(); i++){
        
        ans.num[i]+=shan;
        if (ans.num[i]>99){
            shan=ans.num[i]/100;
            ans.num[i]%=100;
        }else{
            shan=0;}
    }
    
    //clear 00
    for (auto it = ans.num.rbegin(); it!=ans.num.rend(); it++){
        if ((*it)!=0 ) {
        }else{
            ans.num.pop_back();
        }
    }
    
    (*this)=ans;
    
    return *this;
}

BigInteger& BigInteger:: operator/=(int x){
    int plus = 0;
    
    for (auto iter = this->num.rbegin(); iter!=this->num.rend(); iter++){
        int temp = (*iter)+plus*100;
        plus = temp % x;
        * iter = temp/x;
    }
    
    //clear 00
    for (auto it = this->num.rbegin(); it!= this->num.rend(); it++){
        if ((*it)!=0) {
            return *this;
        }else{
            this->num.pop_back();
        }
    }
    return *this;
}

BigInteger& BigInteger:: operator=(const BigInteger& x){
    (*this).num=x.num;
    return *this;
}
bool BigInteger:: iseven(){
    if(*(this->num.cbegin())%2 == 0)
        return true;
    return false;
}

bool BigInteger:: iszero(){
    bool x=1;
    for (auto it=this->num.crbegin(); it!=this->num.crend(); it++){
        if (*it != 0){
            x=false;
            break;
        }else
            x=true;
    }
    return x;
}

std::ostream& operator<<(std::ostream& strm, const BigInteger& b){
    std::vector<int> temp;
    
    for (auto it= b.num.crbegin(); it!=b.num.crend(); it++)
        temp.push_back(*it);
    
    auto it = temp.begin();
    if ((*it)!=0){
        strm << (*it);
        it++;
    }else { it++; }
    
    while (it!=temp.end()){
        if ((*it)<10){
            strm << "0" <<(*it);
        }
        else
            strm << (*it);
        it++;
    }
    return strm;
}



