// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char oper) { // определение приоритета операций
    if (oper == '(') return 0;
    if (oper == ')') return 1;
    if (oper == '+' || oper == '-') return 2;
    if (oper == '*' || oper == '/') return 3;
    return -1;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack1;
    std::string result;
    for (size_t i = 0; i < inf.length(); ++i) {
        char simvol = inf[i];
        if (simvol >= '0' && simvol <= '9') {
            size_t start = i;
            while (start < inf.length() && inf[start] >= '0' && inf[start] <= '9') {
                result += inf[start];
                ++start;
            }
            result += ' ';
            i = start - i; 
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

int Operation(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return 0;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack2;
    for (size_t i = 0; i < pref.length(); ++i) {
        char simvol = pref[i];
        if (simvol == ' ') continue;
        if (simvol >= '0' && simvol <= '9') {
            int num = 0;
            while (i < pref.length() && pref[i] >= '0' && pref[i] <= '9') {
                num = num * 10 + (pref[i] - '0');
                ++i;
            }
            stack2.push(num);
            --i;
        }
        else if (simvol == '+' || simvol == '-' || simvol == '*' || simvol == '/') {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            stack2.push(Operation(b, a, simvol));
        }
    }
    return stack2.get();
}
