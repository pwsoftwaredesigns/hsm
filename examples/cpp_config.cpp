//==============================================================================
// INCLUDES
//==============================================================================

#include <stdlib.h>
#include <new>
#include <iostream>

//==============================================================================
// FUNCTIONS
//==============================================================================

void *operator new(size_t size)
{
	std::cout << "\033[1;31mnew(" << size << ")\033[m" << std::endl;
	return malloc(size);
}

void* operator new[](size_t size)
{
	std::cout << "\033[1;31mnew[](" << size << ")\033[m" << std::endl;
	return malloc(size);
}

void operator delete(void *p)
{
	std::cout << "\033[1;31mfree\033[m" << std::endl;
	free(p);
}

void operator delete[](void *p)
{
	std::cout << "\033[1;31mfree\033[m" << std::endl;
	free(p);
}

/**
 * See https://en.cppreference.com/w/cpp/memory/new/operator_delete
 */
#if __cplusplus >= 201400L

void operator delete(void *p, size_t sz)
{
	operator delete(p);
}

void operator delete[](void *p, size_t sz)
{
	operator delete(p);
}

#endif

/**
 * See https://en.cppreference.com/w/cpp/memory/new/operator_delete
 * See https://en.cppreference.com/w/cpp/memory/new/operator_new
 */
#if __cplusplus >= 201700L

void* operator new(std::size_t size, std::align_val_t al) {
	return operator new(size);
}

void* operator new[](std::size_t size, std::align_val_t al) {
	return operator new[](size);
}


void operator delete(void *p, std::align_val_t al) noexcept
{
	operator delete(p);
}

void operator delete[](void *p, std::align_val_t al) noexcept
{
	operator delete(p);
}

void operator delete(void *p, size_t sz, std::align_val_t al) noexcept
{
	operator delete(p);
}

void operator delete[](void *p, size_t sz, std::align_val_t al) noexcept
{
	operator delete(p);
}

#endif
