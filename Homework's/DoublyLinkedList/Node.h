#ifndef NODE_H
#define NODE_H

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
struct Node {
    T data;
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    Node* next;
    Node* prev;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> bool operator==(const Node<T>& rhs, const Node<T>& lhs);
template<typename T> bool operator!=(const Node<T>& rhs, const Node<T>& lhs);
template<typename T> bool operator<(const Node<T>& rhs, const Node<T>& lhs);
template<typename T> bool operator<=(const Node<T>& rhs, const Node<T>& lhs);
template<typename T> bool operator>(const Node<T>& rhs, const Node<T>& lhs);
template<typename T> bool operator>=(const Node<T>& rhs, const Node<T>& lhs);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////

#endif