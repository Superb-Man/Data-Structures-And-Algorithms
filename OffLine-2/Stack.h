#ifndef Stack_H
#define Stack_H

#include<iostream>

template <typename T>
class Stack{

public:
    virtual ~Stack(){

    }
    virtual void clear() = 0;
    virtual void push(const T& item) = 0;
    virtual T pop() = 0;
    virtual int length() const = 0;
    virtual T& topValue() const = 0;
    virtual void setDirection(int _dir) = 0;
};

#endif