#include <iostream>
#include <cstring>

char *removeDuplicates(char *input)
{
    bool seen[256] = {false}; // Use 256 to cover all possible char values
    int len = strlen(input);
    char *result = new char[len + 1];
    int index = 0;

    for (int i = 0; i < len; ++i)
    {
        if (!seen[static_cast<unsigned char>(input[i])])
        {
            result[index++] = input[i];
            seen[static_cast<unsigned char>(input[i])] = true;
        }
    }
    result[index] = '\0';
    return result;
}

int main()
{
    char test[100];
    while (true)
    {
        std::cin >> test;
        char *result = removeDuplicates(test);
        std::cout << result << std::endl;
        delete[] result; // Free the allocated memory
    }
    return 0;
}