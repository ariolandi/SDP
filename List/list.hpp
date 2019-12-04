#ifndef _LIST_H_
#define _LIST_H_

//Linked list class with iterator
//fields for the first and the last element of the list
//subclass for the iterator
template <typename T>
class List{
    private:
        struct Node;
        Node *front, *back;
        void copy_list(const List<T>&);
        void delete_list();
    public:
        class iterator;

        List();
        List(const List<T>&);
        List<T>& operator=(const List<T>&);
        ~List();

        bool empty()const;
        void push_back(const T);
        void insert_after(List<T>::iterator, const T);
        void erase(iterator);

        iterator begin()const;
        iterator end()const;
};

//the structure of a list's element
//each element has a value field and a pointer (to the next element or NULL by default)
template <typename T>
struct List<T>::Node{
    T value;
    Node* next;
    Node(const T& value_): value(value_){
        next = nullptr;
    }
};

//copy function
template <typename T>
void List<T>::copy_list(const List<T>& other){
    front = nullptr;
    Node *ptr = other.front;
    while(ptr != nullptr){
        push_back(ptr->value);
        ptr = ptr->next;
    }
}

//delete function
template <typename T>
void List<T>::delete_list(){
    while(front != nullptr){
        Node *ptr = front;
        front = front->next;
        delete ptr;
    }
    front = back = nullptr;
}

//constructor
//in the beginning every list is empty
template <typename T>
List<T>::List(){
    front = back = nullptr;
}

//copy constructor
template <typename T>
List<T>::List(const List<T>& other){
    copy_list(other);
}

//assignment operator
template <typename T>
List<T>& List<T>::operator=(const List<T>& other){
    if(this != &other){
        delete_list();
        copy_list(other);
    }
    return *this;
}


//destructor
template <typename T>
List<T>::~List(){
    delete_list();
}


//a list is empty if the first element pointer is NULL
template <typename T>
bool List<T>::empty()const{
    return (front == nullptr);
}

//add function
//adds a new element to the end of the list
template <typename T>
void List<T>::push_back(const T value_){
    Node *node = new Node(value_);
    if(empty())
        front = node;
    else
        back->next = node;
    back = node;
}

//add function
//adds a new element after a certain position in the list
template <typename T>
void List<T>::insert_after(iterator position, const T value_){
    if(position == end() || empty()){
        push_back(value_);
        return;
    }
    Node *node = new Node(value_);
    node->next = position.ptr->next;
    position.ptr->next = node;
}

//erase function
//removes the element of the list on certain position
//Warning: the iterator is being moved to the next element
template<typename T>
void List<T>::erase(iterator position){
    if(empty())
        return;
    if(position == end()){
        Node* ptr = front;
        while(ptr->next != back){
            ptr = ptr->next;
        }
        delete back;
        back = ptr;
    }
    else{
        Node* ptr = front;
        while(ptr->next != position.ptr){
            ptr = ptr->next;
        }
        ptr->next = position.ptr->next;
        delete position.ptr;
        position.ptr = ptr->next;
    }
}

//returns an iterator to the first element of the list
template <typename T>
typename List<T>::iterator List<T>::begin()const{
    return iterator(front);
}

//returns an iterator to the end of the list
//Warning: not the last element
template <typename T>
typename List<T>::iterator List<T>::end()const{
    if(back != nullptr)
        return iterator(back->next);
    return iterator(nullptr);
}

//----------------------------------------------------------------------
//class Iterator
//field: pointer to a node of a list
template <typename T>
class List<T>::iterator{
    private:
        Node *ptr;
    public:
        iterator();
        iterator(Node*);
        iterator& operator=(const iterator&);
        bool operator!=(const iterator&)const;
        bool operator==(const iterator&)const;
        iterator& operator++();
        iterator operator+(const unsigned int);
        T& operator*();

        friend void List<T>::insert_after(iterator, const T);
        friend void List<T>::erase(iterator);
};

//constructor
template <typename T>
List<T>::iterator::iterator(){
    ptr = nullptr;
}

//copy constructor
template <typename T>
List<T>::iterator::iterator(Node* other){
    ptr = other;
}

//assignment operator
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator=(const iterator& other){
    ptr = other.ptr;
}

//operator not-equal
template <typename T>
bool List<T>::iterator::operator!=(const iterator& other)const{
    return ptr != other.ptr;
}

//operator equal
template <typename T>
bool List<T>::iterator::operator==(const iterator& other)const{
    return ptr == other.ptr;
}

//moving operator
//moves the pointer to the next node
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(){
    ptr = ptr->next;
}
//moving operator
//moves the pointer n nodes forward
template <typename T>
typename List<T>::iterator List<T>::iterator::operator+(const unsigned int n){
    Node* p = ptr;
    for(int i=0; i<n && p!=nullptr; i++)
        p = p->next;
    return iterator(p);
}

//dereferencing operator
//returns the value of the pointed node
template <typename T>
T& List<T>::iterator::operator*(){
    return ptr->value;
}




#endif // _LIST_H_
