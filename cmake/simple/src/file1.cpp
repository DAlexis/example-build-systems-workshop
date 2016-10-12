#include "file1.hpp"

#include <iostream>
#include <thread>
#include <chrono> 

void printHello()
{
    std::thread t([]{
        for (int i=0; i<3; i++)
        {
            std::cout << "Hello, file1!" << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    });
    t.join();
}
