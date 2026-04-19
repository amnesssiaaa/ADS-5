// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char oper) { //определение приоритета операций
    if (oper == '(') return 0;
    if (oper == ')') return 1;
    if (oper == '+' || oper == '-') return 2;
    if (oper == '*' || oper == '/') return 3;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack1;
  std::string result;
  for (size_t i = 0; i < inf.length(); ++i) {
        char simvol = inf[i];
        if (simvol >= '0' && simvol <= '9') {
            while (i < inf.length() && inf[i] >= '0' && inf[i] <= '9') {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        }
        else if (simvol == '+' || simvol == '-' || simvol == '*' || simvol == '/') {
            if (stack1.empty() || stack1.get() == '(' || prioritet(simvol) > prioritet(stack1.get())) {
                stack1.push(simvol);
            }
            else {
                while (!stack1.empty() && stack1.get() != '(' && prioritet(stack1.get()) >= prioritet(simvol)) {
                    result += stack1.get();
                    result += ' ';
                    stack1.pop();
                }
                stack1.push(simvol);
            }
        }
        else if (simvol == ')') {
            while (!stack1.empty() && stack1.get() != '(') {
                result += stack1.get();
                result += ' ';
                stack1.pop();
            }
            if (!stack1.empty() && stack1.get() == '(') {
                stack1.pop();
            }
        }
        else if (simvol == '(') {
            stack1.push(simvol);
        }
    }
    while (!stack1.empty()) {
        result += stack1.get();
        result += ' ';
        stack1.pop();
    }
      return result;
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
