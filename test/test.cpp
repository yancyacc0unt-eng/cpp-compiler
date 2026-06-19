#include <iostream>

#define SQUARE(x) ((x) * (x))
#define MESSAGE "Compiler test passed\n"

int main() {
    int value = 5;
    int result = SQUARE(value + 1);

    if (result != 36) {
        std::cerr << "Unexpected result: " << result << std::endl;
        return 1;
    }

    std::cout << MESSAGE;
    return 0;
}
