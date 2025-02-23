#include <iostream>
#include <stdexcept>
using namespace std;
template <class T> class Stack {

private:
  static const int MAX = 100;
  T *data;
  int top;

public:
  Stack() {
    data = new T[MAX];
    top = -1;
  }
  ~Stack() { delete[] data; }
  void push(T value) {
    // CHeck if stack is full
    if (isFull()) {
      // Throw Stack overflow exception
      throw runtime_error("Stack overflow");
    }
    data[++top] = value;
  }

  T pop() {
    if (isEmpty()) {
      throw runtime_error("Stack underflow");
    }
    T topElem = peek();
    top--;
    return topElem;
  }
  T peek() {
    if (isEmpty()) {
      throw runtime_error("Stack underflow!");
    }
    return data[top];
  }

  int size() { return top + 1; }

  void traverse() {
    cout << "Traversing Stack: ";
    for (int i = 0; i <= top; i++) {
      cout << data[i] << " ";
    }
  }

  bool isEmpty() { return top < 0; }
  bool isFull() { return top == MAX - 1; }
};