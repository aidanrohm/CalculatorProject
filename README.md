Infix to Postfix Calculator

Description
  This C++ program implements a simple calculator that converts mathematical expressions from Infix notation to Postfix notation and evaluates the result. It checks for common syntax errors and handles basic arithmetic operations, including addition, subtraction, multiplication, and division. The program ensures that the input expression adheres to the rules of mathematical notation, including balanced parentheses, valid operators, and no division by zero.

Features
  - Balanced Parentheses Check: Validates that all opening parentheses have corresponding closing parentheses.
  - Operator Error Detection: Ensures that operators are not used without sufficient operands.
  - Division by Zero Prevention: Checks for any instances of division by zero in the expression.
  - Invalid Character Detection: Validates that the expression contains only valid characters (digits, operators, and parentheses).
  - Postfix Conversion: Converts the validated Infix expression to Postfix notation using the Shunting Yard algorithm.
  - Expression Evaluation: Evaluates the resulting Postfix expression and outputs the final result.

Usage
  - Compile the code using a C++ compiler.
  - Run the executable.
  - Enter a mathematical expression in Infix notation when prompted.
  - The program will check for errors, convert the expression to Postfix notation, and display the result.

Example
  Please type the expression in Infix Notation:
  3 + 5 * ( 2 - 8 )
  The Postfix notation:
  3 5 2 8 - * +
  The Result:
  -13

Requirements
  - C++11 or later
  - Standard C++ library (no external libraries required)
  
Error Handling
  - The program will provide error messages for:
    - Unmatched parentheses
    - Operators without operands
    - Division by zero
    - Invalid characters in the expression
  - This ensures that users can correct their input before proceeding with the evaluation.

Notes
  - Ensure that spaces are properly placed in the expression for correct parsing.
  - Only basic arithmetic operations are supported.
  - Decimal numbers are handled, allowing for more flexibility in input.
  - Feel free to modify and expand upon this program to include additional features or handle more complex expressions!
