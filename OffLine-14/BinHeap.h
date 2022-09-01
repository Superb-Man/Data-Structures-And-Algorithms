using namespace std ;
typedef long long int ll ;

template<typename T>
struct BinNode{
    T key ;
    ll index ;
};

template<typename T>
class Heap {

private :
    BinNode<T>** _arr ;
    ll _heapsize ;
    ll maxsize ;

    void swap(BinNode<T>*& node1, BinNode<T>*& node2) {
        ll index1 = node1->index;
        ll index2 = node2->index;
        BinNode<T>* temp = node1;
        node1 = node2;
        node2 = temp;
        node1->index = index1;
        node2->index = index2;
        //std::swap(node1,node2) ; eta dileo same kaj kore
    }
    void heapify(ll idx,ll delim) {
        while(true){
            ll smallest = idx ;
            ll leftchild = 2*idx , rightchild = 2*idx + 1 ;
            if(leftchild <= delim && _arr[leftchild]->key < _arr[smallest]->key) {
                smallest = leftchild ;
            }
            if(rightchild <= delim && _arr[rightchild]->key < _arr[smallest]->key) {
                smallest = rightchild ;
            }
            if(smallest != idx) {
                swap(_arr[idx] ,_arr[smallest]) ;
                idx =   smallest ;
            }
            else return ;
        }
        /*ll leftchild = 2*idx;
        ll rightchild = 2*idx+1;
        ll smallest = idx;
        if( leftchild <= delim && _arr[leftchild]<_arr[smallest] )
            smallest = leftchild;
        if( rightchild <= delim && _arr[rightchild] < _arr[smallest] )
            smallest = rightchild;
        if( smallest != idx ){
            swap( _arr[idx],_arr[smallest] );
            heapify(smallest,delim);
        }*/
    }
    void bottomUp(ll idx) {
        ll parent = idx/2 ;
        if(parent == 0) return ;
        while(_arr[idx]->key < _arr[parent]->key  && parent > 0){
            swap(_arr[idx], _arr[parent]) ;
            idx = parent ;
            parent/=2 ;
        }
        /*if(_arr[idx]->key < _arr[parent]->key  && parent > 0){
            swap(_arr[idx], _arr[parent]) ;
            bottomUp(parent/2) ;
        }*/
    }
    BinNode<T>* extractMinNode() {
        BinNode<T>* node = _arr[1] ;
        swap(_arr[1] , _arr[_heapsize]) ;
        _arr[_heapsize] = NULL ;
        _heapsize-- ;
        heapify(1,_heapsize) ;
        //cout << node <<" " <<_arr[1]<< endl;
        return node ;
    }

public:

    Heap(ll _size) {
        _arr = new BinNode<T>*[_size+1] ;
        //maxsize = _size ;
        _heapsize = 0 ;

    }

    BinNode<T>* insert(T& data) {
        BinNode<T>* node = new BinNode<T> ;
        node->key = data ;
        node->index = _heapsize+1 ;
        _arr[++_heapsize] = node ;
        bottomUp(_heapsize) ;

        return node ;
    }

    BinNode<T>* getMin(){
        return _arr[1] ;
    }

    void decreaseKey(BinNode<T>*& node, T& newKey){
        node->key = newKey;

        bottomUp(node->index);
    }

    T extractMin() {
        BinNode<T>* node  = extractMinNode() ;
        //cout << node << endl<<endl;
        return node->key ;
    }

    void deleteKey() {
        //
    }
    ll size() {
        return _heapsize ;
    }

    ~Heap() {
        delete [] _arr ;
    }

};
