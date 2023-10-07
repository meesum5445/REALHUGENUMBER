#include<iostream>
#include<fstream>
#include"realhugenum.h"
#include"hugenumber.h"
using namespace std;
void realhugenum::insertat(int ind,int dig)
{
    if(ind<=this->dec_loc+1)
    {
        this->dec_loc++;
        this->val.insertat(ind,dig);
    }
    else
        this->val.insertat(ind-1,dig);
}
void realhugenum::print()const
{
    if(this->val.isnegative)
    {
        cout<<'-';
    }
    for(int i=this->val.size-1;i>=0;i--)
    {
        if(i==dec_loc)
        cout<<".";
        if(this->val.dig[i]<10)
            cout<<this->val.dig[i];
        else
        {
           char a;
           a=val.dig[i]+55;
           cout<<a;
        }

    }
}
realhugenum::realhugenum()
{
    this->dec_loc=-1;
}
realhugenum::realhugenum(int size,int value)
{
    hugenumber a(size,value);
    this->val=a;
    this->dec_loc=-1;
}
realhugenum::realhugenum(ifstream& rdr)
{
    this->load(rdr);
}
void realhugenum::load(ifstream &rdr)
{
    hugenumber temp;
    //.....................
    if(rdr.peek()=='+')
    {
        temp.isnegative=false;
        rdr.ignore();
    }
    else if(rdr.peek()=='-')
    {
        temp.isnegative=true;
        rdr.ignore();
    }
    int index=-1,i=1;
    char a;
    rdr.get(a);
    while(rdr && a!='\n')
    {
        if(a=='.')
        {
            index=i;
        }
        else
        {
            if(a-48<10)
                temp.insertat(0,a-48);
            else
                temp.insertat(0,a-55);
        }
        rdr.get(a);
        i++;
    }
    if(index==-1)
        index=temp.size;
    //..............................
    this->val=temp;
    this->dec_loc=temp.size-index-1;
    this->trim();
}
realhugenum::realhugenum(const realhugenum &b)
{
    *this=b;
}
void realhugenum::trim_pre_dec()
{
    int i=this->val.size-1;
    int count=0;
    while(this->val.dig[i]==0 && i>=0)
    {
        count++;
        i--;
    }

    if(this->val.size-count==0)
    {
        hugenumber a;
        this->val=a;
        return ;
    }
    int *t=new int[this->val.size-count];
    for(int j=0;j<this->val.size-count;j++)
    {
        t[j]=this->val.dig[j];
    }
    delete[]this->val.dig;
    this->val.dig=t;
    this->val.size-=count;
}
void realhugenum::trim_post_dec()
{
    int count=0;
    while(count<=this->dec_loc&&this->val.dig[count]==0)
    {
        count++;
    }
    int *temp=new int[this->val.size-count]{};
    this->val.size-=count;
    for(int i=0;i<this->val.size;i++)
    {
        temp[i]=this->val.dig[i+count];
    }
    delete [] this->val.dig;
    this->val.dig=temp;
    this->dec_loc-=count;
}
void realhugenum::trim()
{
    
    this->trim_pre_dec();
    this->trim_post_dec();
}
int realhugenum::operator[](int ind) const
{
    return this->val[ind];
}
int& realhugenum::operator[](int ind)
{
    return this->val[ind];
}
bool realhugenum::LessThanQuantityWise(const realhugenum&b) const
{
    realhugenum num0=*this;
    realhugenum num1=b;
    //..................
    if(num0.val.size-num0.dec_loc<num1.val.size-num1.dec_loc)
    {
        return true;
    }
    if(num0.val.size-num0.dec_loc>num1.val.size-num1.dec_loc)
    {
        return false;
    }
    return num0.val.LessThanQuantityWise(num1.val);
}
bool realhugenum::GreaterThanQuantityWise(const realhugenum&b) const
{
    realhugenum num0=*this;
    realhugenum num1=b;
    num0.trim();
    num1.trim();
    //..................
    if(num0.val.size-num0.dec_loc>num1.val.size-num1.dec_loc)
    {
        return true;
    }
    if(num0.val.size-num0.dec_loc<num1.val.size-num1.dec_loc)
    {
        return false;
    }
    return num0.val.GreaterThanQuantityWise(num1.val);
}
bool realhugenum::EqualQuantityWise(const realhugenum & b) const
{
    return (this->val.size-b.dec_loc==b.val.size-b.dec_loc)&&this->val.EqualQuantityWise(b.val);
}
void realhugenum::operator=(const realhugenum &b)
{
    if(this->val.dig==b.val.dig)
        return;
    this->val=b.val;
    this->dec_loc=b.dec_loc;
}
realhugenum realhugenum::operator*(const realhugenum &b)const
{
    realhugenum pro;
    pro.val=this->val*b.val;
    pro.dec_loc=this->dec_loc+b.dec_loc+1;
    pro.trim();
    return pro;
}
realhugenum realhugenum::operator+(const realhugenum &b)const
{
    realhugenum num0=*this;
    realhugenum num1=b;
    //..................
    hugenumber num0den(num0.dec_loc+2,0);
    num0den.dig[num0den.size-1]=1;
    hugenumber num1den(num1.dec_loc+2,0);
    num1den.dig[num1den.size-1]=1;
    hugenumber lcm;
    //.................
    if(num0.dec_loc>num1.dec_loc)
    {
        lcm=num0den;
    }
    else
    {
        lcm=num1den;
    }
    realhugenum sum;
    sum.val=num0.val*(lcm/num0den)+num1.val*(lcm/num1den);
    sum.dec_loc=lcm.size-2;
    sum.trim();
    return sum;
}
realhugenum realhugenum::operator-(const realhugenum &b)const
{
    return *this+(-b);
}
const realhugenum realhugenum::operator++(int)
{
    realhugenum temp=*this;
    realhugenum a(1,1);
    *this=*this+(a);
    return temp;
    
}
realhugenum& realhugenum::operator++()
{
    realhugenum a(1,1);
    *this=*this+(a);
    return *this;
    
}
const realhugenum realhugenum::operator--(int)
{
    realhugenum temp=*this;
    realhugenum a(1,1);
    *this=*this-(a);
    return temp;
    
}
realhugenum& realhugenum::operator--()
{
    realhugenum a(1,1);
    *this=*this-(a);
    return *this;
    
}
realhugenum realhugenum::operator-()const
{
    realhugenum a=*this;
    a.val.isnegative=!a.val.isnegative;
    return a;
}
void realhugenum::operator*=(const realhugenum &b)
{
    *this=*this*b;
}
void realhugenum::operator+=(const realhugenum &b)
{
    *this=*this+b;
}
void realhugenum::operator-=(const realhugenum &b)
{
    *this=*this-b;
}
bool realhugenum::operator==(const realhugenum &b)const
{
    if(this->val.isnegative==b.val.isnegative)
        return (*this).EqualQuantityWise(b);
    return false;
}
bool realhugenum::operator<(const realhugenum &b)const
{
    if(this->val.isnegative==false&&b.val.isnegative==true)
    {
        return false;
    }
    else if(this->val.isnegative==true&&b.val.isnegative==false)
    {
        return true;
    }
    else if(this->val.isnegative==false&&b.val.isnegative==false)
    {
        return (*this).LessThanQuantityWise(b);    
    }
    else
        return (b).LessThanQuantityWise(*this);    
}
bool realhugenum::operator<=(const realhugenum &b)const
{
    return (*this<b) ||(*this==b);
}
bool realhugenum::operator>(const realhugenum &b)const
{
    
    return b<*this;
}
bool realhugenum::operator>=(const realhugenum &b)const
{
    return (*this>b) ||(*this==b);
}
ostream& operator<<(ostream& ,const realhugenum &b)
{
    realhugenum a=b;
    a.print();
    return cout;
}

ifstream& operator>>(ifstream& rdr,realhugenum &b)
{
    b.load(rdr);
    return rdr;
}
ofstream& operator<<(ofstream& writer,const realhugenum &b)
{
    for(int i=0;i<b.val.getsize();i++)
    {
        if(b.dec_loc==b.val.getsize()-i-1)
            writer<<".";
        writer<<b.val[i];

    }
    return writer;
}
realhugenum realhugenum::operator/(const realhugenum &b)const
{
    hugenumber zero;
    hugenumber ten(2,0);
    ten.dig[1]=1;
    //..............
    realhugenum dividend=*this;
    dividend.val.isnegative=false;
    realhugenum divisor=b;
    divisor.val.isnegative=false;
    
    //..........................
    realhugenum ans;
    //....................
    hugenumber qoutient;
    hugenumber reminder(1,1);
    int decimalplace=0;
    while(decimalplace<6)
    {
        qoutient+=dividend.val/divisor.val;
        reminder=dividend.val%divisor.val;
        if(reminder==zero)
        {
            break;
        }
        else
        {
            qoutient*=ten;
            reminder*=ten;
        }
        dividend.val=reminder;
        ans.dec_loc++;
        decimalplace++;
    }
    ans.val=qoutient;
    ans.dec_loc+=dividend.dec_loc-divisor.dec_loc;
    ans.trim();
    return  ans;
    
}