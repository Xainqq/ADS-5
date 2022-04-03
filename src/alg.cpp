// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prior(char ch) {
    if (ch == '(') {
        return 1;
    }
    if (ch == '+' || ch == '-') {
        return 2;
    }
    if (ch == '*' || ch == '/') {
        return 3;
    }
    return -1;
}
std::string infx2pstfx(std::string inf) {
    TStack <char, 100> st;
    std::string post;
    for (int k = 0; k < inf.size(); k++) {
        int pr = prior(inf[k]);
        if ((prior(inf[k]) == -1) && (inf[k] != ')')) {
            if (!post.empty() && prior(inf[k - 1]) != -1) {
                post.push_back(' ');
            }
            post.push_back(inf[k]);
          
        } else if ((prior(inf[k]) > prior(st.get()))
                   || (st.isEmpty()) || (inf[k] == '(')) {
            st.push(inf[k]);
        } else {
            if (inf[k] == ')') {
                while (st.get() != '(') {
                    post.push_back(' ');
                    post.push_back(st.get());
                    st.pop();
                }
                st.pop();
            } else {
                while (prior(st.get()) >= prior(inf[k])) {
                    post.push_back(' ');
                    post.push_back(st.get());
                    st.pop();
                }
                st.push(inf[k]);
            }
        }
    }
    while (!st.isEmpty()) {
        post.push_back(' ');
        if (st.get() != '(') {
            post.push_back(st.get());
        }
        st.pop();
    }
    return post;
}
int convert(char count) {
    int i = 0;
    if (count >= '0' && count <= '9') {
        for (char k = '0'; k <= '9'; k++, i++) {
            if (count == k)
                return i;
        }
    }
    return -1;
}
int eval(std::string pref) {
    TStack<int, 100> st2;
    int oper = 0;
  for (int l = 0; l < pref.size(); l++) {
       if (convert(pref[l]) > -1) {
            oper = oper * 10 + convert(pref[l]);;
        } else {
            if (oper != 0) {
                st2.push(oper);
                oper = 0;
            }
            switch (pref[l]) {
            case '+':
            {
                int op1 = st2.get();
                st2.pop();
                int op2 = st2.get();
                st2.pop();
                st2.push(op1 + op2);
                break;
            }
            case '-':
            {
                int op1 = st2.get();
                st2.pop();
                int op2 = st2.get();
                st2.pop();
                st2.push(op2 - op1);
                break;
            }
            case '*':
            {
                int op1 = st2.get();
                st2.pop();
                int op2 = st2.get();
                st2.pop();
                st2.push(op1 * op2);
                break;
            }
            case '/':
            {
                int op1 = st2.get();
                st2.pop();
                int op2 = st2.get();
                st2.pop();
                st2.push(op2 / op1);
                break;
            }
            }
        }
    }
    return st2.get();
}
