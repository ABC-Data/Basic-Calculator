# Basic Calculator in C++

### *Description:*

a simple command-line calculator application in a programming language of your choice (e.g., C++, C#, Java). The application allows users to perform arithmetic operations (addition, subtraction, multiplication, division, exponential and square root) on two or more numbers.  

The application is designed using object-oriented programming principles, encapsulating all functionality within a Calculator class. The class handles expression parsing, validation, evaluation, and history tracking, providing error handling for invalid input, incomplete expressions, division by zero, and unbalanced parentheses.



### *Test command in Linux shell:*

g++ Main.cpp Calculator.cpp -o calc  
./calc  



### *Instructions:*

Type "**exit**" to exit the program.  
Type "**history**" to see the history of all valid calculations done.  



#### *Operators:*

'+' is addition.  
'-' is subtraction.  
'\*' is multiplication.  
'/' is division.  
'^' is power.  
'sqrt()' is square root.  



### *Tests:*

Simple: 2+3 -> = 5  
Parentheses: (2+3)\*4 -> = 20  
Multiple operations: 2+3\*4-5/2 -> = 11.5  
Functions: sqrt(16)+2^3 -> = 12  



#### *Invalid inputs:*

Empty input -> continues.  
Input characters(eg. **3c + 4**) -> error-handling Invalid character.  
Consecutives operations(eg. **3++4**) -> error-handling Operator without left operand.  
Consecutives numbers with space(eg. **3 3**) -> error-handling Two numbers without operator.  
Division by 0(eg. **3/0** or **1/(2-2)**) -> error-handling Division by zero!  
Missing parenthesis(eg. **(3+4** ) -> error-handling Unbalanced parentheses.  
Incomplete function(eg. **sqrt(** ) -> error-handling Unbalanced parentheses.  



#### *Edge cases:*

Negative numbers(eg. **-3**) -> = -3.  
Floating point(eg. **3.2 - 2.33**) -> = 0.87.  
Zero exponent(eg. **0^0**) -> error-handling 0^0 is undefined.  
Consecutive unary operators(eg. **--3**) -> error-handling Invalid token.  

