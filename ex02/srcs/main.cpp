#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

Base * generate(void)
{
    static unsigned int random_int = 1;
    random_int++;
    srandom((unsigned int)(time(NULL)) * random_int);
    int rand = (int)((random() / (double)(RAND_MAX + 1u)) * 3) + 1;

    switch (rand)
    {
        case 1:
            cout << "A is generated." << endl;
            return new A();
        case 2:
            cout << "B is generated." << endl;
            return new B();
        case 3:
            cout << "C is generated." << endl;
            return new C();
    }
    return (0);
}

template <typename T>
void printType(T *base)
{
    cout << "Base class:" << &base  << endl;
}

template <>
void printType<A>(A *a)
{
    cout << "*p is A class:" << &a << endl;
}

template <>
void printType<B>(B *b)
{
    cout << "*p is B class" <<  &b << endl;
}

template <>
void printType<C>(C *c)
{
    cout << "*p is C class" << &c << endl;
}

/*
class Derived : public Base {};

template <typename T>
void printType(T &obj) {
    std::cout << "Base class" << &obj <<  std::endl;
}
*/



//template <>
//void printType<Derived>(Derived &obj) {
    //std::cout << "Derived class" << &obj << std::endl;
//}

void identify(Base* p)
{
    A *a = dynamic_cast<A*>(p);
    if (a)
        cout << "*p:(" << &a << ") is A class" << endl;
    B *b = dynamic_cast<B*>(p);
    if (b)
        cout << "*p:(" << &b << ") is B class" << endl;
    C *c = dynamic_cast<C*>(p);
    if (c)
        cout << "*p:(" << &c << ") is C class" << endl;
}

void identify(Base& p)
{
    try
    {
        A& a = dynamic_cast<A&>(p);
        cout << "&p:(" << &a << ") is A class" << endl;
    }
    catch (const std::bad_cast& e){
    }
    try
    {
        B& b = dynamic_cast<B&>(p);
        cout << "&p:(" << &b << ") is B class" << endl;
    }
    catch (const std::bad_cast& e){
    }
    try
    {
        C& c = dynamic_cast<C&>(p);
        cout << "&p:(" << &c << ") is C class" << endl;
    }
    catch (const std::bad_cast& e){
    }
}



int main(void)
{
    for (int i = 0; i < 10; i++)
    {
        Base *base = generate();
        identify(base);
        identify(*base);

        delete base;
    }
}
