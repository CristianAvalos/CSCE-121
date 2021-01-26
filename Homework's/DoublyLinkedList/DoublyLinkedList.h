#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList(); 
	DoublyLinkedList(T);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
	
    unsigned int size() const { return sz; }
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) : head(nullptr), tail(nullptr), sz(0) {
	Node<T>* node = new Node<T>(data);
	head = node;
	tail = node;
	sz++;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& rhs) : head(nullptr), tail(nullptr), sz(0) {
	Node<T>* curr = rhs.head;
	while (curr != nullptr) {
		this->push_back(curr->data);
		curr = curr->next;
	}
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>:: operator=(const DoublyLinkedList<T>& rhs) {
	if (this != &rhs) {
		clear();
		Node<T>* curr = rhs.head;
		while (curr != nullptr) {
			this->push_back(curr->data);
			curr = curr->next;
		}
	}
    return *this;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	clear();
}

template<typename T>
T& DoublyLinkedList<T>::front() { 
	return head->data;
}

template<typename T>
const T& DoublyLinkedList<T>::front() const { 
	return head->data;
}
template<typename T>
T& DoublyLinkedList<T>::back() {
	return tail->data;
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
	return tail->data;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T data) {
    Node<T>* node = new Node<T>(data);
    if (head == nullptr) {
        head = node;
    }
	if (tail != nullptr) {
        tail->next = node;
		node->prev = tail;
    }
    tail = node;
    sz++;
}

template<typename T>
void DoublyLinkedList<T>::push_front(T data) {
    Node<T>* node = new Node<T>(data);
    if (head == nullptr) {
		tail = node;
	}
	if (head != nullptr) {
		head->prev = node; 
		node->next = head;
	}
	head = node;
    sz++;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
	if (sz == 0) {
		return;
    }
	else if (head == tail) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else{
		Node<T>* node = tail->prev;
		delete tail;
		tail = node;
		tail->next = nullptr;
	}
	sz--;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (sz == 0) {
		return;
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node<T>* next = head->next;
        delete head;
        head = next;
		head->prev = nullptr;
    }
    sz--;
}

template<typename T>
void DoublyLinkedList<T>::erase(unsigned int idx) {
	if (idx > sz-1 || sz == 0) {
		return;
	}
	else if (idx == 0) {
		pop_front();
		return;
	}
	else if (idx == sz - 1) {
		pop_back();
		return;
	}
	unsigned int i = 0;
	Node<T>* curr = head;
	while (curr != nullptr) {
		if (i == idx) {
			curr->next->prev = curr->prev;
			curr->prev->next = curr->next;
			delete curr;
		}
		curr = curr->next;
		i++;
	}
	sz--;
}

template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx) {
	if (idx >= sz) {
		return;
	}
	if (idx == 0) {
		push_front(data);
		return;		
	}
	Node<T>* current = head;
	for (int i = 0; i < idx - 1; ++i) {
		current = current->next;
	}
	Node<T>* node = new Node<T>(data);
	node->next = current->next;
	node->prev = current;
	current->next->prev = node;
	current->next = node;
	sz++;
	return;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
	Node<T>* current = head;
	if (sz == 0) {
		delete current;
		return;
	}
	else {
		Node<T>* node = nullptr;
		while (current) {
			node = current->next;
			delete current;
			current = node;
		}
		sz = 0;
		head = nullptr;
		tail = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
	if (lhs.size() == rhs.size()) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

#endif
