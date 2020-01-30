//
// Created by user on 27.08.2019.
//

#ifndef MYLIST_MY_LIST_H
#define MYLIST_MY_LIST_H

#include <iostream>

template <class Category, class T, class Distance = ptrdiff_t ,
        class Pointer = T*, class Reference = T&>
struct some_iterator {
    typedef T value_type;
    typedef Distance difference_type ;
    typedef Pointer pointer ;
    typedef Reference reference ;
    typedef Category iterator_category ;
};


template <typename T>
class MyList
{

    struct Node
    {
        T item;
        Node* next = nullptr;
        Node* previous = nullptr;
        Node(T item = T(), Node* next = nullptr,  Node* previous = nullptr)
        {
            this->item = item;
            this->next = next;
            this->previous = previous;
        }
    };

    size_t list_size;
    class ListIterator;
    class const_ListIterator;


public:

    Node* head;
    Node* tail;

    //initialization of list
    explicit MyList();

    //initialization with filling list with n number of element
    explicit MyList(size_t count, const T& value = T());

    //initialization with other list
    MyList(const MyList<T>& lst);

    //initialization with iterators
    template<class InputIt, class OutIt>
    MyList(InputIt first, OutIt last);

    //initialization with initializer list
    MyList(std::initializer_list<T> init);

    ~MyList();

    MyList& operator=(const MyList& lst);

    inline T& operator[](size_t index) { return *(begin() + index); };

    //ListIterator of the beginning of list
    inline ListIterator begin()  { return ListIterator(head); }

    //ListIterator of the end of list
    inline ListIterator end() { return ListIterator(tail); }

    //const ListIterator of beginning
    inline const_ListIterator cbegin() const { return const_ListIterator(head); }

    //const ListIterator of end
    inline const_ListIterator cend() const { return const_ListIterator(tail); }

    //add element to the beginning
    void push_front(const T& item);

    //add element to the end of list
    void push_back(const T& item);


    inline bool empty() { return size() == 0; }

    //add element of type T by arguments
    template<class... Args>
    void emplace_back(const Args&... args);

    //add element of type T by arguments
    template<class... Args>
    void emplace_front(const Args&... args);

    //remove the last element
    void pop_front();

    //remove the first element
    void pop_back();

    //return the last element
    inline T& back() { return tail->previous->item; }

    //return the first element
    inline T& front() { return head->item; }

    //swap two lists
    void swap(MyList<T>& lst);

    //insert element to the certain position
    ListIterator insert(ListIterator position, const T& element);


    //insert element to the certain position by its arguments
    template<class... Args>
    ListIterator emplace(ListIterator position, const Args&... args) { T new_class(args...); return insert(position, new_class);}

    //insert the range of elements to certain position
    template< class InputIt >
    void insert(ListIterator position, InputIt first, InputIt last);


    //remove element
    ListIterator erase(ListIterator position);

    //remove range of elements
    ListIterator erase(ListIterator first, ListIterator last);

    //size of list
    inline size_t size() {return list_size;}

    //clear list
    void clear();
};


template <typename T>
bool operator==(const MyList<T>& lst1, const MyList<T>& lst2);

template <typename T>
bool operator!=(const MyList<T>& lst1, const MyList<T>& lst2);

template <typename T>
bool operator<(const MyList<T>& lst1, const MyList<T>& lst2);
template <typename T>
bool operator<=(const MyList<T>& lst1, const MyList<T>& lst2);

template <typename T>
bool operator>(const MyList<T>& lst1, const MyList<T>& lst2);

template <typename T>
bool operator>=(const MyList<T>& lst1, const MyList<T>& lst2);




template <typename T>
MyList<T>::MyList(): list_size(0)
{
    head = tail = new Node;
}

template <typename T>
MyList<T>::MyList(size_t count, const T& value): list_size(0)
{
    head = tail = new Node;
    for(size_t i = 0; i < count; ++i)
    {
        push_back(value);
    }
}

template <typename T>
MyList<T>::MyList(const MyList<T>& lst): list_size(0)
{
    head = tail = new Node;
    for(auto& x: lst)
    {
        push_back(x);
    }
}

template <typename T>
MyList<T>::MyList(std::initializer_list<T> init): list_size(0)
{
    head = tail = new Node;
    for(auto& element: init)
    {

        push_back(element);
    }
}

template<typename T>
template<class InputIt, class OutIt>
MyList<T>::MyList(InputIt first, OutIt last): list_size(0) {

    head = tail = new Node;
    for(auto i = first; i != last; ++i)
    {
        push_back(*i);
    }
}

template <typename T>
MyList<T>::~MyList()
{
    clear();
}



template<typename T>
MyList<T> &MyList<T>::operator=(const MyList &lst)
{
    MyList new_list(lst);
    new_list.swap(*this);
    return *this;

}


template <typename T>
void MyList<T>::push_front(const T& item)
{
    head = new Node(item, head, nullptr);
    head->next->previous = head;
    ++list_size;
}


template <typename T>
void MyList<T>::push_back(const T& item)
{

    if(head == tail)
    {

        head = new Node(item, tail, nullptr);
        tail->previous = head;
    }
    else
    {
        Node* new_node = new Node(item, tail, tail->previous);
        tail->previous = new_node;
        tail->previous->previous->next = new_node;

    }
    ++list_size;
}


template <typename T>
template <class... Args>
void MyList<T>::emplace_back(const Args&... args)
{
    T new_class(args...);
    push_back(new_class);
}

template <typename T>
template <class... Args>
void MyList<T>::emplace_front(const Args&... args)
{
    T new_class(args...);
    push_front(new_class);
}

template <typename T>
void MyList<T>::pop_front()
{
    Node* new_node = head->next;
    delete head;
    head = new_node;
    --list_size;
}

template <typename T>
void MyList<T>::pop_back()
{
    Node* new_node = tail->previous;
    delete tail;
    tail = new_node;
    --list_size;
}




template <typename T>
void MyList<T>::swap(MyList<T>& lst)
{
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(list_size, lst.list_size);

}



template <typename T>
void MyList<T>::clear()
{
    while(head != tail)
    {
        head = head->next;
        delete head->previous;

    }
    head->previous = nullptr;
    list_size = 0;
}



template<typename T>
class MyList<T>::ListIterator: public some_iterator<std::bidirectional_iterator_tag, T>
{


public:

    Node *ptr;

    ListIterator() : ptr(nullptr) {}
    explicit ListIterator(Node* x) : ptr(x) {}
    ListIterator(const ListIterator& mit) : ptr(mit.ptr) {}
    ListIterator& operator++() {
        ptr = ptr->next;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator new_itr(*this);
        operator++();
        return new_itr;
    }

    ListIterator& operator--(){
        ptr = ptr->previous;
        return *this;
    }

    ListIterator operator--(int){
        ListIterator new_itr(*this);
        operator--();
        return new_itr;
    }


    T& operator*()
    {
        return ptr->item;
    }

    ListIterator operator+(int integer)
    {

        ListIterator new_it(ptr);
        for(int i = 0; i < integer; ++i)
        {
            ++new_it;
        }
        return new_it;
    }

    ListIterator operator+=(int integer)
    {
        *this = *this + integer;
        return *this;
    }

    ListIterator operator-(int integer)
    {
        ListIterator new_it(ptr);
        for(int i = 0; i < integer; ++i)
        {
            --new_it;
        }

        return new_it;
    }

    ListIterator operator-=(int integer)
    {
        *this = *this - integer;
        return *this;
    }


    bool operator==(const ListIterator& it)
    {
        return it.ptr == ptr;
    }

    bool operator!=(const ListIterator& it)
    {
        return it.ptr != ptr;
    }

    bool operator<(const ListIterator& it)
    {
        return ptr < it.ptr;
    }
    bool operator>(const ListIterator& it)
    {
        return ptr > it.ptr;
    }


};

template<typename T>
class MyList<T>::const_ListIterator: public some_iterator<std::bidirectional_iterator_tag, T const>
{


public:

    Node *ptr;

    const_ListIterator() : ptr(nullptr) {}
    explicit const_ListIterator(Node* x) : ptr(x) {}
    const_ListIterator(const const_ListIterator& mit) : ptr(mit.ptr) {}
    const_ListIterator(const ListIterator& mit) : ptr(mit.ptr) {}
    const_ListIterator& operator++() {
        ptr = ptr->next;
        return *this;
    }

    const_ListIterator operator++(int) {
        const_ListIterator new_itr(*this);
        operator++();
        return new_itr;
    }

    const_ListIterator& operator--(){
        ptr = ptr->previous;
        return *this;
    }

    const_ListIterator operator--(int){
        const_ListIterator new_itr(*this);
        operator--();
        return new_itr;
    }


    T& operator*()
    {
        return ptr->item;
    }

    const_ListIterator operator+(int integer)
    {

        const_ListIterator new_it(ptr);
        for(int i = 0; i < integer; ++i)
        {
            ++new_it;
        }
        return new_it;
    }

    const_ListIterator operator+=(int integer)
    {
        *this = *this + integer;
        return *this;
    }


    const_ListIterator operator-=(int integer)
    {
        *this = *this - integer;
        return *this;
    }

    int operator-(const_ListIterator it)
    {
        return ptr - it.ptr;
    }

    bool operator==(const const_ListIterator& it)
    {
        return it.ptr == ptr;
    }

    bool operator!=(const const_ListIterator& it)
    {
        return it.ptr != ptr;
    }

    bool operator<(const const_ListIterator& it)
    {
        return ptr < it.ptr;
    }
    bool operator>(const const_ListIterator& it)
    {
        return ptr > it.ptr;
    }


};

template<typename T>
typename MyList<T>::ListIterator MyList<T>::insert(MyList::ListIterator position, const T &element)
{
    if(position == begin())
    {
        push_front(element);
        return begin();
    }
    else if(position == end())
    {
        push_back(element);
        return --end();
    }
    Node* new_node = new Node(element, position.ptr, position.ptr->previous);
    position.ptr->previous->next = new_node;
    position.ptr->previous = new_node;
    ++list_size;
    return ListIterator(new_node);
}

template<typename T>
template<class InputIt>
void MyList<T>::insert(MyList::ListIterator position, InputIt first, InputIt last)
{

    for(auto i = first; i != last; ++i)
    {
        position = insert(position, *i) + 1;
    }

}


template <typename T>
typename MyList<T>::ListIterator MyList<T>::erase(MyList::ListIterator position)
{
    if(position == begin())
    {
        pop_front();
        return begin();
    }

    position.ptr->next->previous = position.ptr->previous;
    position.ptr->previous->next = position.ptr->next;
    Node* new_pos = position.ptr->next;
    delete position.ptr;
    --list_size;
    return ListIterator(new_pos);
}

template <typename T>
typename MyList<T>::ListIterator MyList<T>::erase(MyList::ListIterator first, MyList::ListIterator last)
{
    list_size -= std::distance(first, last);
    Node* new_ptr;
    if(first.ptr == head)
    {
        head = last.ptr;
        head->previous = nullptr;
        new_ptr = head;
    }
    else
    {
        first.ptr->previous->next = last.ptr;
        first.ptr->previous->next->previous = first.ptr->previous->next;
        new_ptr = first.ptr->previous->next;

    }
    for(auto i = first; i != last; ++i)
    {
        delete i.ptr;
    }




    return ListIterator(new_ptr);
}



template <typename T>
bool operator==(const MyList<T>& lst1, const MyList<T>& lst2)
{
    return std::equal(lst1.cbegin(), lst1.cend(), lst2.cbegin(), lst2.cend());
}

template <typename T>
bool operator!=(const MyList<T>& lst1, const MyList<T>& lst2)
{
    return !(lst1 == lst2);
}

template <typename T>
bool operator<(const MyList<T>& lst1, const MyList<T>& lst2)
{
    return std::lexicographical_compare(lst1.cbegin(), lst1.cend(), lst2.cbegin(), lst2.cend());
}

template <typename T>
bool operator<=(const MyList<T>& lst1, const MyList<T>& lst2)
{
    return !(lst1 > lst2);
}

template <typename T>
bool operator>(const MyList<T>& lst1, const MyList<T>& lst2)
{
    return std::lexicographical_compare(lst2.cbegin(), lst2.cend(), lst1.cbegin(), lst1.cend());
}

template <typename T>
bool operator>=(const MyList<T>& lst1, const MyList<T>& lst2)
{
    return !(lst1 < lst2);
}


#endif //MYLIST_MY_LIST_H