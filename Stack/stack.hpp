#ifndef STACK_H_
#define STACK_H_
#include"nodes.hpp"

template<typename T>
class Stack{
    private:
        Node<T> *start;
        void CopyStack(const Node<T>*);
        void deleteStack();
    public:
        Stack();
        Stack(const Stack<T>&);
        Stack<T>& operator=(const Stack<T>&);
        ~Stack();
        bool empty()const;
        void push(const T&);
        T pop();
        T top()const;
};

template<typename T>
void Stack<T>::CopyStack(const Node<T> *ptr){
        if(ptr != nullptr){
        CopyStack(ptr->next);
        push(ptr->value);
    }
}

template<typename T>
void Stack<T>::deleteStack(){
    while(!empty()){
        Node<T> *ptr = start;
        start = start->next;
        delete ptr;
    }
}

template<typename T>
Stack<T>::Stack(){
    start = nullptr;
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other){
    start = nullptr;
    CopyStack(other.start);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other){
    if(this != &other){
        deleteStack();
        CopyStack(other.start);
    }
    return *this;
}

template<typename T>
Stack<T>::~Stack(){
    deleteStack();
}

template<typename T>
bool Stack<T>::empty()const{
    return (start == nullptr);
}

template<typename T>
void Stack<T>::push(const T& value){
    Node<T> *newElement = new Node<T>(value);
    newElement->next = start;
    start = newElement;
}

template<typename T>
T Stack<T>::pop(){
    if(!empty()){
        Node<T> *ptr = start;
        start = start->next;
        T v = ptr->value;
        delete ptr;
        return v;
    }
}

template<typename T>
T Stack<T>::top()const{
    if(!empty()){
        return start->value;
    }
}

#endif // STACK_H_
