#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>   
#include <ctime>     

// ������״ͼ���ܹ����ճ������������
int largestRectangleArea(std::vector<int>& heights) {
    std::stack<int> st;  // ջ�����ڴ洢���ӵ�����
    heights.push_back(0); // ������ĩβ��һ���߶�Ϊ0�����ӣ����ڴ���
    int maxArea = 0;

    for (int i = 0; i < heights.size(); ++i) {
        // ��ջ�ǿ��ҵ�ǰ�߶�С��ջ���ĸ߶�ʱ����ʼ�������
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int h = heights[st.top()];  // ջ���߶�
            st.pop();  // ����ջ��
            int width = st.empty() ? i : i - st.top() - 1;  // ������
            maxArea = std::max(maxArea, h * width);  // ����������
        }
        st.push(i);  // ��ǰ����������ջ
    }

    return maxArea;
}

// ��ӡ����
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// ������ɲ������ݲ��������������
void runTestCases() {
    std::srand(std::time(0));  // ʹ�õ�ǰʱ����Ϊ�������

    for (int i = 0; i < 10; ++i) {
        // ����������ȣ�1 <= heights.length <= 105
        int n = 1 + std::rand() % 105;  // �������
        std::vector<int> heights(n);

        // ����������Ӹ߶ȣ�0 <= heights[i] <= 104
        for (int j = 0; j < n; ++j) {
            heights[j] = std::rand() % 105;
        }

        std::cout << "�������� " << i + 1 << ": ";
        printVector(heights);

        // ���㲢������������
        int maxArea = largestRectangleArea(heights);
        std::cout << "���������: " << maxArea << std::endl;
    }
}

int main() {
    runTestCases();
    return 0;
}
