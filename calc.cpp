#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "dlist.h"
using namespace std;

class Complex{//a class to represent a complex number
    int real;
    int imag;
    bool isp_real;
    bool isp_imag;
public:
    Complex(int r=0,int i=0){
        real=r;
        imag=i;
        if(r>=0)isp_real=true;
        else isp_real= false;
        if(i>=0)isp_imag=true;
        else isp_imag= false;
    }
    friend Complex operator+(const Complex &c0, const Complex &c1){
        Complex rst;
        rst.real=c0.real+c1.real;
        rst.imag=c0.imag+c1.imag;
        if(rst.real>=0) rst.isp_real= true;
        else rst.isp_real= false;
        if(rst.imag>=0) rst.isp_imag= true;
        else rst.isp_imag= false;
        return rst;
    }
    friend Complex operator-(const Complex &c0, const Complex &c1){
        Complex rst;
        rst.real=c0.real-c1.real;
        rst.imag=c0.imag-c1.imag;
        if(rst.real>=0) rst.isp_real= true;
        else rst.isp_real= false;
        if(rst.imag>=0) rst.isp_imag= true;
        else rst.isp_imag= false;
        return rst;
    }
    friend Complex operator*(const Complex &c0, const Complex &c1){
        Complex rst;
        rst.real=c0.real*c1.real-c0.imag*c1.imag;
        rst.imag=c0.real*c1.imag+c0.imag*c1.real;
        if(rst.real>=0) rst.isp_real= true;
        else rst.isp_real= false;
        if(rst.imag>=0) rst.isp_imag= true;
        else rst.isp_imag= false;
        return rst;
    }
    Complex &operator=(const Complex &c0){
        this->real=c0.real;
        this->imag=c0.imag;
        if(c0.isp_real) this->isp_real= true;
        else this->isp_real= false;
        if(c0.isp_imag) this->isp_imag= true;
        else this->isp_imag= false;
        return *this;
    }
    void print(){
        if(isp_imag) cout<<this->real<<"+"<<this->imag<<"i";
        else cout<<this->real<<this->imag<<"i";
    }
};

int GetLength(const int tmp)
{
    //Requires: an int
    //Return: the length of the int
    int count=0;
    int i=1;
    if(tmp!=0) {
        while (tmp >= i) {
            i = i * 10;
            count++;
        }
        return count;
    }
    else return 1;
}

void Least_two_op(string l, Dlist<Complex> &op){
    //Requires: l is a valid input which requires at least two operands
    //Modifies: the top two element of the stack
    Complex *a;
    Complex *b;
    if(op.isEmpty()){
        cout<<"Not enough operands\n";
        return;
    }
    a=op.removeFront();
    if(op.isEmpty()){
        cout<<"Not enough operands\n";
        op.insertFront(a);
        return;
    }
    b=op.removeFront();
    switch (l[0]){
        case '+':
            *b=*b+*a;
            delete a;
            break;

        case '-':
            *b=*b-*a;
            delete a;
            break;

        case '*':
            *b=*b**a;
            delete a;
            break;

        case 'r':
            op.insertFront(a);
            break;

        default:break;
    }
    op.insertFront(b);
}

void Least_one_op(string l, Dlist<Complex> &op){
    //Requires: l is a valid input which requires at least one operands
    //Modifies: the top one element of the stack
    Complex *a;
    Complex *temp=new Complex;
    if(op.isEmpty()){
        cout<<"Not enough operands\n";
        delete temp;
        return;
    }
    a=op.removeFront();
    switch (l[0]){
        case 'n':
            *a=*temp-*a;//Here b is an defalut complex,0+0i
            delete temp;
            break;

        case 'd':
            *temp=*a;
            op.insertFront(temp);
            break;

        case 'p':
            a->print();
            cout<<"\n";
            delete temp;
            break;

        default:break;
    }
    op.insertFront(a);
}

void All_valid_op(string l, Dlist<Complex> &op){
    //Requires: l is a valid input which is valid all the time
    //Modifies: the stack, or may just print but don't change the stack
    Dlist<Complex> temp;
    temp=op;
    switch (l[0]){
        case 'c':
            while(!op.isEmpty()){
                Complex *a;
                a=op.removeFront();
                delete a;
            }
            break;

        case 'a':
            while(!temp.isEmpty()) {
                Complex *a;
                a = temp.removeFront();
                a->print();
                cout << " ";
                delete a;
            }
            cout<<"\n";

    }
}

void input(string l, Dlist<Complex> &op){
    //Modifies: handle the input and cout, do some change on the stack
    bool good_input=false;
    if(l.length()==1) {
        char c=l[0];
        switch (c) {
            case '+':
                good_input= true;
                Least_two_op(l,op);
                break;
            case '-':
                good_input= true;
                Least_two_op(l,op);
                break;
            case '*':
                good_input= true;
                Least_two_op(l,op);
                break;
            case 'n':
                good_input= true;
                Least_one_op(l,op);
                break;
            case 'd':
                good_input= true;
                Least_one_op(l,op);
                break;
            case 'r':
                good_input= true;
                Least_two_op(l,op);
                break;
            case 'p':
                good_input= true;
                Least_one_op(l,op);
                break;
            case 'c':
                good_input= true;
                All_valid_op(l,op);
                break;
            case 'a':
                good_input= true;
                All_valid_op(l,op);
                break;
            case 'q':
                good_input = true;
                break;

        }
    }
    if(l.length()>=4 && (l[0]=='-' || (l[0]>='0' && l[0]<='9'))){
        unsigned int i=1;
        int r=0;
        int im=0;
        int imag_length=0;
        r=stoi(l);
        string imag_part;
        string i_exam; //this string exam whether there is only a 'i' behind imag part
        while((i<=l.length()-1 && l[i]>='0' && l[i]<='9') || (l[i]=='+' || l[i]=='-')){
            if(l[i]=='+'){
                imag_part=l.substr(i+1,l.length()-i-1);//the following procedures seperate the complex into four part
                im=stoi(imag_part);
                imag_length=GetLength(im);
                i_exam=l.substr(i+imag_length+1,l.length()-i-1-imag_length);
                if(im>=0 && i_exam[0]=='i' && i_exam.length()==1){
                    Complex *a=new Complex(r,im);
                    op.insertFront(a);
                    good_input= true;
                }
            }
            if(l[i]=='-'){
                imag_part=l.substr(i+1,l.length()-i-1);
                im=stoi(imag_part);
                imag_length=GetLength(im);
                i_exam=l.substr(i+imag_length+1,l.length()-i-1-imag_length);
                if(im>=0 && l[l.length()-1]=='i'&& i_exam.length()==1){
                    Complex *a=new Complex(r,-im);
                    op.insertFront(a);
                    good_input= true;
                }
            }
            i++;
        }

    }
    if(!good_input)cout<<"Bad input\n";
}

int main() {
    Dlist<Complex> RPN_list;
    string temp;
    string str;
    while(temp!="q"){
        cin>>str;
        temp=str;
        input(str, RPN_list);
    }
    return 0;
}