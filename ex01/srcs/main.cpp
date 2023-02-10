#include <cstdint>
#include <Data.hpp>
#include <iostream>

using std::cout;
using std::endl;

uintptr_t serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data *>(raw);
}


int main(void)
{
    Data testA = {1, 2};
    Data testB = {-1, -1};
    Data *ptestA;
    Data *ptestB;

    uintptr_t resultA;
    uintptr_t resultB;

    resultA = serialize(&testA);
    resultB = serialize(&testB);

    ptestA = deserialize(resultA);
    ptestB = deserialize(resultB);
    if (ptestA == &testA)
        cout << "Success *testA:" << &testA << ", resulatA:" << resultA << ", ptestA:" << ptestA << endl;
    else
        cout << "Failure testA" << endl;
    if (ptestB == &testB)
        cout << "Success *testB:" << &testB << ", resulatB:" << resultB << ", ptestB:" << ptestB << endl;
    else
        cout << "Failure testB" << endl;


    return (0);
}
