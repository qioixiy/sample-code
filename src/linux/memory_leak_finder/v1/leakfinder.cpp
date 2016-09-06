#include<iostream>

extern "C" void* malloc(size_t size)
{
    std::cout << "malloc called" << std::endl;
    // Somehow track this allocation
}

extern "C" void free(void* ptr)
{
    std::cout << "free called" << std::endl;
    // Somehow marry up this deallocation to a previous allocation
}
