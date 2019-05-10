#ifndef NODES_H_
#define NODES_H_

template<typename T>
struct Node{
    T value;
    Node<T> *next;
    Node(T _value){
        value = _value;
        next = nullptr;
    }
};

#endif //NODES_H_
