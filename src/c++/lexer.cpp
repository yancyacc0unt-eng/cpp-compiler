#include "compiler.h"

const char *precs[] = {
    "#define", "undef",
    "#include", "#line", "#error", "#pragma",
    "#if", "#ifdef", "#ifndef", "#else", "#elif", "#endif"
};
const char *kywds[] = {
    "alignas", "alignof", "and", "and_eq", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto",
    "bitand", "bitor", "bool", "break",
    "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
    "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return", "co_yield",
    "decltype", "default", "delete", "do", "double", "dynamic_cast",
    "else", "enum", "explicit", "export", "extern",
    "false", "float", "for", "friend",
    "goto", "if", "inline", "int", "long", "mutable",
    "namespace", "new", "noexcept" "not", "not_eq", "nullptr",
    "operator", "or", "or_eq",
    "private", "protected", "public",
    "reflexpr", "register", "reinterpret_cast", "requires", "return",
    "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized",
    "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename",
    "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
};
const char *opers[] = {
    "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
    "++", "--", "+", "-", "*", "/", "%", "&", "|", "~", "^", "<<", ">>",
    "&&", "||", "!", "==", "!=", "<=", ">=", "<", ">", "<=>", "?", ":",
    "[", "]",/*/"*","&",/**/".", "->", ".*", "->*", "(", ")", ",", "..."
};
const char *attrs[] = {
    "[[noreturn]]", "[[fallthrough]]", "[[likely]]", "[[unlikely]]",
    "[[msvc::dllimport]]", "[[msvc::dllexport]]",
    "[[gnu::always_inline]]", "[[gnu::const]]"
};

char Lexer::peek(unsigned long ofst = 1) {
    this->file.seekg(this->pos+ofst);
    char result = this->file.get();
    this->file.seekg(this->pos);
    return result;
}
char Lexer::step(unsigned long ofst = 1) {
    this->file.seekg(this->pos+ofst);
    char result = this->file.get();
    this->pos += ofst;
    return result;
}
void Lexer::skip() {
    if(this->peek() == '\\' && this->peek(2) == '\\') {
        while(this->step() != '\n');
    }
    if(this->peek() == '\\' && this->peek(2) == '*'){
        while(this->step() != '*' || this->peek() != '\\');
        pos++;
    }
    if(this->peek() == ' ' || this->peek() == '\n'){
        while(this->peek() != ' ' || this->peek() != '\n'){
            this->pos++;
        }
    }
}
void Lexer::genattr(Token *tmp){
}
void Lexer::genprec(Token *tmp){
}
void Lexer::genkwds(Token *tmp){
}
void Lexer::genopos(Token *tmp){
}
Token *Lexer::scan(){
    auto temp = this->newToken({
        nullptr,
        TokenType::TK_ERROR,
        "",
        nullptr,
        NULL
    });
    switch(this->peek()){
    case '#':
        genprec(temp);
        break;
    case ';':
        temp->type = TokenType::TK_SEMI;
        temp->name = ";";
        break;
    case '{':
        temp->type = TokenType::TK_LBRACE;
        temp->name = "{";
        break;
    case '}':
        temp->type = TokenType::TK_RBRACE;
        temp->name = "}";
        break;
    [[fallthrough]]case '[':
        if(this->peek(2) == '['){
            genattr(temp);
        } else {
            temp->type = TokenType::TK_OP;
            temp->name = "[";
        }
    default:
        break;
    }
    return temp;
}
Token *Lexer::tokenize() {
    while(true){
        if(this->peek() == EOF){
            return this->head;
        }
        this->skip();
        this->addToken(this->scan());
        if(this->tail->type == TokenType::TK_ERROR){
            std::cout
            << "ERROR at position : " << this->pos << '\n'
            << "name : " << this->tail->name << std::endl;
        }
    }
    return nullptr;
}
Token *Lexer::newToken(const Token t = {0}) {
    return new Token{t};
}
void Lexer::addToken(Token *t) {
    if(this->head == nullptr){
        this->head = this->tail = t;
    } else {
        this->tail->next = t;
        t->prev = this->tail;
        this->tail = this->tail->next;
    }
}
