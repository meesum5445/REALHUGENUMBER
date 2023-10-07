#include<iostream>
#include<fstream>
#include"hugenumber.h"
using namespace std;
class realhugenum
{
    private:
        hugenumber val;
        int dec_loc;
    public:
        void insertat(int,int);
        realhugenum();
        realhugenum(int,int);
        realhugenum(ifstream&);
        void load(ifstream&);
        realhugenum(const realhugenum &);
        void print()const;
        void trim_pre_dec();
        void trim_post_dec();
        void trim();
        //..............
        int operator[](int) const;
        int& operator[](int);
        bool LessThanQuantityWise(const realhugenum&) const;
        bool GreaterThanQuantityWise(const realhugenum & ) const;
        bool EqualQuantityWise(const realhugenum & ) const;
        void operator=(const realhugenum &b);
        const realhugenum operator++(int);
        realhugenum& operator++();
        const realhugenum operator--(int);
        realhugenum& operator--();
        realhugenum operator*(const realhugenum &b)const;
        realhugenum operator+(const realhugenum &b)const;
        realhugenum operator-(const realhugenum &b)const;
        void operator*=(const realhugenum &b);
        realhugenum operator/(const realhugenum &b)const;
        // void operator/=(const realhugenum &b);
        void operator+=(const realhugenum &b);
        void operator-=(const realhugenum &b);
        realhugenum operator-()const;
        bool operator<(const realhugenum &b)const;
        bool operator<=(const realhugenum &b)const;
        bool operator>(const realhugenum &b)const;
        bool operator>=(const realhugenum &b)const;
        bool operator==(const realhugenum &b)const;
        friend ostream& operator<<(ostream&,const realhugenum &b);
        friend ifstream& operator>>(ifstream& rdr,realhugenum &b);
        friend ofstream& operator<<(ofstream& writer,const realhugenum &b);
        
};