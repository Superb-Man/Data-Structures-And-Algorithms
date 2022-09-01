#include<iostream>
#include"LQueue.h"
#include"ArrQueue.h"

struct Customer{
    int entry_time ;
    int service_time ;
};

void respond(Queue<Customer> &q1, Queue<Customer> &q2 , int& end_time1 , int& end_time2 , int entry, int booth){
    if(end_time1 <= entry && q1.length())  {
        //std::cout << "booth " <<(booth%2 == 0 ? 2 : 1) << " : Current customer is leaving at " <<end_time1 <<'\n' ;
        q1.dequeue() ;
    }
    if(q2.length() -1 > q1.length()) {
        //std::cout << "Queue " <<((booth+1)%2 == 0 ? 2 : 1) << " last entered Customer switching to queue " <<(booth%2 == 0 ? 2 : 1) <<" at " << end_time1 <<'\n' ;
        q1.enqueue(q2.leaveQueue()) ;
    }
    if(end_time2 <= entry && q2.length()) {
        //std::cout << "booth " << ((booth+1)%2 == 0 ? 2 : 1) << " : Current customer is leaving at " <<end_time2 <<'\n' ;
        q2.dequeue() ;
    }
    if(q1.length() -1 > q2.length())  {
        //std::cout << "Queue " <<(booth%2 == 0 ? 2 : 1) << " last entered Customer switching to queue " <<((booth+1)%2 == 0 ? 2 : 1) <<" at " << end_time2 <<'\n' ;
        q2.enqueue(q1.leaveQueue()) ;
    }
}

void updateAllQueue(Queue<Customer> &q1, Queue<Customer> &q2 ,int& end_time1 ,int entry ,Customer& c , int booth){

    if(end_time1 == entry && q1.length()) {
        //std::cout << "booth " <<(booth%2 == 0 ? 2 : 1) << " : Current customer is leaving at " <<end_time1 <<'\n' ;
        q1.dequeue() ;
    }
    if(q2.length() -1 > q1.length() ){
        if(end_time1 < entry){
            if(q2.length() -1 > 0){
                //std::cout << "Queue " <<((booth+1)%2 == 0 ? 2 : 1) << " last entered Customer switching to queue " <<(booth%2 == 0 ? 2 : 1) <<" at " << end_time1 <<'\n' ;
                q1.enqueue(q2.leaveQueue()) ;
            }
            q1.enqueue(c) ;
            //std::cout << "Queue " <<(booth%2 == 0 ? 2 : 1) << " new customer entered at " << entry <<'\n' ;
        }
        else {
            q1.enqueue(c) ;
            //std::cout << "Queue " <<(booth%2 == 0 ? 2 : 1) << " new customer entered at " << entry <<'\n' ;
            if(q2.length() - 1 > 0){    
                //std::cout << "Queue " <<((booth+1)%2 == 0 ? 2 : 1) << " last entered Customer switching to queue " <<(booth%2 == 0 ? 2 : 1) <<" at " << end_time1 <<'\n' ;
                q1.enqueue(q2.leaveQueue()) ;
            }
        }
    }
    else {
        q1.enqueue(c) ;
        //std::cout << "Queue " <<(booth%2 == 0 ? 2 : 1) << " new customer entered at " << entry <<'\n' ;
    }
    end_time1 = entry + q1.frontValue().service_time ;    
}

int main(){
    LQueue<Customer> queue_1 , queue_2 ;
    int N , end_time1 = -1, end_time2 = -1;
    std:: cin >> N ;
    for(int i = 0 ; i<=N ;i++){
        int entry , service ;
        Customer customer ;

        if(i != N) {
            std::cin >> entry >> service ;
            customer.entry_time = entry ;
            customer.service_time = service ;
        }
        if(i == N ) entry = std::max(end_time1,end_time2) + 1;


        while((queue_1.length() && end_time1 < entry) || (end_time2 < entry && queue_2.length()) || i==N){

            if(end_time2 < end_time1){
                respond(queue_2, queue_1, end_time2, end_time1 ,entry , 2) ;
            }
            else {
                respond(queue_1, queue_2, end_time1, end_time2 ,entry , 1) ;
            }

            //std::cout << "Queue 1 members : " <<queue_1.length() << '\n' ;
            //std::cout << "Queue 2 members : " <<queue_2.length() << '\n' ;
            if(end_time1 <= entry && queue_1.length())  end_time1+=queue_1.frontValue().service_time ;
            if(end_time2 <= entry && queue_2.length())  end_time2+=queue_2.frontValue().service_time ;

            if(i == N) entry = std::max(end_time1 , end_time2) ;

            if(queue_1.length() == 0 && queue_2.length() == 0) break; 


        }
        if(i == N) {
            //std::cout << "booth 1 endtime : " <<end_time1 <<'\n' ;
            //std::cout << "booth 2 endtime : " <<end_time2 <<'\n' ;
            break;
        } 

        if(end_time1 <= entry){
            updateAllQueue(queue_1, queue_2, end_time1, entry, customer, 1) ;
        }

        else if(end_time2 <= entry){
            updateAllQueue(queue_2, queue_1, end_time2, entry, customer, 2) ;   
        }

        else if(end_time1 > entry || end_time2 > entry){
            if(queue_2.length() >= queue_1.length()){
                queue_1.enqueue(customer) ;
                //std::cout << "Queue 1" << " new customer entered at " << entry <<'\n' ;
            }
            else {
                queue_2.enqueue(customer) ;
                //std::cout << "Queue 2" << " new customer entered at " << entry <<'\n' ;
            }
        }

        //std::cout << "Queue 1 members : " <<queue_1.length() << '\n' ;
        //std::cout << "Queue 2 members : " <<queue_2.length() << '\n' ;
        //std::cout << "booth 1 endtime : " <<end_time1 <<'\n' ;
        //std::cout << "booth 2 endtime : " <<end_time2 <<'\n' ;


    }
    std::cout <<"Booth 1 finishes Service at " << end_time1 <<'\n' ;
    std::cout <<"Booth 2 finishes Service at " << end_time2 <<'\n' ;

}

/*10
2 5
3 6
5 10
6 5
8 6
9 3
10 5
12 7
15 5
16 4*/
/*10
2 35
3 4
4 5
7 4
38 11
46 3
49 1
52 3
53 4
60 5*/
//./Offline-3/Bank.exe

