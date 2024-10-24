#include <iostream>
#include <string>
#include <stack>
#include <cctype> 
#include <stdexcept>  
// 栈数据结构，用于存储数字和符号
template<typename T>
class Stack {
private:
    std::stack<T> stack;
public:
    void push(const T& item) {
        stack.push(item);
    }

    T pop() {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow");
        }
        T item = stack.top();
        stack.pop();
        return item;
    }

    T top() const {
        if (stack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack.top();
    }

    bool isEmpty() const {
        return stack.empty();
    }
};

// 定义操作符优先级，使用函数代替 map
int getPrecedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 0;  // 括号的优先级为 0
    default:
        return -1; // 非法操作符
    }
}

// 判断是否是操作符
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 运算函数，执行基本的四则运算
int applyOperator(char op, int b, int a) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    default: throw std::runtime_error("Unknown operator");
    }
}

// 比较操作符优先级
bool hasHigherPrecedence(char op1, char op2) {
    return getPrecedence(op1) >= getPrecedence(op2);
}

// 计算器函数，输入字符串，输出计算结果
int evaluateExpression(const std::string& expr) {
    std::stack<int> values; // 存储操作数
    std::stack<char> ops;   // 存储操作符

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        // 忽略空格
        if (isspace(ch)) {
            continue;
        }

        // 如果是数字，处理多位数并将其推入操作数栈
        if (isdigit(ch)) {
            int value = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                i++;
            }
            values.push(value);
            i--;  // 回退一位，因为外层循环还会增加 i
        }
        // 如果是左括号，直接推入操作符栈
        else if (ch == '(') {
            ops.push(ch);
        }
        // 如果是右括号，处理括号内的表达式
        else if (ch == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(op, val2, val1));
            }
            // 弹出左括号
            if (!ops.empty()) {
                ops.pop();
            }
        }
        // 如果是操作符，处理优先级
        else if (isOperator(ch)) {
            while (!ops.empty() && hasHigherPrecedence(ops.top(), ch)) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(op, val2, val1));
            }
            ops.push(ch);
        }
        else {
            throw std::runtime_error("Invalid character in expression");
        }
    }

    // 处理剩下的操作符
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperator(op, val2, val1));
    }

    // 最终结果应该在 values 栈顶
    return values.top();
}

// 测试函数
int main() {
    std::string expression;

    std::cout << "请输入算式：";
    std::getline(std::cin, expression);

    try {
        int result = evaluateExpression(expression);
        std::cout << "计算结果是：" << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }

    return 0;
}
