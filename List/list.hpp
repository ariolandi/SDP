#ifndef _LIST_H_
#define _LIST_H_

template <typename T>
class List{
    private:
        struct Node;
        Node *front, *back;
        void copy_list(const List<T>&);
        void delete_list();
    public:
        List();
        List(const List<T>&);
        List<T>& operator=(const List<T>&);
        ~List();
        class iterator;

        bool empty()const;
        void push_back(const T);
        void insert_after(iterator, const T);
        void erase(iterator);

        iterator begin()const;
        iterator end()const;
};

template <typename T>
struct List<T>::Node{
    T value;
    Node* next;
    Node(const T& value_): value(value_){
        next = nullptr;
    }
};

template <typename T>
void List<T>::copy_list(const List<T>& other){
    front = nullptr;
    Node *ptr = other.front;
    while(ptr != nullptr){
        push_back(ptr->value);
        ptr = ptr->next;
    }
}

template <typename T>
void List<T>::delete_list(){
    while(front != nullptr){
        Node *ptr = front;
        front = front->next;
        delete ptr;
    }
    front = back = nullptr;
}

template <typename T>
List<T>::List(){
    front = back = nullptr;
}

template <typename T>
List<T>::List(const List<T>& other){
    copy_list(other);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other){
    if(this != &other){
        delete_list();
        copy_list(other);
    }
    return *this;
}

template <typename T>
List<T>::~List(){
    delete_list();
}

template <typename T>
bool List<T>::empty()const{
    return (front == nullptr);
}

template <typename T>
void List<T>::push_back(const T value_){
    Node *node = new Node(value_);
    if(empty())
        front = node;
    else
        back->next = node;
    back = node;
}

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

template <typename T>
typename List<T>::iterator List<T>::begin()const{
    return iterator(front);
}

template <typename T>
typename List<T>::iterator List<T>::end()const{
    if(back != nullptr)
        return iterator(back->next);
    return iterator(nullptr);
}

//---------------------------------
/*class Iterator*/

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



template <typename T>
List<T>::iterator::iterator(){
    ptr = nullptr;
}

template <typename T>
List<T>::iterator::iterator(Node* other){
    ptr = other;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator=(const iterator& other){
    ptr = other.ptr;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator& other)const{
    return ptr != other.ptr;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator& other)const{
    return ptr == other.ptr;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(){
    ptr = ptr->next;
}

template <typename T>
T& List<T>::iterator::operator*(){
    return ptr->value;
}


template <typename T>
typename List<T>::iterator List<T>::iterator::operator+(const unsigned int n){
    Node* p = ptr;
    for(int i=0; i<n && p!=nullptr; i++)
        p = p->next;
    return iterator(p);
}


#endif // _LIST_H_
