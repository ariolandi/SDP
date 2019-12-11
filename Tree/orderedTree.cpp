#ifndef ORDERED_TREE_H_
#define ORDERED_TREE_H_
#include <stack>
#include <utility>
using std::stack;

//OrderedTree class
//has one field: pointer to the root of the tree
template <typename T>
class OrderedTree{
    private:
        struct Node;
        Node* root;
        void deleteNode(Node*);
        OrderedTree<T>::Node* copyNode(Node*);
        void addTo(Node*, const T&);
    public:
        OrderedTree(const T&);
        OrderedTree(const OrderedTree<T>&);
        OrderedTree<T>& operator=(const OrderedTree<T>&);
        ~OrderedTree();
        class Iterator;

        const OrderedTree<T>::Iterator begin();
        void add(const T&);
};

//the structure of a tree's element
//each element has a value field and two pointers (to the left and right child)
template <typename T>
struct OrderedTree<T>::Node{
    T value;
    Node *left, *right;
    Node(const T& v):value(v){
        right = left = nullptr;
    }
    bool has_left()const{return left!=nullptr;}
    bool has_right()const{return right!=nullptr;}
};

//class Iterator
//field: a stack of tree's elements in order to be traversed
//implements inorder (left-root-right) iteratorion
template <typename T>
class OrderedTree<T>::Iterator{
    private:
        stack<pair<Node*, bool> > nodes;
    public:
        Iterator(){};
        Iterator(Node*);
        Iterator(const OrderedTree<T>::Iterator&);
        bool operator++();
        T& operator*()const;

    friend class OrderedTree<T>;
};

//------------------------------------------------------------

//delete function
//for each node deletes the two children (if has any) and then the node itself
template <typename T>
void OrderedTree<T>::deleteNode(Node* node){
    if(node->has_left()){
        deleteNode(node->left);
    }
    if(node->has_right()){
        deleteNode(node->right);
    }
    delete[] node;
}

//copy function
//recursively copies the left and right child
template <typename T>
typename OrderedTree<T>::Node* OrderedTree<T>::copyNode(Node* node){
    Node *newNode = new Node(node->value);
    if(node->has_left()){
        newNode->left=copyNode(node->left);
    }
    if(node->has_right()){
        newNode->right=copyNode(node->right);
    }
    return newNode;
}

//add function
//adds bigger (or equal) values in the right child
//and lower values in the left child
template <typename T>
void OrderedTree<T>::addTo(Node* node, const T& value){
    if (node->value > value){
        if(node->has_left())addTo(node->left, value);
        else node->left = new Node(value);
    }
    else if(node->has_right())addTo(node->right, value);
    else node->right = new Node(value);
}


//constructor
template <typename T>
OrderedTree<T>::OrderedTree(const T& value){
    root = new Node(value);
}

//copy constructor
template <typename T>
OrderedTree<T>::OrderedTree(const OrderedTree<T>& other){
    root = copyNode(other.root);
}

//assignment operator
template <typename T>
OrderedTree<T>& OrderedTree<T>::operator=(const OrderedTree<T>& other){
    if(this!=&other){
        deleteNode(root);
        root = copyNode(other.root);
    }
    return *this;
}

//destructor
template <typename T>
OrderedTree<T>::~OrderedTree(){
    deleteNode(root);
}

//returns an iterator to the root
template <typename T>
const typename OrderedTree<T>::Iterator OrderedTree<T>::begin(){
    return Iterator(root);
}

//add function
//adds a value in the tree
template <typename T>
void OrderedTree<T>::add(const T& value){
   addTo(root, value);
}

//---------------------------------------------------------------------

//constructor from node
template <typename T>
OrderedTree<T>::Iterator::Iterator(Node* node){
    if(node->has_right()){
        nodes.push(make_pair(node->right, 0));
    }
    nodes.push(make_pair(node, 1));
    if(node->has_left()){
        nodes.push(make_pair(node->left, 0));
    }
}

//copy constructor
template <typename T>
OrderedTree<T>::Iterator::Iterator(const OrderedTree<T>::Iterator& other){
    nodes = other.nodes;
}

//moving operator
//on each move the most left untraversed node
//returns false if there is no more untraversed nodes in the OrderedTree
template <typename T>
bool OrderedTree<T>::Iterator::operator++(){
    pair<Node*, bool> current = nodes.top();
    nodes.pop();

    if(current.second == 1)return !nodes.empty();

    Node *node = current.first;
    while(node->has_left()){
        if(node->has_right())nodes.push(make_pair(node->right, 0));
        nodes.push(make_pair(node, 1));
        node = node->left;
    }
    return !nodes.empty();
}

//dereferencing operator
//returns the value of the pointed node (the one on the top of traversing order)
template <typename T>
T& OrderedTree<T>::Iterator::operator*()const{
    return nodes.top().first->value;
}


#endif // ORDERED_TREE_H_
