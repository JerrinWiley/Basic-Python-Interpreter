Piethon
============
A basic python-like interpreter in C++ using flex and bison.

### Requirements
A C++ compiler, Flex, and Bison.

### Build Instructions
To build the project, run make.

### Running the Interpreter
To run the interpreter accepting input from STDIN, run ./piethon
To use a source file, run ./piethon filename

Sample programs can be found in the 'test' directory.


### Features
This program aims to be an experiment with Flex, Bison, and Abstract Syntax
Trees, rather than any sort of Python replacement. However, the following
(small) functionality exists.

* Integer and floating point expressions
* If/Else blocks
* Variables (with both global and function scope)
* Functions (including nested functions and recursion)
* While loops
* Arithmetic Operators (+, -, *, /, %, ^)
* Assignment operators (+=, -=, *=, /=, ^=, %=)
* Increment/Decrement operator (++/--, cannot currently be used in expressions)
* Comments (beginning with a '#')
* Condiional statements (<, >, <=, >=, ==, !=)
* Line-number reporting for both syntactic and semantic errors
* Different return codes for semantic/syntactic errors. The interpreter will return the following values:
   - 0: successful parse and run
   - 1: syntax error
   - 2: semantic error
   - 3: other error (ex: source file not found)

* Function calls as statements. Simply "f()" is a valid program statement. If main() is defined, it will automatically be invoked.
* Smart exception handling and error messages for runtime   errors, such as:
   - unbound identifier
   - undefined function
   - function signature mismatch
   - div/mod by zero
   - return statement outside of function body

