#ifndef _TREE_H_
#define _TREE_H_

template<typename T>
class OrderTree{
    private:
        T *root;
        OrderTree<T> *left, *right, *parent;
        OrderTree<T>* findLeft()const;
        void insertNode(OrderTree<T>* node);
    public:
        OrderTree();
        ~OrderTree();

        void insertNode(const T& data);
        bool deleteNode(T& data);
        OrderTree<T>* find(T& data);
        void remove(OrderTree<T>* node);

        void print()const;

};

template<typename T>
OrderTree<T>* OrderTree<T>::findLeft()const{
    if(left == nullptr){
        return *this;
    }
    else return left->findLeft();
}

template<typename T>
OrderTree<T>::OrderTree(){
    root = nullptr;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<typename T>
OrderTree<T>::~OrderTree(){
    if(left)delete left;
    if(right)delete right;
    if(root)delete root;
}

template<typename T>
void OrderTree<T>::insertNode(OrderTree<T>* node){
    if(root > node->root){
        if(left == nullptr){
            left = node;
            left->parent = this;
        }
        else left->insertNode(node);
    }
    else{
        if(right == nullptr){
            right = node;
            right->parent = this;
        }
        else right->insertNode(node);
    }
}

template<typename T>
void OrderTree<T>::insertNode(const T& data){
    T *newElement = new T(data);
    if(root == nullptr){
        root = newElement;
    }
    else{
        if(*root > *newElement){
            if(left == nullptr){
                left = new OrderTree;
                left->root = newElement;
                left->parent = this;
            }
            else left->insertNode(data);
        }
        else{
            if(right == nullptr){
                right = new OrderTree;
                right->root = newElement;
                right->parent = this;
            }
            else right->insertNode(data);
        }
    }
}

template<typename T>
OrderTree<T>* OrderTree<T>::find(T& data){
    if(root == nullptr)return nullptr;
    if(*root == data){
        data = *root;
        return this;
    }
    else if(*root > data){
        if(left == nullptr)return nullptr;
        return left->find(data);
    }
    else{
        if(right == nullptr)return nullptr;
        return right->find(data);
    }
}

template<typename T>
bool OrderTree<T>::deleteNode(T& data){
    OrderTree<T>* pos = find(data);
    if(pos == nullptr)return false;
    else{
        remove(pos);
        return true;
    }
}

template<typename T>
void OrderTree<T>::remove(OrderTree<T>* node){
    if(node->left != nullptr){
        (node->parent)->left = node->left;
        node->left->parent = node->parent;
        if(node->right != nullptr)
            node->left->insertNode(node->right);
    }
    else if(node->right != nullptr){
        (node->parent)->right = node->right;
        node->right->parent = node->parent;
    }
    else{
        if(node->parent->left == node)node->parent->left = nullptr;
        else node->parent->right = nullptr;
    }
}


template<typename T>
void OrderTree<T>::print()const{
    if(left != nullptr)left->print();
    std::cout<<*root<<" ";
    if(right != nullptr)right->print();
}

#endif // _TREE_H_
