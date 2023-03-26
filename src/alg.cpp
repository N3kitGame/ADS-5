// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
  // добавьте код стека
 private:
    T arr[100];
    int top;

 public:
    TStack() :top(-1) {}
    void push(T value) {
      if (isFull()) {
        throw std::string("Stack is full");
      } else {
        arr[++top] = value;
      }
    }
    const T& pop() {
      if (isEmpty()) {
        throw std::string("Stack is empty");
      } else {
        return arr[top--];
      }
    }
    bool isEmpty()const {
      return top == -1;
    }
    bool isFull()const {
      return top == size - 1;
    }
    const T& get()const {
      return arr[top];
    }
};

#endif  // INCLUDE_TSTACK_H_
  115  
src/alg.cpp
Marking files as viewed can help keep track of your progress, but will not affect your submitted reviewViewed
Comment on this file
@@ -3,12 +3,119 @@
#include <map>
#include "tstack.h"

int getPrior(char op) {
  std::pair<char, int> priority[6];
  switch (op) {
    case'(':
      priority[0].first = '(';
      priority[0].second = 0;
    case')':
      priority[1].first = ')';
      priority[1].second = 1;
    case'+':
      priority[2].first = '+';
      priority[2].second = 2;
    case'-':
      priority[3].first = '-';
      priority[3].second = 2;
    case'*':
      priority[4].first = '*';
      priority[4].second = 3;
    case'/':
      priority[5].first = '/';
      priority[5].second = 3;
  }
  int prior = -1;
  for (int j = 0; j < 6; ++j) {
    if (op == priority[j].first) {
      prior = priority[j].second;
      break;
    }
  }
  return prior;
}

std::string space1(const std::string& s) {
  if (s.length() <= 2) return s;
  int n = 2 - s.length() % 2;
  std::string r(s, 0, n);
  for (auto it = s.begin() + n; it != s.end();) {
    r += ' '; r += *it++;;
  }
  return r;
}

std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
  std::string work;
  TStack<char, 100> stack1;
  for (auto& op : inf) {
    int prior = getPrior(op);
    if (prior == -1) {
      work += op;
    } else {
      if (stack1.get() < prior || prior == 0 || stack1.isEmpty()) {
        stack1.push(op);
      } else if (op == ')') {
        char sm = stack1.get();
        while (getPrior(sm) >= prior) {
          work += sm;
          stack1.pop();
          sm = stack1.get();
        }
        stack1.pop();
      } else {
        char sm = stack1.get();
        while (getPrior(sm) >= prior) {
          work += sm;
          stack1.pop();
          sm = stack1.get();
        }
        stack1.push(op);
      }
    }
  }
  while (!stack1.isEmpty()) {
    work += stack1.get();
    stack1.pop();
  }
  work = space1(work);
  return work;
}

int eval(std::string pref) {
  // добавьте код
int count(const int& a, const int& b, const int& oper) {
  switch (oper) {
    default:
      break;
    case'+': return a + b;
    case'-': return a - b;
    case'*': return a * b;
    case'/': return a / b;
  }
  return 0;
}

int eval(std::string pref) {
  TStack<int, 100> stack1;
  std::string num = "";
  for (size_t i = 0; i < pref.size(); i++) {
    if (getPrior(pref[i]) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        num += pref[i];
        continue;
      } else {
        num += pref[i];
        stack1.push(atoi(num.c_str()));
        num = "";
      }
    } else {
      int b = stack1.get();
      stack1.pop();
      int a = stack1.get();
      stack1.pop();
      stack1.push(count(a, b, pref[i]));
    }
  }
  return stack1.get();
}
