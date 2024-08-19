This repository documents the work on the final coursework for the Instruction Architecture and Compilers 2024 module, collaboratively completed with [Noam Weitzman](https://github.com/noamweitz).


## Project Overview

In this project, we implemented a C90 to RISC-V compiler using C++. The compiler supports the following features:
* Binary and Unary operations
* Integers
* Floats and Doubles
* Function calls
* Arrays
* Pointers
* Chars
* Strings
* Globals
* Control flow
* Switch statement


## Repository Structure

```
├───compiler_tests
│   ├───array
│   ├───control_flow
│   ├───...
├───include
│   ├───arrays
│   ├───context
│   ├───...
├───scripts
└───src
    ├───arrays
    ├───context
    ├───...
```

* <b> include/: </b> Contains user-defined header files, such as ast.hpp.
* <b> scripts/: </b> Contains scripts for running the compiler and tests.
* <b> src/: </b> Contains the source code, including lexer, parser, compiler, and command line programs.

To build and test the compiler, run:

``` bash
python3 test.py ../compiler_tests
```

## Future Work

Over the summer, the codebase will be augmented to include:
* Enums
* Typedef
* Structs


## Technologies Used

The project makes use of:
* LEX for token recognition
* YACC for AST building
* Object-Oriented Programming, inheritance and polymorphism for Node handling


Acknowledgements
================

* The coursework was originally designed by [David Thomas](https://www.southampton.ac.uk/people/5z9bmb/professor-david-thomas), who lectured this module until 2017-18. It is nowadays maintained by [John Wickerson](https://johnwickerson.github.io/), to whom any feedback should be sent.
* Thanks to [Yann Herklotz](https://yannherklotz.com/) for making various improvements to the compiler-testing scripts.
* Thanks to [Archie Crichton](https://www.doc.ic.ac.uk/~ac11018/) for providing a basic "getting started" compiler.
* Thanks to [James Nock](https://www.linkedin.com/in/jpnock) for overhauling the scripts for configuring the development environment, for writing detailed instructions for setting this up on various operating systems, and for creating GitHub actions capable of automatically testing compilers.
* Thanks to [Quentin Corradi](https://www.imperial.ac.uk/people/q.corradi22) for setting up coverage testing and writing a getting-started guide for that.
* Thanks to [Filip Wojcicki](https://www.linkedin.com/in/filip-wojcicki) for overhauling the coursework specification and providing a new getting-started guide.
* Thanks to [Noam Weitzman](https://github.com/noamweitz) for putting up with me! ;)
