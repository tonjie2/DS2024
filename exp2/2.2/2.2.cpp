#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>   
#include <ctime>     

// 计算柱状图中能够勾勒出的最大矩形面积
int largestRectangleArea(std::vector<int>& heights) {
    std::stack<int> st;  // 栈，用于存储柱子的索引
    heights.push_back(0); // 在数组末尾加一个高度为0的柱子，便于处理
    int maxArea = 0;

    for (int i = 0; i < heights.size(); ++i) {
        // 当栈非空且当前高度小于栈顶的高度时，开始计算面积
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int h = heights[st.top()];  // 栈顶高度
            st.pop();  // 弹出栈顶
            int width = st.empty() ? i : i - st.top() - 1;  // 计算宽度
            maxArea = std::max(maxArea, h * width);  // 更新最大面积
        }
        st.push(i);  // 当前柱子索引入栈
    }

    return maxArea;
}

// 打印向量
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

// 随机生成测试数据并计算最大矩形面积
void runTestCases() {
    std::srand(std::time(0));  // 使用当前时间作为随机种子

    for (int i = 0; i < 10; ++i) {
        // 生成随机长度，1 <= heights.length <= 105
        int n = 1 + std::rand() % 105;  // 随机长度
        std::vector<int> heights(n);

        // 生成随机柱子高度，0 <= heights[i] <= 104
        for (int j = 0; j < n; ++j) {
            heights[j] = std::rand() % 105;
        }

        std::cout << "测试数据 " << i + 1 << ": ";
        printVector(heights);

        // 计算并输出最大矩形面积
        int maxArea = largestRectangleArea(heights);
        std::cout << "最大矩形面积: " << maxArea << std::endl;
    }
}

int main() {
    runTestCases();
    return 0;
}
