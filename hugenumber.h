#pragma once
#include<fstream>
#include<iostream>
using namespace std;
class hugenumber
{
    static int const base=10;
    friend class realhugenum;
    private:
        int size;
        int *dig;
        bool isnegative;
        void insertat(int,int);
    public:
        int getsize()const;
        hugenumber();
        hugenumber(int,int);
        hugenumber(ifstream&);
        hugenumber(const hugenumber &b);
        void load(ifstream&);
        void load2(ifstream&);
        void print();
        //.................
        void trim();
        //.................
        //OPERATIONS(without operators)//
        int operator[](int ) const;
        int& operator[](int );
        hugenumber add(const hugenumber &)const;
        hugenumber sub(const hugenumber &)const;
        bool LessThanQuantityWise(const hugenumber&) const;
        bool GreaterThanQuantityWise(const hugenumber & b) const;
        bool EqualQuantityWise(const hugenumber & b) const;
        //.............................//
        //OPERATIONS(operators)//
        void operator=(const hugenumber &b);
        hugenumber operator++(int);
        hugenumber operator++();
        hugenumber operator--(int);
        hugenumber operator--();
        hugenumber operator+(const hugenumber &b)const;
        hugenumber operator*(const hugenumber &b)const;
        void operator*=(const hugenumber &b);
        hugenumber operator/(const hugenumber &b)const;
        void operator/=(const hugenumber &b);
        hugenumber operator%(const hugenumber &b)const;
        void operator%=(const hugenumber &b);
        void operator+=(const hugenumber &b);
        hugenumber operator-(const hugenumber &b)const;
        hugenumber operator-()const;
        void operator-=(const hugenumber &b);
        bool operator<(const hugenumber &b)const;
        bool operator<=(const hugenumber &b)const;
        bool operator>(const hugenumber &b)const;
        bool operator>=(const hugenumber &b)const;
        bool operator==(const hugenumber &b)const;
        friend ostream& operator<<(ostream&,const hugenumber &b);
        friend ifstream& operator>>(ifstream& rdr,hugenumber &b);
        friend ofstream& operator<<(ofstream& writer,const hugenumber &b);
        //.............................//
};