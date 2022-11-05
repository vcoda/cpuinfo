#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>

static std::streamsize width = 0;

void setFieldWidth(std::streamsize fieldWidth)
{
    width = fieldWidth;
}

template<class Type>
void printLn(const char *description, const Type& value)
{
    std::cout << std::setw(width) << std::left << description << value << std::endl;
}

void printString(const char *description)
{
    std::cout << description << std::endl;
}

void printHeading(const char *description)
{
    const std::size_t length = strlen(description);
    std::size_t dashedLength = (80 - length)/2;
    std::cout << std::endl;
    for (std::size_t i = 0; i < dashedLength - 1; ++i)
        std::cout << "=";
    std::cout << " " << description << " ";
    if (length % 2)
        ++dashedLength;
    for (std::size_t i = 1; i < dashedLength; ++i)
        std::cout << "=";
    std::cout << std::endl << std::endl;
}
