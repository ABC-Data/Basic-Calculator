# Basic Calculator in C++

### *Description:*

The Basic Calculator is designed using Object-Oriented Programming (OOP) principles allowing users to input arithmetic expressions with multiple operators (+, -, \*, /, ^, sqrt) and parentheses, and it outputs the correct result while maintaining a history of previous calculations.  



#### *The application is designed using object-oriented programming(OOP) principles:*  

**Encapsulation** is achieved by organizing related data and behaviour into separate classes, restricting direct access to internal data. For example, the Calculator class handles the workflow by combining parsing, evaluation, and history management. Internally, it holds instances of Tokenizer, Evaluator, and History privately. Users interact only through the calculate() method, which hides internal complexity. History stores previous calculations in a private records vector and exposes controlled methods add(), print(), and clear(). Evaluator \& Tokenizer keeps internal computation and tokenization details private, users do not access stacks or parsing logic directly.  



**Inheritance** is demonstrated in the Operation hierarchy, the base abstract class Operation defines the interface apply(double lhs, double rhs) and symbol(). Derived classes implement specific operations like AddOperation, SubtractOperation, MultiplyOperation, DivideOperation, PowerOperation, and SqrtOperation.  



**Polymorphism** is applied through virtual functions in the Operation class, where Evaluator stores a collection of operations using std::unique\_ptr<Operation>. When evaluating an expression, Evaluator calls apply() on an Operation pointer. The actual derived class implementation executes depending on the operation type (AddOperation, SqrtOperation, etc.).  



**Abstraction** is shown by hiding complex implementation details behind the History, Tokenizer \& Evaluator class. Where the Calculator class only exposes simple functions that integrates all components, not showing the stack-based evaluation or operator precedence logic.  



### *Test command in Linux shell:*

g++ Main.cpp Calculator.cpp History.cpp Tokenizer.cpp Evaluator.cpp -o calc  
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
Consecutives operations(eg. **3++4**) -> error-handling Operator in invalid position.  
Consecutives numbers with space(eg. **3 3**) -> error-handling Two numbers without operator.  
Division by 0(eg. **3/0** or **1/(2-2)**) -> error-handling Division by zero!  
Missing parenthesis(eg. **(3+4** ) -> error-handling Unbalanced parentheses.  
Incomplete function(eg. **sqrt(** ) -> error-handling Unbalanced parentheses.



#### *Edge cases:*

Negative numbers(eg. **-3**) -> = -3.  
Floating point(eg. **3.2 - 2.33**) -> = 0.87.  
Zero exponent(eg. **0^0**) -> error-handling 0^0 is undefined.  
Consecutive unary operators(eg. **--3**) -> error-handling Invalid token.

