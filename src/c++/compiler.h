#ifndef COMPILER_H
#define COMPILER_H

#include <fstream>
#include <iostream>
#include <string>
//lex
enum class TokenType {
    TK_ERROR,
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
    TK_EOF
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
        char *arg[2];
    } as;
};
class Lexer {
private:
    Token *head;
    Token *tail;
    std::ifstream file;
    unsigned long pos;
    std::string code;
    Token *newToken(const Token t = {0});
    void addToken(Token *t);
    char peek(unsigned long ofst = 1);
    char step(unsigned long ofst = 1);
    void skip();
    void genattr(Token *tmp);
    Token *scan();
public:
    Lexer(const std::string &fileName):file(fileName), pos(0), head(nullptr), tail(nullptr) {}
    Lexer(const char *sourceCode):code(sourceCode), head(nullptr), tail(nullptr) {}
    Token *tokenize();
    ~Lexer() = default;
};

#endif//COMPILER_H