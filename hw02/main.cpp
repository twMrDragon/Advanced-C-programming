#include <unistd.h>
#include <iostream>
#include <cassert>
#include <vector>
#include "linked_list.hpp"
#include "memory_usage.hpp"

void question0();
void question1_2();
void question3();
void question4();
void question5();
void print_pages()
{
    static size_t pagesize = sysconf(_SC_PAGESIZE);
    int64_t bytes = getCurrentRSS();
    assert((bytes % pagesize) == 0);
    std::cout << "Memory usage: " << (double)bytes / (1024 * 1024) << " [MB]" << std::endl;
}

int main()
{
    question0();
    question1_2();
    question3();
    question4();
    question5();
    return 0;
}

void question0()
{
    LinkedList<size_t> lsA, lsB;
    lsA.push_back(1);
    lsA.push_back(4);
    lsA.push_back(3);
    lsB.push_front(1);
    lsB.push_front(4);
    lsB.push_front(3);

    std::cout << "lsA: ";
    lsA.Print();
    std::cout << "lsB: ";
    lsB.Print();
    std::cout << std::endl;
}

void question1_2()
{
    // question 1
    LinkedList<size_t> ls1;
    ls1.push_back(1);
    ls1.push_back(4);
    ls1.push_back(3);
    ls1.push_back(1);

    // question 2
    LinkedList<size_t> ls2 = ls1;
    ls1.push_back(5);

    std::cout << "ls1: ";
    ls1.Print();
    std::cout << "ls2: ";
    ls2.Print();
    std::cout << "ls1.getFirstPtr() = " << ls1.getFirstPtr() << std::endl;
    std::cout << "ls2.getFirstPtr() = " << ls2.getFirstPtr() << std::endl;
    std::cout << std::endl;
}

void question3()
{
    std::vector<LinkedList<size_t>> v;
    std::cout << "Before resize:  ";
    print_pages();
    size_t num1 = 65536 * 16;
    v.resize(num1);
    for (size_t i = 0; i < num1; ++i)
    {
        v[i].push_back(i);
    }
    std::cout << "After resize:  ";
    print_pages();
    v.clear();
    v.shrink_to_fit();
    std::cout << "After clear:  ";
    print_pages();
    std::cout << std::endl;
}

void question4()
{
    LinkedList<size_t> ls3;
    {
        LinkedList<size_t> ls4;
        ls4.push_back(6);
        ls4.push_back(7);
        ls4.push_back(1);
        ls4.push_back(2);
        ls3 = ls4;
        std::cout << "ls4: ";
        ls4.Print();
        std::cout << "ls3: ";
        ls3.Print();
        std::cout << "ls3.getFirstPtr() = " << ls3.getFirstPtr() << std::endl;
        std::cout << "ls4.getFirstPtr() = " << ls4.getFirstPtr() << std::endl;
    }

    std::cout << "ls3: ";
    ls3.Print();
    std::cout << std::endl;
}

void question5()
{
    size_t num2 = 65536 * 2;
    std::cout << "Initialize:  ";
    print_pages();
    for (size_t i = 0; i < 10; ++i)
    {
        LinkedList<size_t> ls4;
        for (size_t j = 0; j < num2; ++j)
        {
            ls4.push_back(j);
        }
        std::cout << "Memory in loop:  ";
        print_pages();
    }
    std::cout << "Finish:  ";
    print_pages();
}