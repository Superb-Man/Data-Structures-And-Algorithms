#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue{

public:
    virtual ~Queue(){

    }
    virtual void clear() = 0 ;
    virtual void enqueue(const T& item) = 0;
    virtual T dequeue() = 0;
    virtual int length() = 0;
    virtual T frontValue() = 0;
    virtual T rearValue() = 0;
    virtual T leaveQueue() = 0;
};

#endif