#ifndef QUEUE_H_
#define QUEUE_H_

//Queue class with linked representation
//has two fields:
//pointers to the first (front/top) and last (rear) element
template<typename T>
class Queue{
    private:
        struct Node;
        Node *frontElement, *rearElement;
        void copyQueue(const Queue<T>&);
        void deleteQueue();
    public:
        Queue();
        Queue(const Queue<T>&);
        Queue<T>& operator=(const Queue<T>&);
        ~Queue();
        bool empty()const;
        void push(const T&);
        void pop();
        const T& front()const;
};

//the structure of a queue's element
//each element has a value field and a pointer (to the next element or NULL by default)
template<typename T>
struct Queue<T>::Node{
    T value;
    Node *next;
    Node(const T& value_){
        value = value_;
        next = nullptr;
    }
};

//copy function
template<typename T>
void Queue<T>::copyQueue(const Queue<T>& other){
    Node *q = other.frontElement;
    while(q != nullptr){
        push(q->value);
        q = q->next;
    }
}

//delete function
template<typename T>
void Queue<T>::deleteQueue(){
    while(!empty())
        pop();
}

//constructor
//in the beginning every queue is empty
template<typename T>
Queue<T>::Queue(){
    frontElement = rearElement = nullptr;
}

//copy constructor
template<typename T>
Queue<T>::Queue(const Queue<T>& other){
    frontElement = rearElement = nullptr;
    copyQueue(other);
}

//assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){
    if(this != &other){
        deleteQueue();
        copyQueue(other);
    }
    return *this;
}

//destructor
template<typename T>
Queue<T>::~Queue(){
    deleteQueue();
}


//a queue is empty if the front pointer is NULL
template<typename T>
bool Queue<T>::empty() const{
    return (frontElement == nullptr);
}

//add function
//adds an element to the rear of the queue
template<typename T>
void Queue<T>::push(const T& value){
    Node *node = new Node(value);
    if(empty())frontElement = node;
    else rearElement->next = node;
    rearElement = node;
}

//remove function
//removes the frint element of the queue if the queue is not empty
template<typename T>
void Queue<T>::pop(){
    if(!empty()){
        Node *node = frontElement;
        frontElement = frontElement->next;
        delete node;
    }
}

//peek function
//returns the value of the front element
template<typename T>
const T& Queue<T>::front() const{
    if(!empty())
        return frontElement->value;
}


#endif // QUEUE_H_
