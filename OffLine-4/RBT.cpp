#include<iostream>
#include<vector>
using namespace std ;
template <typename T>
struct node {
    node<T>* left ;
    node<T>* right ;
    node<T>* parent ;
    T item ;
    int color ;
    int nodes_count ;

    node() {
        left = right = parent = NULL ;
        nodes_count = 0 ;
    }
    node(T item) {
        this->item = item ;
        left = right = parent = NULL ;
        nodes_count = 0 ;
    }

} ;

template <typename T>
class RBT{
    node<T>* root ;
    node<T>* NIL ;

    //Slide + Cormen

    int color(node<T>* x) {
        if(x == NULL || x == NIL) return 0 ;
        else return x->color ;
    }

    void left_rotate(node<T>* x) {
        node<T>* y = x->right ;
        x->right = y->left ;
        if(y->left != NIL)  y->left->parent = x ;
        y->parent = x->parent ;
        if(x->parent == NIL)
            root = y ;
        else if(x == x->parent->left)
            x->parent->left = y ;
        else x->parent->right = y ;
        int yleft = y->left->nodes_count ;
        y->left = x ;
        x->parent = y ;
        int cnt  = x->nodes_count ;
        x->nodes_count = x->nodes_count - y->nodes_count + yleft  ;
        y->nodes_count = cnt ;
    }

    void right_rotate(node<T>* x) {
        node<T>* y = x->left ;
        x->left = y->right ;
        if(y->right != NIL) y->right->parent = x ;
        y->parent = x->parent ;
        if(x->parent == NIL)
            root = y ;
        else if(x == x->parent->right)
            x->parent->right = y ;
        else x->parent->left = y ;
        int yright = y->right->nodes_count ;
        y->right = x ;
        x->parent = y ;
        int cnt  = x->nodes_count ;
        x->nodes_count = x->nodes_count - y->nodes_count + yright  ;
        y->nodes_count = cnt ;
    }

    void insert_Fix_Up (node<T>* z) {
        while(color(z->parent)) {
            if(z->parent == z->parent->parent->left) {
                node<T>* y = z->parent->parent->right ; //y is the uncle
                if(color(y)) {
                    z->parent->color = 0 ;
                    y->color = 0 ;
                    z->parent->parent->color = 1 ;
                    z = z->parent->parent ;
                }
                else {
                    if(z == z->parent->right) {
                        z = z->parent ;
                        left_rotate(z) ;
                    }
                    z->parent->color = 0 ;
                    z->parent->parent->color = 1 ;
                    right_rotate(z->parent->parent) ;
                }
            }
            else{
                node<T>* y = z->parent->parent->left ; //y is the uncle
                if(color(y)) {
                    z->parent->color = 0 ;
                    y->color = 0 ;
                    if(y == NIL) {}
                    z->parent->parent->color = 1 ;
                    z = z->parent->parent ;
                }
                else {
                    if(z == z->parent->left) {
                        z = z->parent ;
                        right_rotate(z) ;
                    }
                    z->parent->color = 0 ;
                    z->parent->parent->color = 1 ;
                    left_rotate(z->parent->parent) ;
                }

            }
            if(z == root) break ;
        }

        root->color = 0 ;
        root->parent = NIL ;

    }

    node<T>* insert_helper(T item) {
        node<T>* y = NIL ;
        node<T>* x = root ;
        if(find(item) == true) return NULL ;
        node<T>* z = new node<T>(item) ;
        z->right = z->left = NIL ;
        while(x != NIL) {
            y = x ;
            x->nodes_count++ ;
            if(z->item < x->item) {
                x = x->left ;
            }
            else if (z->item > x->item) {
                x = x->right ;
            }
        }
        //cout <<"Insert successful"<<endl;

        z->parent = y ;
        z->nodes_count = 1 ;
        if (y == NIL) {
            root = z ;
        }
        else if(z->item < y->item) {
            y->left = z ;
        }
        else y->right = z ;
        z->color = 1 ;
        insert_Fix_Up(z) ;

        return z ;
    }

    node<T>* find_helper(T item) {
        node<T>* temp = root ;
        while (true)
        {
            if (temp == NIL) return NULL ;
            if(item < temp->item)   temp = temp->left ;
            else if(item > temp->item)  temp = temp->right ;
            else return temp ;
        }

    }

    node<T>* getMin(node<T>* x , int param = 0) {
        x = x->right ;
        while(x->left != NIL) {
            x = x->left ;
        }

        return x ;
    }

    bool delete_helper(T item) {
        node<T>* z = find_helper(item) ;
        node<T>* y = z ;
        node<T>* x = NIL ;
        if(z == NULL) {
            //cout <<"No elements \n" ;
            return false ;
        }
        if(z->left == NIL || z->right == NIL){
            y = z ;
            node<T>* t = y ;
            while(t!=NIL) {
                t = t->parent ;
                if(t != NIL) t->nodes_count-- ;
            }
            //cout <<"HERE" <<y->item<<endl;
        }
        else{
            y = getMin(z) ;
            node<T>* t = y ;
            while(t!=NIL) {
                t = t->parent ;
                if(t != NIL) t->nodes_count-- ;
            }
        }

        if(y->left != NIL)   x = y->left ;
        else  x = y->right ;

        x->parent = y->parent ;
        if(y->parent == NIL) root = x ;

        else if( y == y->parent->left)
            y->parent->left = x ;
        else
            y->parent->right = x ;

        swap(y->item,z->item) ;
        if(color(y) == 0) delete_Fix_Up(x) ;

        delete y ;

        return true ;


    }

    void delete_Fix_Up(node<T>* x) {
        while (!color(x) && root != x) {
            if(x == x->parent->left) {
                node<T>* w = x->parent->right ;
                if(color(w)) {
                    w->color = 0 ;
                    x->parent->color = 1 ;
                    left_rotate(x->parent) ;
                    w = x->parent->right ;
                }
                if(color(w->left) == 0 && color(w->right) == 0) {
                    w->color = 1 ;
                    x = x->parent ;
                }

                else {
                    if(color(w->right) == 0) {
                        w->left->color = 0 ;
                        w->color = 1 ;
                        right_rotate(w) ;
                        w = x->parent ;
                    }
                    w->color = x->parent->color ;
                    x->parent->color = 0 ;
                    w->right->color = 0 ;
                    left_rotate(x->parent) ;
                    x = root ;
                }
            }
            else {
                node<T>* w = x->parent->left ;
                if(color(w)) {
                    w->color = 0 ;
                    x->parent->color = 1 ;
                    right_rotate(x->parent) ;
                    w = x->parent->left ;
                }
                if(color(w->right) == 0 && color(w->left) == 0) {
                    w->color = 1 ;
                    x = x->parent ;
                }

                else {
                    if(color(w->left) == 0) {
                        w->right->color = 0 ;
                        w->color = 1 ;
                        left_rotate(w) ;
                        w = x->parent ;
                    }
                    w->color = x->parent->color ;
                    x->parent->color = 0 ;
                    w->left->color = 0 ;
                    right_rotate(x->parent) ;
                    x = root ;
                }

            }
        }
        x->color  = 0 ;

    }
    void removeSubTree(node<T>* _root){
        if(_root == NIL ) return ;
        removeSubTree(_root->left) ;
        removeSubTree(_root->right) ;

        //deleting nodes
        delete _root ;
    }


public :
    RBT() {
        NIL = new node<T> ;
        NIL->parent = NIL->left = NIL->right = NULL ;
        NIL->color = 0 ;
        root = NIL ;
    }

    bool insert(T item) {
        node<T>* nod = insert_helper(item) ;
        if(nod != NULL) return true ;
        else return false ;
    }
    bool delete_key(T item) {
        if(delete_helper(item) == false) return false ;
        else return true ;
    }
    void inorder(node<T>* temp,vector<T>& vec) {
        if(temp != NIL){
            inorder(temp->left , vec);
            vec.push_back(temp->item) ;
        //cout << "--> " << temp->item << "<" << temp->color << ">";
            inorder(temp->right, vec);
        }
    }
    void preorder(node<T>* temp) {
        if(temp == NIL){ return; }
        cout << "--> " << temp->item << "<" << temp->color << ">";
        preorder(temp->left);
        preorder(temp->right);
    }
    bool find(T item) {
        return (find_helper(item) != NULL ? true : false) ;
    }

    int less(T item){
        node<T>* temp = root ;
        int cnt = 0 ;
        //int xx = 0 ;
        NIL->nodes_count = 0 ;
        while(temp != NIL) {
            if(item > temp->item){
                cnt+=temp->left->nodes_count + 1  ;
                temp = temp->right ;
            }
            else if(item <= temp->item) {
                temp = temp->left ;
            }
        }

        return cnt  ;
    }

    void preorder() {preorder(root) ;}
    int inorder(T item){
        vector<T>vec ;
        inorder(root,vec) ;
        int cnt  = 0 ;
        for(int i = 0 ; i < vec.size() ; i++) {
            if(item > vec[i]) cnt++ ;
        }

        return cnt ;
    }

    ~RBT() {
        removeSubTree(root) ;
        delete NIL ;
    }
} ;

/*int main() {
    RBT<int>tree ;
    tree.insert(5) ;
    tree.insert(4) ;
    tree.insert(3) ;
    tree.insert(7) ;
    //if(tree.find(1) == false)    tree.insert(1) ;
    //tree.insert(113) ;
    cout << endl;
    //tree.delete_key(1) ;
    tree.preorder() ;
    cout << endl;
    tree.delete_key(0) ;
    //if(tree.find(1) == false) tree.insert(1) ;
    tree.preorder() ;
    cout << tree.less(5) << endl;
    cout << endl ;
}*/
