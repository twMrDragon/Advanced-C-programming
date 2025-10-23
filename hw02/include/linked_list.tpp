#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), len(0) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
    ListNode<T> *current = head;
    while (current)
    {
        ListNode<T> *next = current->GetNext();
        delete current;
        current = next;
    }
    head = nullptr;
    len = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) : head(nullptr), len(0)
{
    ListNode<T> *current = other.head;
    while (current)
    {
        push_back(current->GetData());
        current = current->GetNext();
    }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this == &other)
        return *this;

    this->~LinkedList();

    head = nullptr;
    len = 0;
    ListNode<T> *current = other.getFirstPtr();
    while (current)
    {
        push_back(current->GetData());
        current = current->GetNext();
    }

    return *this;
}

template <typename T>
void LinkedList<T>::push_back(const T &value)
{
    ListNode<T> *newNode = new ListNode<T>(value);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        ListNode<T> *current = head;
        while (current->GetNext())
        {
            current = current->GetNext();
        }
        current->SetNext(newNode);
    }
    len++;
}

template <typename T>
void LinkedList<T>::push_front(const T &value)
{
    ListNode<T> *newNode = new ListNode<T>(value);
    newNode->SetNext(head);
    head = newNode;
    len++;
}

template <typename T>
void LinkedList<T>::Print() const
{
    ListNode<T> *current = head;
    while (current)
    {
        std::cout << current->GetData() << " ";
        current = current->GetNext();
    }
    std::cout << std::endl;
}