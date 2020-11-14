# Basic-Python-Interpreter
A simple interpreter based on the work by Jonathan Beard using Bison and Flexx


A Python interpreter written in C++ that can evaluate simple variable assignments with integer arithmetic expressions. The input Python program will have variable assigment, function definitions, if/else control statement,
function calls, following Python syntax and evaluation semantics.

Call syntax at the OS prompt:
g++ -std=c++11 *.cpp -o mypython
./mypython <file.py>
