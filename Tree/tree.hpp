#ifndef TREE_H_
#define TREE_H_
#include <stack>
#include <utility>
using std::stack;

//Tree class
//has one field: pointer to the root of the tree
template <typename T>
class Tree{
    private:
        struct Node;
        Node* root;
        void deleteNode(Node*);
        Tree<T>::Node* copyNode(Node*);
    public:
        Tree(const T&);
        Tree(const Tree<T>&);
        Tree<T>& operator=(const Tree<T>&);
        ~Tree();
        class Iterator;

        const Tree<T>::Iterator begin();
        bool add(Tree<T>::Iterator, const T&);
};

//the structure of a tree's element
//each element has a value field and two pointers (to the left and right child)
template <typename T>
struct Tree<T>::Node{
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
class Tree<T>::Iterator{
    private:
        stack<pair<Node*, bool> > nodes;
    public:
        Iterator(){};
        Iterator(Node*);
        Iterator(const Tree<T>::Iterator&);
        bool operator++();
        T& operator*()const;

    friend class Tree<T>;
};

//------------------------------------------------------------

//delete function
//for each node deletes the two children (if has any) and then the node itself
template <typename T>
void Tree<T>::deleteNode(Node* node){
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
typename Tree<T>::Node* Tree<T>::copyNode(Node* node){
    Node *newNode = new Node(node->value);
    if(node->has_left()){
        newNode->left=copyNode(node->left);
    }
    if(node->has_right()){
        newNode->right=copyNode(node->right);
    }
    return newNode;
}

//constructor
template <typename T>
Tree<T>::Tree(const T& _root){
    root = new Node(_root);
}

//copy constructor
template<typename T>
Tree<T>::Tree(const Tree<T>& other){
    root = copyNode(other.root);
}

//assignment operator
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other){
    if(this!=&other){
        deleteNode(root);
        root = copyNode(other.root);
    }
    return *this;
}

//destructor
template<typename T>
Tree<T>::~Tree(){
    deleteNode(root);
}

//returns an iterator to the root
template<typename T>
const typename Tree<T>::Iterator Tree<T>::begin(){
    return Iterator(root);
}

//add function
//adds a new child of a node if it is not full
//full node: has two children
//the new node is in the traversal path after reseting the iterator
template<typename T>
bool Tree<T>::add(Tree<T>::Iterator pos, const T& value){
    Node *onNode = pos.nodes.top().first;
    if(!onNode->has_left()){
        onNode->left = new Node(value);
        return true;
    }
    if(!onNode->has_right()){
        onNode->right = new Node(value);
        return true;
    }
    return false;
}

//---------------------------------------------------------------------

//constructor from node
template<typename T>
Tree<T>::Iterator::Iterator(Node* node){
    if(node->has_right()){
        nodes.push(make_pair(node->right, 0));
    }
    nodes.push(make_pair(node, 1));
    if(node->has_left()){
        nodes.push(make_pair(node->left, 0));
    }
}

//copy constructor
template<typename T>
Tree<T>::Iterator::Iterator(const Tree<T>::Iterator& other){
    nodes = other.nodes;
}

//moving operator
//on each move the most left untraversed node
//returns false if there is no more untraversed nodes in the tree
template<typename T>
bool Tree<T>::Iterator::operator++(){
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
template<typename T>
T& Tree<T>::Iterator::operator*()const{
    return nodes.top().first->value;
}

#endif // TREE_H_
