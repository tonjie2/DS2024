#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

// Huffman 树节点结构
struct HuffNode {
    char data;
    int freq;
    HuffNode* left;
    HuffNode* right;
    HuffNode(char d, int f, HuffNode* l = nullptr, HuffNode* r = nullptr)
        : data(d), freq(f), left(l), right(r) {}
};

// 比较器，用于优先队列
struct Compare {
    bool operator()(HuffNode* l, HuffNode* r) {
        return l->freq > r->freq;
    }
};

// 读取文件并返回文本内容
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// 函数：统计字母频率
std::unordered_map<char, int> calculateFrequency(const std::string& text) {
    std::unordered_map<char, int> freqMap;
    for (unsigned char ch : text) {
        if (isalpha(ch)) {
            ch = tolower(ch);  // 转为小写
            freqMap[ch]++;
        }
    }
    return freqMap;
}

// 构建 Huffman 树
HuffNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, Compare> pq;
    for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        char ch = it->first;
        int freq = it->second;
        pq.push(new HuffNode(ch, freq));
    }


    while (pq.size() > 1) {
        HuffNode* left = pq.top(); pq.pop();
        HuffNode* right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new HuffNode('\0', sum, left, right));
    }

    return pq.top();  // 返回根节点
}

// 生成编码表
void generateCodes(HuffNode* root, const std::string& str, std::unordered_map<char, std::string>& huffCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffCode[root->data] = str;
    }

    generateCodes(root->left, str + "0", huffCode);
    generateCodes(root->right, str + "1", huffCode);
}

// 对单词进行编码
std::string encodeWord(const std::string& word, const std::unordered_map<char, std::string>& huffCode) {
    std::string encoded;
    for (char ch : word) {
        ch = tolower(ch);
        encoded += huffCode.at(ch);  // 获取每个字母的编码
    }
    return encoded;
}

int main() {
    // 从文件中读取文本内容
    std::string text = readFile("text.txt");
    if (text.empty()) {
        std::cerr << "Error: Unable to read file or file is empty." << std::endl;
        return 1;
    }

    // 计算频率
    auto freqMap = calculateFrequency(text);

    // 构建 Huffman 树
    HuffNode* root = buildHuffmanTree(freqMap);

    // 生成编码表
    std::unordered_map<char, std::string> huffCode;
    generateCodes(root, "", huffCode);

    // 对指定单词进行编码
    std::string word = "freedom";
    std::string encodedWord = encodeWord(word, huffCode);
    std::cout << "'freedom'的Huffman编码: " << encodedWord << std::endl;

    return 0;
}
