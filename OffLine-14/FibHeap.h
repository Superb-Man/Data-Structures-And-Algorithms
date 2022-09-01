#include <iostream>
#include <vector>
#include<math.h>
#include<list>

typedef long long int ll ;

template<typename T>
struct FibHnode{
    T key ;
    int degree ;
    FibHnode<T>* left ;
    FibHnode<T>* right ;
    FibHnode<T>* child ;
    FibHnode<T>* parent ;
    bool marked ;
    int id ;
    FibHnode() {

    }
    FibHnode(T key) {
        this->key = key;
        this->left = this->right = this;
        this->parent = NULL ;
        this->child = NULL ;
        this->degree = 0;
        this->marked = false;

    }

} ;

template <typename T>
class FibHeap{
	void insertNode(FibHnode<T>*) ; // To insert a node in the root list
	void removeNode(FibHnode<T>* ) ; //remove a node from the root list
	FibHnode<T>* concatenate(FibHnode<T>*  , FibHnode<T>* ); // concatenate two nodes in the root lists
	void link(FibHnode<T>* , FibHnode<T>*) ; // make child-parent relation :)
	void consolidate(); // To upgrade the heapTree
	void disconnectAll(FibHnode<T>* ); // disconnect the child from parent
	FibHnode<T>* extractMinNode(); // return the node with minimum key
	void cut(FibHnode<T>* , FibHnode<T>* );
	void cascadeCut(FibHnode<T>* );
	void clearAll(FibHnode<T>* ); // delete all nodes

public :
	FibHnode<T>* min ;
    int n ;
	FibHeap() {
		min = NULL ;
		n = 0 ;
	}
	~FibHeap(){
		clearAll(min) ;
	}

	FibHnode<T>* insert(T ) ;
	void unionHeaps(FibHeap<T>& ) ;
	T extractMin() ;
	void decreaseKey(FibHnode<T>* , T) ; // decrease the key of a particular node
	void deleteNode(FibHnode<T>* ) ; // delete a particular node
	T getMin() ; // return min key
	int& nodeCount() ; // don't need this function
} ;

template<typename T>
void FibHeap<T> :: insertNode(FibHnode<T>* newNode) {
	min = concatenate(min, newNode); // insert a node and then merge
	n++;
}

template<typename T>
void FibHeap<T> :: unionHeaps(FibHeap<T>& h2){
    min = concatenate(min ,h2.min) ;
    n = n + h2.nodeCount() ;
    h2.min = NULL ;
    h2.n = 0 ;
}

template<typename T>
T FibHeap<T> :: extractMin(){
    FibHnode<T>* mini = extractMinNode() ;
    T val = mini->key ;   delete mini ;
    //std::cout << "---------minValue--------" << std :: endl ;
    return val ;
}

template<typename T>
void FibHeap<T> :: decreaseKey(FibHnode<T>* node, T key) {
	node->key = key; //set the key
    FibHnode<T>* b = node->parent ;
    if(b != NULL && b->key > node->key ) {
		cut(node,b); // use the cut method to just cut the node and mark the parent
		cascadeCut(b); //if the parent is already marked before cut then remove it too.
	}
	if(node->key < min->key)    min = node ; // update the min_node
	//std :: cout <<"--------Decrease-Key-----" << '\n' ;
}

template<typename T>
void FibHeap<T> :: deleteNode(FibHnode<T>* node) {
    //decreaseKey(node, (node->key)-(1e8+100)) ;
    //extractMin() ;
}

template<typename T>
T FibHeap<T> :: getMin() {
    return min->key ;
}

template<typename T>
int& FibHeap<T> :: nodeCount() {
    return n ;
}


template<typename T>
void FibHeap<T> :: removeNode(FibHnode<T>* x){
    if(x->right == x) return ; //is already isolated
    else{
        //isolating node x
        FibHnode<T>* lsb = x->left ;
        FibHnode<T>* rsb = x->right ;
        lsb->right = rsb ;
        rsb->left  = lsb ;
        x->right = x->left = x ; // isolation done
        //std :: cout <<"-----removeNode------" << '\n' ;
    }
}

template<typename T>
FibHnode<T>* FibHeap<T> :: concatenate(FibHnode<T>* x , FibHnode<T>* y) {
    //If only one node exists
    if(x == NULL) return y ;
    if(y == NULL) return x ;
    // If x.key > y.key then swap and think the min_node tree in the left
    if(x->key > y->key){
        FibHnode<T>* temp = x ; x = y ; y = temp ;
    }

    FibHnode<T>* xr = x->right ; FibHnode<T>* yl = y->left ;
    x->right = y ;
    y->left = x ;
    xr->left = yl ;
    yl->right = xr ;

    //std :: cout << "------concatenate-----" <<'\n' ;

    return x ;
}

template<typename T>
void FibHeap<T> :: link(FibHnode<T>* c, FibHnode<T>* p) {
    //c's parent is p
    //p's child is = remaining p's child union c
    //increase the degree
    //newly linked , so child should be unmarked
    c->parent = p ;
    p->child  = concatenate(p->child , c) ;
    p->degree = p->degree + 1 ;
    c->marked = false ;
}

template<typename T>
void FibHeap<T> :: disconnectAll(FibHnode<T>* node){
    if(node == NULL)    return;
	FibHnode<T>* temp = node ;
    temp->parent = NULL ;   //setting parent = NIL
	temp = temp->right ;
	while(temp != node) {
        temp->parent = NULL ;   //setting parent = NIL
	    temp = temp->right ;    //Going to right siblings
    }

    //std :: cout <<"----------disconnectAll--------" << '\n' ;
}

template<typename T>
FibHnode<T>* FibHeap<T> :: extractMinNode() {
    FibHnode<T>* mini = min ;
    if(mini == NULL) return NULL ;
    disconnectAll(mini->child) ;    //set the parent to NULL

    concatenate(mini, mini->child) ;    //Now merge two nodes
    if(mini == mini->right) min = NULL ;    //only mini node remaining
    else min = mini->right ; //set the min to right of mini
    removeNode(mini) ;  //remove the mini node from the root


    if(min != NULL) consolidate() ;    // now consolidate because min = mini->right might not be the min node

    //decrease the number of nodes
    n-- ;

    //std :: cout <<"--------extractMin-------"<< '\n' ;

    return mini ;
}

template<typename T>
void FibHeap<T> :: consolidate() {
    ll d = (ll) (log2(n) /log2(1.618)) ; //sonali onupat
    //implementing as Sar Cormen says
    FibHnode<T>** A = new FibHnode<T>*[d+1] ;
    for(int i = 0 ; i< d + 1 ; i++) {
        A[i] = NULL ;
    }
    ll idx = 0 ;
    FibHnode<T>* node = min ;
    node = node->right ;
    idx++ ;
    while(node != min) {
        node = node->right ; idx++ ;
    }

    FibHnode<T>** nodes = new FibHnode<T>*[idx] ;
    idx = 0 ;
    //making a list of nodes from min_node to min_node->left in circular way
    node = min ;
    nodes[idx++] = node ;
    node = node->right ;
    while(node != min) {
        nodes[idx++] = node ;
        node = node->right ;
    }
    //FibHnode<T>* eu : nodes
    //std::cout << nodes.size() <<std :: endl;
    for(ll i = 0 ; i < idx ; i++) {
        FibHnode<T>* eu = nodes[i] ;
        int deg = eu->degree ;
        removeNode(eu) ; //removing from root because later we will concatenate all after consolidating
        while(A[deg] != NULL) {
            FibHnode<T>* temp = A[deg] ;
            if(eu->key > temp->key ) {
                FibHnode<T>* t =eu ;
                eu = temp ;
                temp = t ;
            }

            link(temp ,eu) ;
            A[deg] = NULL ;
            deg++ ;
        }
        A[eu->degree] =eu ;
        min  =eu ;
    }
    // Now concatenate the nodes
    for(int i = 0 ; i < d + 1 ; i++) {
        if(A[i] != NULL && A[i] != min) {
            concatenate(min, A[i]) ;
        }
    }

    //update the min_node
    FibHnode<T>* x = min ;
    FibHnode<T>* y = x ;
    if(min->key > y->key) min = y ;
    y = y->right ;
    while(y != x){
        if(min->key > y->key) min = y ;
        y = y->right ;
    }

    //std :: cout <<"-----------Consolidate----------" << '\n' ;
    delete []A ;
    delete []nodes ;

}

template<typename T>
void FibHeap<T> :: cut(FibHnode<T>* a, FibHnode<T>* b) {
    if( a == a->right ) b->child = NULL ; //had only one child
    else  b->child = a->right ; // point to the chilld's right sibling

    removeNode(a) ; // isolate a from tree
    b->degree = b->degree -1 ;
    concatenate(min , a) ; //Concatenate two tree
    a->parent = NULL ; //because it's in the root list
    a->marked = false ; //newly linked to the rootlist

    //std :: cout << "-------cut------" <<'\n' ;
}


//Sar Cormen says :
template<typename T>
void FibHeap<T> :: cascadeCut(FibHnode<T>* a ){
    FibHnode<T>* b = a->parent;
	if (b != NULL) {
		if(!(a->marked))
			a->marked = true ;
        else{
		    cut(a,b) ;
		    cascadeCut(b) ;
	    }
    }
}

template<typename T>
FibHnode<T>* FibHeap<T> :: insert(T key) {
	FibHnode<T>* node = new FibHnode<T>(key) ;
	insertNode(node) ;
	return node ;
}


//to delete all node start from the min

template<typename T>
void FibHeap<T> :: clearAll(FibHnode<T>* node) {
	if (node) {
		FibHnode<T>* temp = node ;
        FibHnode<T>* temp2 = temp ;
		temp = temp->right ;
		clearAll(temp2->child) ;
		delete temp2 ;
		while(temp != node) {
            FibHnode<T>* temp = node ;
            FibHnode<T>* temp2 = temp ;
		    temp = temp->right ;
		    clearAll(temp2->child) ;
		    delete temp2 ;
		}
	}
}
