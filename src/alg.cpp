// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> result;
  TStack<char, 100> stack;
  int currentNumber = 0;
  for (int i = 0; i < inf.size(); i++) switch (inf[i]) {
      case '+':
      case '-':
        if (stack.get() == '/' || stack.get() == '*')
          result.push(stack.getAndPop());
      case '*':
      case '/':
      case '(':
        stack.push(inf[i]);
        break;
      case ')':
        while (stack.get() != '(') result.push(stack.getAndPop());
        stack.pop();
        while (!stack.isEmpty()) {
          if (stack.get() == '(' || stack.get() == '+' || stack.get() == '-')
            break;
          result.push(stack.getAndPop());
        }
            break;
      default:
        result.push(inf[i]);
        break;
    }
  while (!stack.isEmpty()) result.push(stack.getAndPop());
  std::string resString = "";
  while (!result.isEmpty())
    resString =
        result.getAndPop() + (resString.size() == 0 ? "" : " " + resString);
  printf("\n123: %s\n\n", resString.c_str());
  return resString;
}

int eval(std::string pref) {
  TStack<int, 100> stack;
  for (int i = 0; i < pref.size(); i++) {
    if (pref[i] >= '0') stack.push(pref[i] - '0');
    switch (pref[i]) {
      case '+':
        stack.push(stack.getAndPop() + stack.getAndPop());
        break;
      case '-': {
        int tmp = stack.getAndPop();
        stack.push(stack.getAndPop() - tmp);
        break;
      }
      case '*':
        stack.push(stack.getAndPop() * stack.getAndPop());
        break;
      case '/': {
        int tmp = stack.getAndPop();
        stack.push(stack.getAndPop() / tmp);
        break;
      }
    }
  }
  return stack.get();
}
