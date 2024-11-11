#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

// Huffman ���ڵ�ṹ
struct HuffNode {
    char data;
    int freq;
    HuffNode* left;
    HuffNode* right;
    HuffNode(char d, int f, HuffNode* l = nullptr, HuffNode* r = nullptr)
        : data(d), freq(f), left(l), right(r) {}
};

// �Ƚ������������ȶ���
struct Compare {
    bool operator()(HuffNode* l, HuffNode* r) {
        return l->freq > r->freq;
    }
};

// ��ȡ�ļ��������ı�����
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// ������ͳ����ĸƵ��
std::unordered_map<char, int> calculateFrequency(const std::string& text) {
    std::unordered_map<char, int> freqMap;
    for (unsigned char ch : text) {
        if (isalpha(ch)) {
            ch = tolower(ch);  // תΪСд
            freqMap[ch]++;
        }
    }
    return freqMap;
}

// ���� Huffman ��
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

    return pq.top();  // ���ظ��ڵ�
}

// ���ɱ����
void generateCodes(HuffNode* root, const std::string& str, std::unordered_map<char, std::string>& huffCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffCode[root->data] = str;
    }

    generateCodes(root->left, str + "0", huffCode);
    generateCodes(root->right, str + "1", huffCode);
}

// �Ե��ʽ��б���
std::string encodeWord(const std::string& word, const std::unordered_map<char, std::string>& huffCode) {
    std::string encoded;
    for (char ch : word) {
        ch = tolower(ch);
        encoded += huffCode.at(ch);  // ��ȡÿ����ĸ�ı���
    }
    return encoded;
}

int main() {
    // ���ļ��ж�ȡ�ı�����
    std::string text = readFile("text.txt");
    if (text.empty()) {
        std::cerr << "Error: Unable to read file or file is empty." << std::endl;
        return 1;
    }

    // ����Ƶ��
    auto freqMap = calculateFrequency(text);

    // ���� Huffman ��
    HuffNode* root = buildHuffmanTree(freqMap);

    // ���ɱ����
    std::unordered_map<char, std::string> huffCode;
    generateCodes(root, "", huffCode);

    // ��ָ�����ʽ��б���
    std::string word = "freedom";
    std::string encodedWord = encodeWord(word, huffCode);
    std::cout << "'freedom'��Huffman����: " << encodedWord << std::endl;

    return 0;
}
