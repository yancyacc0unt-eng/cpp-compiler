#include "compiler.h"
bool isalpha(char c){
    return (c>='a'&&c<='z')
    ||(c>='A'&&c<='Z')||(c=='_');
}
