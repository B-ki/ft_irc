#include "NewClass.h"

NewClass::NewClass()
{
}

NewClass::~NewClass()
{
}

NewClass::NewClass(const NewClass& other)
{
	*this = other;
}

NewClass & NewClass::operator=(const NewClass& other)
{
	if (this != &other)
		// ...

	return *this;
}
