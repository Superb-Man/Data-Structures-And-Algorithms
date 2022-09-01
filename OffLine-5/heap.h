using namespace std ;


template<typename T>
class Heap {
    T* _arr ;
    int _heapsize ;
    int maxsize ;

    void bottom_up(int idx) {
        int parent = idx/2 ;
        if(parent == 0) return ;
        if(_arr[parent] < _arr[idx]){
            swap(_arr[idx], _arr[parent]) ;
            bottom_up(parent) ;
        }
        
    }

    void heapify(int idx,int delim) {
        while(true){
            int smallest = idx ;
            int leftchild = 2*idx , rightchild = 2*idx + 1 ;
            if(leftchild >= delim && _arr[leftchild] < _arr[smallest]) {
                smallest = leftchild ;
            }
            if(rightchild >= delim && _arr[rightchild] < _arr [smallest]) {
                smallest = rightchild ;
            }
            if(smallest != idx) {
                swap(_arr[idx] ,_arr[smallest]) ;
                idx =   smallest ;
            }
            else return ;
        }
        /*int leftchild = 2*idx;
        int rightchild = 2*idx+1;
        int smallest = idx;
        if( leftchild <= delim && _arr[leftchild]>_arr  smallest] )
            smallest = leftchild;
        if( rightchild <= delim && _arr[rightchild] > _arr  smallest] )
            smallest = rightchild;
        if( smallest != idx ){
            swap( _arr[idx],_arr    smallest] );
            heapify smallest,delim);
        }*/
    }
    void build_max_heap(int* array, int _size){
        for(int i = _size/2 ; i>=1 ;i--){
            heapify(i,_size) ; 
        }
    }

public:

    Heap(int _size) {
        _arr = new int[_size+1] ;
        maxsize = _size ;
        _heapsize = 0 ;

    }

    Heap<T>(vector<int>&vec){
        _arr = new T[vec.size()+1] ;
        _heapsize = 0 ;
        maxsize = vec.size() ;
        for(int i = 0 ; i< vec.size() ;i++){
            _arr[++_heapsize] = vec[i] ;
        }
        build_max_heap(_arr,_heapsize) ;
    }
    
    void insert(int data) {
        if( _heapsize == maxsize ) {
            cout<<"-----------Error! Array is full!-------------"<<endl;
            return ;
        }
        _arr[++_heapsize] = data ;
        bottom_up(_heapsize) ;
    }
    
    int extractMin() {
        return _arr[1] ;
    }

    void deleteKey() {
        if(_heapsize < 1) {
            cout <<"------------Empty array-----------" <<endl;
            return ;
        }
        swap(_arr[_heapsize] , _arr[1]) ;
        _heapsize-- ;
        heapify(1 , _heapsize) ;
    }
    int size() {
        return _heapsize ;
    }
    ~Heap() {
        delete [] _arr ;
    }

};

void heapsort(vector<int>& v)
{
  Heap heap(v);
  for(int i = 0 ; i< v.size() ;i++)
  {
      v[i] = heap.getMax() ;
      heap.deleteKey();
  }
}