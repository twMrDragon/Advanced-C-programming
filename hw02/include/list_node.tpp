#include "list_node.hpp"

template <typename T>
ListNode<T>::ListNode() : next(nullptr) {}

template <typename T>
ListNode<T>::ListNode(const T &value) : data(value), next(nullptr) {}

template <typename T>
ListNode<T>::~ListNode() {}