#include <boost/filesystem/operations.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "The size of " << boost::filesystem::absolute(argv[0])
              << " is " << boost::filesystem::file_size(argv[0]) << '\n';

    std::cout << "Hello world ;)" << std::endl;
    std::cout << "It works, finally..." << std::endl;
    return 0;
}