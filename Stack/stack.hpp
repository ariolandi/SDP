#ifndef STACK_H_
#define STACK_H_

//Stack class with linked representation
//has only one field - a pointer to the top of the stack
template<typename T>
class Stack{
    private:
        struct Node;
        Node *start;
        void copyStack(const Node*);
        void deleteStack();
    public:
        Stack();
        Stack(const Stack<T>&);
        Stack<T>& operator=(const Stack<T>&);
        ~Stack();
        bool empty()const;
        void push(const T&);
        void pop();
        const T& top()const;
};

//the structure of a stack's element
//each element has a value field and a pointer (to the next element or NULL by default)
template<typename T>
struct Stack<T>::Node{
    T value;
    Node *next;
    Node(const T& value_){
        value = value_;
        next = nullptr;
    }
};

//recursive copy function
//goes to the bottom of the stack and recursively adds elements
template<typename T>
void Stack<T>::copyStack(const Node *node){
    if(node == nullptr)return;
    else{
        copyStack(node->next);
        push(node->value);
    }
}

//delete function
template<typename T>
void Stack<T>::deleteStack(){
    while(!empty()){
        Node *ptr = start;
        start = start->next;
        delete ptr;
    }
}

//constructor
//in the beginning every stack is empty
template<typename T>
Stack<T>::Stack(){
    start = nullptr;
}

//copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T>& other){
    start = nullptr;
    copyStack(other.start);
}

//assignment operator
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other){
    if(this != &other){
        deleteStack();
        copyStack(other.start);
    }
    return *this;
}

//destructor
template<typename T>
Stack<T>::~Stack(){
    deleteStack();
}

//a stack is empty if the start pointer is NULL
template<typename T>
bool Stack<T>::empty()const{
    return start == nullptr;
}

//add function
//adds an element to the top of the stack
template<typename T>
void Stack<T>::push(const T& value){
    Node *newElement = new Node(value);
    newElement->next = start;
    start = newElement;
}


//remove function
//removes the top element of the stack if the stack is not empty
template<typename T>
void  Stack<T>::pop(){
    if(!empty()){
        Node *ptr = start;
        start = start->next;
        delete ptr;
    }
}

//peek function
//returns the value of the top element
template<typename T>
const T& Stack<T>::top()const{
    if(!empty()){
        return start->value;
    }
}

#endif // STACK_H_
