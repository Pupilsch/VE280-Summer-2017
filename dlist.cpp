#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#ifndef DLIST_H
#define DLIST_H
#include "dlist.h"
using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const {
    return (first==NULL && last==NULL);
}

template <class T>
void Dlist<T>::insertFront(T *op) {
    node *np=new node;
    np->next=first;
    np->prev=NULL;
    np->op=op;
    if(first!=NULL)first->prev=np;
    if(last==NULL)last=np;
    first=np;
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    node *np=new node;
    np->next=NULL;
    np->prev=last;
    np->op=op;
    if(last!=NULL)last->next=np;
    if(first==NULL)first=np;
    last=np;
}

template <class T>
T* Dlist<T>::removeFront() {
    node *victim=first;
    if(isEmpty()) throw emptyList();
    else{
        T *result=victim->op;
        if(first->next==NULL){
            first=NULL;
            last=NULL;
        } else{
            first=victim->next;
            first->prev=NULL;
        }
        delete victim;
        return result;
    }
}

template <class T>
T* Dlist<T>::removeBack() {
    node *victim=last;
    if(isEmpty()) throw emptyList();
    else{
        T *result=victim->op;
        if(last->prev==NULL){
            first=NULL;
            last=NULL;
        } else{
            last=victim->prev;
            last->next=NULL;
        }
        delete victim;
        return result;
    }
}

template <class T>
void Dlist<T>::removeAll() {
    while(!isEmpty()){
        T *op=removeFront();
        delete op;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l) {
    node *list=l.first;
    while(list){
        T *o=new T(*list->op);
        insertBack(o);
        list=list->next;
    }
    return;
}

template <class T>
Dlist<T>::Dlist(const Dlist &l) {
    first=NULL;
    last=NULL;
    if(this!=&l) {
        copyAll(l);
    }
}

template <class T>
Dlist<T>::Dlist() {
    first=NULL;
    last=NULL;
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if(this!=&l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist() {
    removeAll();
}

#endif