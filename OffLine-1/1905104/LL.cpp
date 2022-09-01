#include<iostream>
#include"LL.h"


template<typename T>
void print(List<T> &list){
    int cur = list.currPos() ;
    int size = list.length() ;
    std:: cout <<"<" ;
    if(size != 0){
        list.moveToStart() ;
        int i = 0 ;
        while( i++ < size){
            if(cur == i-1) std::cout <<"| " ;
            std::cout << list.getValue() << " " ;
            list.next() ;
        }
        list.moveToPos(cur) ;
    }
    std::cout <<">\n" ;
}

int main()
{

    int k, x, value ,ara[50];
    std::cin >> k >> x;
    for (int i = 0; i < k; i++) std::cin >> ara[i];
    LList<int> llist(ara, k, x);
    print(llist);

    int q, n;
    while (true)
    {
        std::cin >> q >> n;

        if (q == 0)
            break;

        switch (q) {
        case 1:
            llist.clear();
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 2:
            llist.insert(n);
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 3:
            llist.append(n);
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 4:
            value = llist.remove();
            print(llist);
            std::cout << value << std::endl;
            break;

        case 5:
            llist.moveToStart();
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 6:
            llist.moveToEnd();
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 7:
            llist.prev();
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 8:
            llist.next();
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 9:
            print(llist);
            std::cout << llist.length() << std::endl;
            break;

        case 10:
            print(llist);
            std::cout << llist.currPos() << std::endl;
            break;

        case 11:
            llist.moveToPos(n);
            print(llist);
            std::cout << -1 << std::endl;
            break;

        case 12:
            print(llist);
            std::cout << llist.getValue() << std::endl;
            break;

        case 13:
            print(llist);
            std::cout << llist.Search(n) << std::endl;
            break;

        default:
            break;
        }
    }

    return 0;
}