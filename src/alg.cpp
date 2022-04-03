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
    for (char d : inf) {
        if (ops.find(d) == ops.end()) {
            post += d;
            post += ' ';
        } else {
            if (d == ')') {
                while (opsStack.get() != '(') {
                    post += opsStack.get();
                    post += ' ';
                    opsStack.pop();
                }
                opsStack.pop();
            } else if (ops[d] > ops[opsStack.get()]) {
                opsStack.push(d);
            } else if (d == '(' || opsStack.isEmpty()) {
                opsStack.push(d);
            } else {
                while (ops[opsStack.get()] >= ops[d] && !opsStack.isEmpty()) {
                    post += opsStack.get();
                    post += ' ';
                    opsStack.pop();
                }
                opsStack.push(d);
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

    for (char d : post) {
        if (d == ' ') continue;
        std::size_t op = ops.find(d);
        if (op == std::string::npos) {
            operandsStack.push(d & 0xF);
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
