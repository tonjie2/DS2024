#include <iostream>
#include <string>
#include <stack>
#include <cctype> 
#include <stdexcept>  
// ջ���ݽṹ�����ڴ洢���ֺͷ���
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

// ������������ȼ���ʹ�ú������� map
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
        return 0;  // ���ŵ����ȼ�Ϊ 0
    default:
        return -1; // �Ƿ�������
    }
}

// �ж��Ƿ��ǲ�����
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// ���㺯����ִ�л�������������
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

// �Ƚϲ��������ȼ�
bool hasHigherPrecedence(char op1, char op2) {
    return getPrecedence(op1) >= getPrecedence(op2);
}

// �����������������ַ��������������
int evaluateExpression(const std::string& expr) {
    std::stack<int> values; // �洢������
    std::stack<char> ops;   // �洢������

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        // ���Կո�
        if (isspace(ch)) {
            continue;
        }

        // ��������֣������λ�����������������ջ
        if (isdigit(ch)) {
            int value = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                i++;
            }
            values.push(value);
            i--;  // ����һλ����Ϊ���ѭ���������� i
        }
        // ����������ţ�ֱ�����������ջ
        else if (ch == '(') {
            ops.push(ch);
        }
        // ����������ţ����������ڵı��ʽ
        else if (ch == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(op, val2, val1));
            }
            // ����������
            if (!ops.empty()) {
                ops.pop();
            }
        }
        // ����ǲ��������������ȼ�
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

    // ����ʣ�µĲ�����
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperator(op, val2, val1));
    }

    // ���ս��Ӧ���� values ջ��
    return values.top();
}

// ���Ժ���
int main() {
    std::string expression;

    std::cout << "��������ʽ��";
    std::getline(std::cin, expression);

    try {
        int result = evaluateExpression(expression);
        std::cout << "�������ǣ�" << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "����" << e.what() << std::endl;
    }

    return 0;
}
