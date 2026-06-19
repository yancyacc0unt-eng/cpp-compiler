@echo off
echo "================================"
echo "Building..."
g++ src\main.cpp src\lexer.cpp -o bin\compile++.exe
echo "Build completed."
echo "================================"
echo "Testing..."
bin\compile++.exe -h
echo "Test completed."
echo "================================"
pause