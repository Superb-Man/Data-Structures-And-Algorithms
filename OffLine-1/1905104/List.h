#ifndef List_h
#define List_h

template<typename T>
class List{
    public:

    virtual ~List(){

    }
    virtual void clear() =0 ;
    virtual void insert(const T&) = 0;
    virtual void append(const T&) = 0;
    virtual T remove() = 0;
    virtual void moveToStart()  = 0;
    virtual void moveToEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual int length()const = 0;
    virtual int currPos() = 0;
    virtual void moveToPos(int) = 0;
    virtual T getValue()const = 0;
    virtual int Search(const T&) = 0;
};

#endif