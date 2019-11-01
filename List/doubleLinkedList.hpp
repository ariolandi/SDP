#ifndef _DOUBLE_LIST_H_
#define _DOUBLE_LIST_H_

//Linked list class with iterator
//fields for the first and the last element of the list
//subclass for the iterator
template <typename T>
class DoubleLinkedList{
    private:
        struct Node;
        Node *front, *back;
        void copy_list(const DoubleLinkedList<T>&);
        void delete_list();
    public:
        class iterator;

        DoubleLinkedList();
        DoubleLinkedList(const DoubleLinkedList<T>&);
        DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>&);
        ~DoubleLinkedList();

        bool empty()const;
        void push_back(const T);
        void insert_after(iterator, const T);
        void insert_before(iterator, const T);
        void erase(iterator);

        iterator begin()const;
        iterator end()const;
};

//the structure of a list's element
//each element has a value field and a pointer (to the next element or NULL by default)
template <typename T>
struct DoubleLinkedList<T>::Node{
    T value;
    Node* next, *prev;
    Node(const T& value_): value(value_){
        next = prev = nullptr;
    }
};

//copy function
template <typename T>
void DoubleLinkedList<T>::copy_list(const DoubleLinkedList<T>& other){
    front = nullptr;
    Node *ptr = other.front;
    while(ptr != nullptr){
        push_back(ptr->value);
        ptr = ptr->next;
    }
}

//delete function
template <typename T>
void DoubleLinkedList<T>::delete_list(){
    while(front != nullptr){
        Node *ptr = front;
        front = front->next;
        delete ptr;
    }
    front = back = nullptr;
}

//constructor
//in the beginning every DoubleLinkedList is empty
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(){
    front = back = nullptr;
}

//copy constructor
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other){
    copy_list(other);
}

//assignment operator
template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other){
    if(this != &other){
        delete_list();
        copy_list(other);
    }
    return *this;
}


//destructor
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    delete_list();
}


//a list is empty if the first element pointer is NULL
template <typename T>
bool DoubleLinkedList<T>::empty()const{
    return (front == nullptr);
}

//add function
//adds a new element to the end of the list
template <typename T>
void DoubleLinkedList<T>::push_back(const T value_){
    Node *node = new Node(value_);
    if(empty())
        front = node;
    else{
        back->next = node;
        node->prev = back;
    }
    back = node;
}

//add function
//adds a new element after a certain position in the list
template <typename T>
void DoubleLinkedList<T>::insert_after(iterator position, const T value_){
    if(position == end() || empty()){
        push_back(value_);
        return;
    }
    Node *node = new Node(value_);
    node->next = position.ptr->next;
    position.ptr->next = node;
    (node->next)->prev = node;
    node->prev = position.ptr;
}

//add function
//adds a new element before a certain position in the list
template <typename T>
void DoubleLinkedList<T>::insert_before(iterator position, const T value_){
    if(empty()){
        push_back(value_);
        return;
    }
    Node *node = new Node(value_);
    node->next = position.ptr;
    if(position != begin()){
        (position.ptr->prev)->next = node;
        node->prev = position.ptr->prev;
    }
    position.ptr->prev = node;
}

//erase function
//removes the element of the list on certain position
//Warning: the iterator is being moved to the next element
template<typename T>
void DoubleLinkedList<T>::erase(iterator position){
    if(empty())
        return;
    if(position == end()){
        Node* ptr = back->prev;
        delete back;
        back = ptr;
    }
    else{
        Node* ptr = position.ptr->next;
        ptr->prev = position.ptr->prev;
        (position.ptr->prev)->next = ptr;
        delete position.ptr;
        position.ptr = ptr->next;
    }
}

//returns an iterator to the first element of the list
template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::begin()const{
    return iterator(front);
}

//returns an iterator to the end of the list
//Warning: not the last element
template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::end()const{
    if(back != nullptr)
        return iterator(back->next);
    return iterator(nullptr);
}

//----------------------------------------------------------------------
//class Iterator
//field: pointer to a node of a list
template <typename T>
class DoubleLinkedList<T>::iterator{
    private:
        Node *ptr;
    public:
        iterator();
        iterator(Node*);
        iterator& operator=(const iterator&);
        bool operator!=(const iterator&)const;
        bool operator==(const iterator&)const;
        iterator& operator++();
        iterator& operator--();
        iterator operator+(const unsigned int);
        iterator operator-(const unsigned int);
        T& operator*();

        friend void DoubleLinkedList<T>::insert_after(iterator, const T);
        friend void DoubleLinkedList<T>::insert_before(iterator, const T);
        friend void DoubleLinkedList<T>::erase(iterator);
};

//constructor
template <typename T>
DoubleLinkedList<T>::iterator::iterator(){
    ptr = nullptr;
}

//copy constructor
template <typename T>
DoubleLinkedList<T>::iterator::iterator(Node* other){
    ptr = other;
}

//assignment operator
template <typename T>
typename DoubleLinkedList<T>::iterator& DoubleLinkedList<T>::iterator::operator=(const iterator& other){
    ptr = other.ptr;
}

//operator not-equal
template <typename T>
bool DoubleLinkedList<T>::iterator::operator!=(const iterator& other)const{
    return ptr != other.ptr;
}

//operator equal
template <typename T>
bool DoubleLinkedList<T>::iterator::operator==(const iterator& other)const{
    return ptr == other.ptr;
}

//moving operator
//moves the pointer to the next node
template <typename T>
typename DoubleLinkedList<T>::iterator& DoubleLinkedList<T>::iterator::operator++(){
    ptr = ptr->next;
}

//moving operator
//moves the pointer to the previous node
template <typename T>
typename DoubleLinkedList<T>::iterator& DoubleLinkedList<T>::iterator::operator--(){
    ptr = ptr->prev;
}

//moving operator
//moves the pointer n nodes forward
template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::iterator::operator+(const unsigned int n){
    Node* p = ptr;
    for(int i=0; i<n && p!=nullptr; i++)
        p = p->next;
    return iterator(p);
}

//moving operator
//moves the pointer n nodes backward
template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::iterator::operator-(const unsigned int n){
    Node* p = ptr;
    for(int i=0; i<n && p!=nullptr; i++)
        p = p->prev;
    return iterator(p);
}

//dereferencing operator
//returns the value of the pointed node
template <typename T>
T& DoubleLinkedList<T>::iterator::operator*(){
    return ptr->value;
}




#endif // _DOUBLE_LIST_H_
