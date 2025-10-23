#pragma once

#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class ListNode
{
public:
    ListNode();
    ListNode(const T &value);
    ~ListNode();

    T GetData() const { return data; }
    void SetData(const T& value) { data = value; }

    ListNode<T>* GetNext() const { return next; }
    void SetNext(ListNode<T>* nextNode) { next = nextNode; }


private:
    T data;
    ListNode<T> *next;
};

#include "list_node.tpp"

#endif // LIST_NODE_H