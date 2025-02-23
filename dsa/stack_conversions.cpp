#include "stack.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

int precedence(char ch) {
  if (ch == '+' || ch == '-')
    return 1;
  else if (ch == '*' || ch == '/')
    return 2;
  else if (ch == '$')
    return 3;
  else
    return 0;
}

void infixToPostfixConversion(Stack<char> *opStack, Stack<char> *postStack,
                              string infix) {

  int i = 0;
  int len = infix.length();
  while (i < len) {
    char scannedCh = infix[i];
    cout << "Scanned Character: " << scannedCh << endl;
    if (scannedCh == '(') {
      cout << "Pushing ( to opStack" << endl;
      opStack->push(scannedCh);
    } else if (scannedCh == ')') {
      cout << "Popping from opStack until ( is found" << endl;
      while (opStack->peek() != '(') {
        cout << "Pushing" << opStack->peek() << " to postStack" << endl;
        postStack->push(opStack->pop());
      }
      opStack->pop();
    } else if (scannedCh == '+' || scannedCh == '$' || scannedCh == '-' ||
               scannedCh == '*' || scannedCh == '/') {
      cout << "Operator Found: " << scannedCh << endl;
      if (opStack->isEmpty()) {
        cout << "Stack is empty, pushing " << scannedCh << " to opStack"
             << endl;
        opStack->push(scannedCh);
      } else if (precedence(scannedCh) > precedence(opStack->peek())) {
        cout << "Precedence of " << scannedCh
             << " is greater than opStack top: " << opStack->peek() << endl;
        cout << "Pushing " << scannedCh << " to opStack" << endl;
        opStack->push(scannedCh);
      } else {
        cout << "Precedence of " << scannedCh
             << " is less than opStack top: " << opStack->peek() << endl;
        while (!opStack->isEmpty() &&
               precedence(scannedCh) <= precedence(opStack->peek())) {
          cout << "Pushing " << opStack->peek() << " to postStack" << endl;
          postStack->push(opStack->pop());
        }
        opStack->push(scannedCh);
      }
    } else {
      cout << "Operand Found: " << scannedCh << endl;
      cout << "Pushing " << scannedCh << " to postStack" << endl;
      postStack->push(scannedCh);
    }
    i++;
  }
  // Push remaining operators to postStack
  while (!opStack->isEmpty()) {
    postStack->push(opStack->pop());
  }
}
int main() {
  int choice;
  Stack<char> *opStack = new Stack<char>();
  Stack<char> *postStack = new Stack<char>();
  string infix;

  cout << "What operation do you want to perform? " << endl;
  cout << "1. Infix to Postfix Coversion" << endl;
  cout << "2. Infix to Prefix Coversion" << endl;
  cout << "3. Postfix Evaluation" << endl;
  cout << "4. Prefix Evaluation" << endl;

  cin >> choice;

  switch (choice) {
  case 1:
    cout << "Enter your infix expression: " << endl;
    cin >> infix;
    infixToPostfixConversion(opStack, postStack, infix);
    postStack->traverse();
    break;
  case 2:
    cout << "Enter your infix expression: " << endl;
    cin >> infix;
    // Reverse the infix notation, ( to be replaced with ) and vice versa
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < infix.length(); i++) {
      if (infix[i] == '(') {
        infix[i] = ')';
      } else if (infix[i] == ')') {
        infix[i] = '(';
      }
    }
    //  Same rules as postfix conversions
    infixToPostfixConversion(opStack, postStack, infix);
    // Display the prefix expression
    cout << "Prefix Expression: " << endl;
    while (!postStack->isEmpty()) {
      cout << (postStack->pop()) << " ";
    }
    break;
  }
}
