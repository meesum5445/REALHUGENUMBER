#include<iostream>
#include<fstream>
#include"hugenumber.h"
using namespace std;
int hugenumber::getsize()const
{
    return this->size;
}
void hugenumber::insertat(int ind,int num)
{
    int *temp=new int[this->size+1]{};
    for(int i=0,j=0;i<this->size+1;i++)
    {
        if(i!=ind)
        {
            temp[i]=this->dig[j];
            j++;
        }
        else
        {
            temp[i]=num;
        }
    }
    this->size++;
    delete []this->dig;
    this->dig=temp;
}
hugenumber::hugenumber()
{
    this->size=1;
    this->dig=new int[1]{};
    this->isnegative=false;
}
hugenumber::hugenumber(int size,int value)
{
    this->size=size>0?size:1;
    this->dig=(size>0)?new int[size]:new int[1]{};
    this->isnegative=false;
    for(int i=0;i<size;i++)
    {
        this->dig[i]=value;
    }
}
hugenumber::hugenumber(ifstream &rdr)
{
    this->load(rdr);
}
hugenumber::hugenumber(const hugenumber &b)
{
    *this=b;
}
void hugenumber::load(ifstream &rdr)
{
    this->size=1;
    this->dig=new int[1]{};
    this->isnegative=false;
    //.....................
    if(rdr.peek()=='+')
    {
        this->isnegative=false;
        rdr.ignore();
    }
    else if(rdr.peek()=='-')
    {
        this->isnegative=true;
        rdr.ignore();
    }
    char a;
    rdr.get(a);
    while(rdr && a!='\n')
    {
        this->insertat(0,a-48);
        rdr.get(a);
    }
    (*this).trim();
}
void hugenumber::load2(ifstream &rdr)
{
    if(rdr.peek()=='+')
    {
        this->isnegative=false;
        rdr.ignore();
    }
    else if(rdr.peek()=='-')
    {
        this->isnegative=true;
        rdr.ignore();
    }
    string a;
    getline(rdr,a);
    int i=0;
    while(a[i]!='\0')
    {
        this->insertat(0,a[i]-48);
        i++;
    }
    (*this).trim();
}
void hugenumber::print()
{
    if(this->isnegative)
    {
        cout<<'-';
    }
    for(int i=this->size-1;i>=0;i--)
    {
        cout<<this->dig[i];
    }
}
void hugenumber::trim()
{
    int i=this->size-1;
    int count=0;
    while(this->dig[i]==0 && i>=0)
    {
        count++;
        i--;
    }

    if(this->size-count==0)
    {
        this->size=1;
        this->dig=new int[1]{};
        return ;
    }
    int *t=new int[this->size-count];
    for(int j=0;j<this->size-count;j++)
    {
        t[j]=this->dig[j];
    }
    delete[]this->dig;
    this->dig=t;
    this->size-=count;
}
hugenumber hugenumber::add(const hugenumber &b)const
{
    hugenumber sum;
    sum.size=this->size+1;
    sum.dig=new int[sum.size]{};
    for(int i=0;i<this->size;i++)
    {
        sum.dig[i]=this->dig[i];
    }
    //..........................
    int carry=0;
    for(int i=0;i<this->size;i++)
    {
        int S=carry+((i<this->size)?this->dig[i]:0)+((i<b.size)?b.dig[i]:0);
        sum.dig[i]=S%base;
        carry=S/base;
    }
    sum.dig[sum.size-1]+=carry;
    sum.trim();
    return sum;
}
hugenumber hugenumber::sub(const hugenumber &b)const
{
    hugenumber sub;
    sub=*this;
    for(int i=0;i<sub.size;i++)
    {
        if(sub.dig[i]<((i<b.size)?b.dig[i]:0))
        {
            sub.dig[i+1]--;
            sub.dig[i]=(sub.dig[i]+base)-((i<b.size)?b.dig[i]:0);
        }
        else
        {
            sub.dig[i]=sub.dig[i]-((i<b.size)?b.dig[i]:0);
        }
    }
    sub.trim();
    return sub;
}
bool hugenumber::LessThanQuantityWise(const hugenumber & b) const
{
    if(this->size<b.size) return true;
    else if(this->size>b.size) return false;
    
    for(int i=size-1;i>=0;i--)
    {
        if(this->dig[i]<b.dig[i]) return true;
        else if(this->dig[i]>b.dig[i]) return false;
    }
    return false;
}
bool hugenumber::GreaterThanQuantityWise(const hugenumber & b) const
{
    if(this->size<b.size) return false;
    else if(this->size>b.size) return true;
    
    return !(this->LessThanQuantityWise(b))&&(!(this->EqualQuantityWise(b)));
}

bool hugenumber::EqualQuantityWise(const hugenumber & b) const
{
    if(this->size!=b.size)return false;
    for(int i=0;i<this->size;i++)
    {
        if(this->dig[i]!=b.dig[i])
        {
            return false;
        }
    }
    return true;
}
int hugenumber::operator[](int i) const
{
    if(i>=this->size)return 0;
    return this->dig[this->size-i-1];
}
int& hugenumber::operator[](int i)
{
    return this->dig[this->size-i-1];
}
void hugenumber::operator=(const hugenumber &b)
{
    if(this->dig==b.dig)
        return;
    this->size=b.size;
    //delete []this->dig;
    this->dig=new int[this->size];
    for(int i=0;i<this->size;i++)
    {
        this->dig[i]=b.dig[i];
    }
    this->isnegative=b.isnegative;
}
hugenumber hugenumber::operator++(int b)
{
    hugenumber a(1,1);
    hugenumber temp=*this;
    
    *this=(*this+a);
    return temp;
}
hugenumber hugenumber::operator++()
{
    hugenumber a(1,1);
    *this=(*this+a);;
    return *this;
}
hugenumber hugenumber::operator--(int b)
{
    hugenumber a(1,1);
    hugenumber temp=*this;
    *this=(*this-a);
    return temp;
}
hugenumber hugenumber::operator--()
{
    hugenumber a(1,1);
    *this=(*this-a);
    return *this;
}
hugenumber hugenumber::operator+(const hugenumber &b)const
{
    hugenumber sum;
    if((*this).GreaterThanQuantityWise(b) ||(*this).EqualQuantityWise(b))
    {
        if(this->isnegative==false&&b.isnegative==false)
            sum=(*this).add(b);
        else if(this->isnegative==true&&b.isnegative==true)
            {
                sum=(*this).add(b);
                sum.isnegative=true;
            }
        else if(this->isnegative==true&&b.isnegative==false)
        {
            sum=(*this).sub(b);
            sum.isnegative=true;
        }
        else
        {
            sum=(*this).sub(b);
        }
            
    }
    else
    {
        return b+(*this);
    }
    return sum;
}
hugenumber hugenumber::operator*(const hugenumber &b)const
{
   hugenumber result;
   hugenumber btemp=b;
   btemp.isnegative=false;
   hugenumber zero;
   while(zero<btemp)
   {
       hugenumber temp_res=*this;
       hugenumber counter(1,1);
       while((counter+counter).LessThanQuantityWise(btemp))
       {
           temp_res+=temp_res;
           counter+=counter;
       }
       result+=temp_res;
       btemp-=counter;
   }
   if(this->isnegative==b.isnegative)
        return result;
    else
        result.isnegative=true;
        return result;
}
hugenumber hugenumber::operator/(const hugenumber &b)const
{
   hugenumber temp=(*this);
  temp.isnegative=false;
   hugenumber result;
   hugenumber zero;
   while(zero<temp)
   {   
       hugenumber counter(1,1);
       hugenumber btemp=b;
       while((btemp+btemp).LessThanQuantityWise(temp))
       {
           counter+=counter;
           btemp+=btemp;

       }
       result+=counter;
       temp-=btemp;
   }
//   if(temp<zero)
//   {
//       temp+=b;
//       hugenumber reminder=temp-zero;
//       cout<<"reminder==="<<reminder;
//   }
   hugenumber a(1,1);
  if(!((result*b)==(*this)))
        result-=a;
   if(this->isnegative==b.isnegative)
        return result;
    else
        result.isnegative=true;
        return result;
}
hugenumber hugenumber::operator%(const hugenumber &b)const
{
    return (*this)-((*this/b)*b);
}
void hugenumber::operator+=(const hugenumber &b)
{
    *this=(*this+b);
}
hugenumber hugenumber::operator-(const hugenumber &b)const
{
    return (*this+(-b));
}
void hugenumber::operator-=(const hugenumber &b)
{
    *this=(*this-b);
}
bool hugenumber::operator<(const hugenumber &b)const
{
    if(this->isnegative==false&&b.isnegative==true)
    {
        return false;
    }
    else if(this->isnegative==true&&b.isnegative==false)
    {
        return true;
    }
    else if(this->isnegative==false&&b.isnegative==false)
    {
        return (*this).LessThanQuantityWise(b);    
    }
    else
        return (*this).GreaterThanQuantityWise(b);    
    
}
bool hugenumber::operator<=(const hugenumber &b)const
{
    return (*this<b) ||(*this==b);
}
bool hugenumber::operator>(const hugenumber &b)const
{
    return b<*this;
}
bool hugenumber::operator>=(const hugenumber &b)const
{
    return (*this>b) ||(*this==b);
}
bool hugenumber::operator==(const hugenumber &b)const
{
    if(this->isnegative==b.isnegative)
        return (*this).EqualQuantityWise(b);
    return false;
}
hugenumber hugenumber::operator-()const
{
    hugenumber a=*this;
    a.isnegative=!a.isnegative;
    return a;
}
ifstream& operator>>(ifstream& rdr,hugenumber &b)
{
    b.load(rdr);
    return rdr;
}
ostream& operator<<(ostream& ,const hugenumber &b)
{
    hugenumber a=b;
    a.print();
    return cout;
}
ofstream& operator<<(ofstream& writer,const hugenumber &b)
{
    for(int i=b.size-1;i>=0;i--)
    {
        writer<<b.dig[i];
    }
    return writer;
}
void hugenumber::operator*=(const hugenumber &b)
{
    *this=*this*b;
}
void hugenumber::operator/=(const hugenumber &b)
{
    *this=*this/b;
}
void hugenumber::operator%=(const hugenumber &b)
{
    *this=*this%b;
}