
#include <iostream>
#include <memory>

int main()
{
    {
        std::unique_ptr<int> ptr = std::make_unique<int>();
        std::cout << ptr << std::endl;
    }

    std::cout << ptr << std::endl;

    return EXIT_SUCCESS;
}

