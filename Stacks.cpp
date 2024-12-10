#include <iostream>
#include <stack>
#include <cctype>
#include <sstream>
#include <string>
using namespace std;

class Calculator {
private:
    stack<char> ops;
    stack<int> nums;

    int precedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    int applyOperator(int x, int y, char op) {
        switch (op) {
            case '+': return x + y;
            case '-': return x - y;
            case '*': return x * y;
            case '/': return x / y;
        }
        return 0;
    }

    string infixToPostfix(const string& expr) {
        stringstream output;
        for (size_t i = 0; i < expr.length(); i++) {
            if (expr[i] == ' ')
                continue;

            if (isdigit(expr[i])) {
                while (i < expr.length() && isdigit(expr[i])) {
                    output << expr[i];
                    i++;
                }
                output << ' ';
                i--;
            } else if (expr[i] == '(') {
                ops.push(expr[i]);
            } else if (expr[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    output << ops.top() << ' ';
                    ops.pop();
                }
                ops.pop();
            } else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                    output << ops.top() << ' ';
                    ops.pop();
                }
                ops.push(expr[i]);
            }
        }

        while (!ops.empty()) {
            output << ops.top() << ' ';
            ops.pop();
        }

        return output.str();
    }

    int evaluatePostfix(const string& postfix) {
        stringstream ss(postfix);
        string token;

        while (ss >> token) {
            if (isdigit(token[0])) {
                nums.push(stoi(token));
            } else {
                int y = nums.top(); nums.pop();
                int x = nums.top(); nums.pop();
                nums.push(applyOperator(x, y, token[0]));
            }
        }

        return nums.top();
    }

public:
    int calculate(const string& expr) {
        string postfix = infixToPostfix(expr);
        return evaluatePostfix(postfix);
    }
};

int main() {
    Calculator calculator;
    string expression;

    cout << "Enter an expression: ";
    getline(cin, expression);
    
    int result = calculator.calculate(expression);
    cout << "Result: " << result << endl;

    return 0;
}
