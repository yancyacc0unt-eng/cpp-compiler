@echo off

g++ .\src\c++\main.cpp .\src\c++\lexer.cpp .\src\c++\util.cpp -o .\bin\compile++.exe
gcc .\src\c\main.c -o .\bin\compile.exe
