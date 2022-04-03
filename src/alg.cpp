// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACKH
#define INCLUDE_TSTACKH

template<typename T, int size>
class TStack {
 private:
  T arr[100];
  int top;

 public:
  TStack() : top(-1) {}
  bool isEmpty() const {
    return top == -1;
  }

  bool isFull() const {
    return top == size - 1;
  }

  T get() {
    if (!isEmpty())
      return *(arr + top);
    else
      throw "Stack is empty yet, add more elements";
  }

  void pop() {
    if (!isEmpty())
      --top;
  }

  void push(T value) {
    if (!isFull())
      *(arr + ++top) = value;
    else
      throw "Stack is already full, remove some elements";
  }
};
#endif  // INCLUDE_TSTACKH

TStack<char, 100> stack1;
TStack<int, 100> stack2;

#include <string>
#include <map>
#include "tstack.h"

int prior(char operation) {
  if (operation == '*'  operation == '/')
    return 2;
  if (operation == '+'  operation == '-')
    return 1;
  if (operation == '(')
    return 0;
  return -1;
}

int convert(char num) {
  int analogue = 0;
  if (num >= '0' && num <= '9') {
    for (char i = '0'; i <= '9'; i++, analogue++) {
      if (num == i)
        return analogue;
    }
  }
  return -1;
}
std::string infx2pstfx(std::string inf) {
  std::string pstf = "";
  for (int i = 0; i < inf.size(); i++) {
    if (prior(inf[i]) == -1) {
      if (inf[i] == ')') {
        while (prior(stack1.get()) != 0) {
          if (pstf[pstf.size() - 1] != ' ')
            pstf += " ";
          pstf += stack1.get();
          pstf += " ";
          stack1.pop();
        }
        stack1.pop();
        continue;
      }
      pstf += inf[i];
      if (prior(inf[i + 1]) != -1)
        pstf += " ";
    } else if (stack1.isEmpty()  prior(inf[i]) == 0 
             prior(inf[i]) > prior(stack1.get())) {
      stack1.push(inf[i]);
    } else if (prior(inf[i]) <= prior(stack1.get())) {
      if (pstf[pstf.size() - 1] != ' ')
        pstf += " ";
      pstf += stack1.get();
      pstf += " ";
      stack1.pop();
      stack1.push(inf[i]);
    }
  }
  while (!stack1.isEmpty()) {
    if (pstf[pstf.size() - 1] != ' ')
      pstf += " ";
    pstf += stack1.get();
    pstf += " ";
    stack1.pop();
  }
  return pstf.substr(0, pstf.size() - 1);
}
int eval(std::string pref) {
  int operand = 0;
  for (int i = 0; i < pref.size(); i++) {
    int current = convert(pref[i]);
    if (current > -1) {
      operand = operand * 10 + current;
    } else {
      if (operand != 0) {
        stack2.push(operand);
        operand = 0;
      }
      switch (pref[i]) {
        case '+':
          {
            int oper2 = stack2.get();
            stack2.pop();
            int oper1 = stack2.get();
            stack2.pop();
            stack2.push(oper1 + oper2);
            break;
          }
        case '-':
          {
            int oper2 = stack2.get();
            stack2.pop();
            int oper1 = stack2.get();
            stack2.pop();
            stack2.push(oper1 - oper2);
            break;
          }
        case '*':
          {
            int oper2 = stack2.get();
            stack2.pop();
            int oper1 = stack2.get();
            stack2.pop();
            stack2.push(oper1 * oper2);
            break;
          }
        case '/':
          {
            int oper2 = stack2.get();
            stack2.pop();
            int oper1 = stack2.get();
            stack2.pop();
            stack2.push(oper1 / oper2);
            break;
          }
      }
    }
  }
  return stack2.get();
}
