/* This is a calculator that accepts an input from a user in infix notation
   infix notation is what we consider to be the normal format of a mathematical expression; take 2+2 as an example
   the calculator then changes the infix notation to a postfix notation where it will then use a stack to calculate the result
   calculator also uses stacks to check for syntax errors and any mistake the user may make
*/

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>  // For isdigit
#include <sstream> // For stringstream

using namespace std;

// Function to check if parentheses are balanced
bool hasBalancedParentheses(const string& input) {
    stack<char> parenthesesStack; // Stack to keep track of opening parentheses

    for (char ch : input) {
        if (ch == '(') {
            parenthesesStack.push(ch); // Push opening parenthesis onto the stack
        } else if (ch == ')') {
            if (parenthesesStack.empty()) {
                cout << "Syntax Error: Unmatched closing parenthesis." << endl;
                return false; // Error if there's no matching opening parenthesis
            }
            parenthesesStack.pop(); // Match found, pop the opening parenthesis
        }
    }

    // If stack is not empty, there are unmatched opening parentheses
    if (!parenthesesStack.empty()) {
        cout << "Syntax Error: Unmatched opening parenthesis." << endl;
        return false;
    }

    return true; // Parentheses are balanced
}

// Function to check for operator errors (no operand before operator)
bool hasOperatorErrors(const string& input) {
    stack<char> operandStack; // Stack to keep track of operands

    for (char ch : input) {
        if (isdigit(ch) || ch == '.') {
            operandStack.push(ch); // Push digits and decimal points onto the stack
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (operandStack.empty()) {
                cout << "Syntax Error: Operator without required operands." << endl;
                return false; // Error if an operator is found without an operand
            }
            // Remove the last operand to account for the operator
            while (!operandStack.empty() && (isdigit(operandStack.top()) || operandStack.top() == '.')) {
                operandStack.pop(); // Pop the last operand
            }
        }
    }

    // If there are no operands left for an operator, it's an error
    return !operandStack.empty();
}

// Function to check for division by zero
bool isDividingByZero(const string& input) {
    for (size_t i = 0; i < input.size(); ++i) {
        // Check if there's a division by zero
        if (input[i] == '/' && (i + 1 < input.size() && input[i + 1] == '0')) {
            cout << "Error: Cannot divide by zero." << endl;
            return false;
        }
    }
    return true;
}

// Function to check if the input contains invalid characters
bool hasInvalidCharacters(const string& input) {
    for (char ch : input) {
        if (!isdigit(ch) && ch != '.' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ' ' && ch != '(' && ch != ')') {
            return true; // Found an invalid character
        }
    }
    return false; // All characters are valid
}

// Main function for the calculator
int main() {
    string expression;

    // Get user input
    while (true) {
        cout << "Please type the expression in Infix Notation:" << endl;
        getline(cin, expression);

        // Check for invalid characters
        if (hasInvalidCharacters(expression)) {
            cout << "Invalid input: Please use numbers and valid operators only." << endl;
            continue; // Prompt for input again
        }

        // Validate the expression
        if (!isDividingByZero(expression) || !hasOperatorErrors(expression) || !hasBalancedParentheses(expression)) {
            return 1; // Exit on error
        }
        break; // Exit the loop if input is valid
    }

    // Convert infix expression to Postfix
    vector<string> postfix; // Vector to hold the postfix expression
    stack<char> operatorStack; // Stack to hold operators during conversion

    for (size_t i = 0; i < expression.size(); i++) {
        char ch = expression[i];
        if (isdigit(ch) || ch == '.') {
            string number;
            // Read the entire number (including decimal point)
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                number += expression[i++];
            }
            postfix.push_back(number); // Add the complete number to the postfix vector
            i--; // Adjust index to account for the outer loop's increment
        } else if (ch == '(') {
            operatorStack.push(ch); // Push opening parenthesis onto the operator stack
        } else if (ch == ')') {
            // Pop operators until an opening parenthesis is found
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix.push_back(string(1, operatorStack.top())); // Add operator to postfix
                operatorStack.pop(); // Remove operator from stack
            }
            operatorStack.pop(); // Pop the '('
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Pop operators of higher or equal precedence
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix.push_back(string(1, operatorStack.top())); // Add operator to postfix
                operatorStack.pop(); // Remove operator from stack
            }
            operatorStack.push(ch); // Push the current operator onto the stack
        }
    }

    // Pop any remaining operators in the stack
    while (!operatorStack.empty()) {
        postfix.push_back(string(1, operatorStack.top()));
        operatorStack.pop();
    }

    // Display Postfix notation
    cout << "The Postfix notation:" << endl;
    for (const auto& elem : postfix) {
        cout << elem << " ";
    }
    cout << endl;

    // Calculate the result from Postfix
    stack<float> numStack; // Stack to hold numerical values for calculation

    for (const auto& token : postfix) {
        // If token is a number, convert and push onto the number stack
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1) || (token[0] == '.' && token.size() > 1)) {
            numStack.push(stof(token)); // Convert string to float and push onto the stack
        } else {
            // Operator found, pop two operands for the operation
            float number2 = numStack.top(); numStack.pop(); // Second operand
            float number1 = numStack.top(); numStack.pop(); // First operand
            float result;

            // Perform the operation based on the operator
            if (token == "+") {
                result = number1 + number2;
            } else if (token == "-") {
                result = number1 - number2;
            } else if (token == "*") {
                result = number1 * number2;
            } else if (token == "/") {
                result = number1 / number2;
            }
            numStack.push(result); // Push the result back onto the stack
        }
    }

    // Output the final result
    cout << "The Result:" << endl;
    cout << numStack.top() << endl; // Display the top of the number stack, which is the result

    return 0;
}

