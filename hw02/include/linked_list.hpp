#pragma once

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list_node.hpp"
#include <iostream>

template <typename T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList<T> &other);
    ~LinkedList();

    LinkedList<T>& operator=(const LinkedList<T> &other);

    void push_back(const T &value);
    void push_front(const T &value);
    void Print() const;
    ListNode<T>* getFirstPtr() const { return head; }

private:
    ListNode<T> *head;
    size_t len;
};

#include "linked_list.tpp"

#endif // LINKED_LIST_H