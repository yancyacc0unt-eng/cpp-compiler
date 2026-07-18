#include "compiler.h"

int main(int argc, char* argv[]) {
    Lexer tokenizer(std::string("../src/c++/main.cpp"));
    tokenizer.tokenize();
    return 0;
}
