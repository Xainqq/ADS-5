// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  // добавьте код
    TStack<char, 20> opsStack;
    std::string post;
    std::map<char, int> ops;
    ops['('] = 0;
    ops[')'] = 0;
    ops['+'] = 1;
    ops['-'] = 1;
    ops['*'] = 2;
    ops['/'] = 2;
    for (char c : inf) {
        if (ops.find(c) == ops.end()) {
            post += c;
            post += ' ';
        } else {
            if (c == ')') {
                while (opsStack.get() != '(') {
                    post += opsStack.get();
                    post += ' ';
                    opsStack.pop();
                }
                opsStack.pop();
            } else if (c == '(' || opsStack.isEmpty()) {
                opsStack.push(c);
            } else if (ops[c] > ops[opsStack.get()]) {
                opsStack.push(c);
            } else {
                while (ops[opsStack.get()] >= ops[c] && !opsStack.isEmpty()) {
                    post += opsStack.get();
                    post += ' ';
                    opsStack.pop();
                }
                opsStack.push(c);
            }
        }
    }
    while (!opsStack.isEmpty()) {
        post += opsStack.get();
        post += ' ';
        opsStack.pop();
    }
    post.pop_back();
    return post;
}

int eval(std::string post) {
    TStack<int, 20> operandsStack;
    std::string ops = "+-*/";

    for (char c : post) {
        if (c == ' ') continue;
        std::size_t op = ops.find(c);
        if (op == std::string::npos) {
            operandsStack.push(c & 0xF);
        } else {
            int arg2 = operandsStack.get();
            operandsStack.pop();
            int arg1 = operandsStack.get();
            operandsStack.pop();
            int result;
            switch (ops[op]) {
            case '+':
                result = arg1 + arg2;
                break;
            case '-':
                result = arg1 - arg2;
                break;
            case '*':
                result = arg1 * arg2;
                break;
            case '/':
                result = arg1 / arg2;
                break;
            }
            operandsStack.push(result);
        }
    }
    return operandsStack.get();
}
