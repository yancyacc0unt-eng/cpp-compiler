#ifndef COMPILER_H
#define COMPILER_H

#include <fstream>
#include <iostream>
#include <string>
//lex
enum class TokenType {
    TK_PRE,
    TK_KEYWORD,
    TK_OP,
    TK_ATTR,
    TK_IDENT,
    TK_CHAR,
    TK_STR,
    TK_INT,
    TK_FLOAT,
    TK_SEMI,
    TK_LBRACE,
    TK_RBRACE,
    TK_EOF,
};
struct Token {
    Token *prev;
    TokenType type;
    std::string name;
    Token *next;
    union {
        char ch;
        char *str;
        long integer;
        double floating;
        char *args[2];
    } as;
};
class Lexer {
private:
    Token *head;
    Token *tail;
    std::ifstream file;
    long pos;
    Token *newToken(const Token t);
    void addToken(const Token *t);
public:
    Lexer(const char *filename):file(filename), pos(0), head(nullptr), tail(nullptr) {}
    Token *tokenize();
    ~Lexer() = default;
};

#endif//COMPILER_H