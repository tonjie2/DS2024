#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex() {
        real = 0;
        imag = 0;
    }

    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    double getReal() const {
        return real;
    }

    double getImag() const {
        return imag;
    }

    void setReal(double r) {
        real = r;
    }

    void setImag(double i) {
        imag = i;
    }

    // 计算复数的模
    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    // 重载运算符 ==
    friend bool operator==(const Complex& c1, const Complex& c2) {
        return c1.real == c2.real && c1.imag == c2.imag;
    }

    // 重载运算符 <<
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real << "+" << c.imag << "i";
        return out;
    }

    // 重载运算符 <
    friend bool operator<(const Complex& c1, const Complex& c2) {
        if (c1.modulus() != c2.modulus()) {
            return c1.modulus() < c2.modulus();
        }
        return c1.real < c2.real;
    }

    // 重载运算符 >
    friend bool operator>(const Complex& c1, const Complex& c2) {
        return c2 < c1;
    }
};

// 置乱
void shuffle(vector<Complex>& vec) {
    srand(time(NULL));
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        swap(vec[i], vec[j]);
    }
}

// 查找
int find(const vector<Complex>& vec, const Complex& c) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if (vec[i] == c) {
            return i;
        }
    }
    return -1;
}

// 插入
void insert(vector<Complex>& vec, const Complex& c) {
    vec.push_back(c);
}

// 删除
void remove(vector<Complex>& vec, const Complex& c) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if (vec[i] == c) {
            vec.erase(vec.begin() + i);
            break;
        }
    }
}

// 唯一化
void unique(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec[i] == vec[j]) {
                vec.erase(vec.begin() + j);
                n--;
                j--;
            }
        }
    }
}

// 逆序函数
void reverseComplex(vector<Complex>& vec) {
    std::reverse(vec.begin(), vec.end());
}

// 起泡排序
void bubbleSort(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 归并排序辅助函数
void merge(vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Complex> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        merge(vec, left, mid, right);
    }
}

// 区间查找
vector<Complex> rangeSearch(const vector<Complex>& vec, double m1, double m2) {
    vector<Complex> result;
    for (const auto& c : vec) {
        double mod = c.modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    return result;
}


int main() {
    vector<Complex> vec = {
        Complex(1, 2), Complex(3, 4), Complex(5, 6),
        Complex(1, 2), Complex(7, 8), Complex(9, 10)
    };

    cout << "原始复数向量： ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // 置乱
    shuffle(vec);
    cout << "置乱操作后的复数向量: ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    vector<Complex> vec_unsorted = vec;
    cout << endl;

    // 查找
    Complex target(1, 2);
    int index = find(vec, target);
    if (index != -1) {
        cout << "查到 " << target << "索引是：" << index << endl;
    }
    else {
        cout << "无法查到 " << target << endl;
    }

    // 插入
    Complex newComplex(5, 6);
    insert(vec, newComplex);
    cout << "插入1+2i后： " << newComplex << ": ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // 删除
    remove(vec, target);
    cout << "删除1+2i后：" << target << ": ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // 唯一化
    unique(vec);
    cout << "唯一化后： ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;


    // 乱序排序：
    vector<Complex> vecBubble = vec_unsorted;
    vector<Complex> vecMerge = vec_unsorted;

    clock_t start, end;

    start = clock();
    bubbleSort(vecBubble);
    end = clock();
    cout << "乱序的起泡排序时间: " << 1000 * double(end - start) / CLOCKS_PER_SEC << "ms" << endl;

    start = clock();
    mergeSort(vecMerge, 0, vecMerge.size() - 1);
    end = clock();
    cout << "乱序的归并排序时间: " << 1000 * double(end - start) / CLOCKS_PER_SEC << "ms" << endl;

    //顺序排序：
    start = clock();
    bubbleSort(vecBubble);
    end = clock();
    cout << "顺序的起泡排序时间: " << 1000 * double(end - start) / CLOCKS_PER_SEC << "ms" << endl;

    start = clock();
    mergeSort(vecMerge, 0, vecMerge.size() - 1);
    end = clock();
    cout << "顺序的归并排序时间: " << 100000 * double(end - start) / CLOCKS_PER_SEC << "ms" << endl;

    //逆序排序：
    reverseComplex(vecBubble);
    reverseComplex(vecMerge);
    start = clock();
    bubbleSort(vecBubble);
    end = clock();
    cout << "逆序的起泡排序时间: " << 1000 * double(end - start) / CLOCKS_PER_SEC << "ms" << endl;

    start = clock();
    mergeSort(vecMerge, 0, vecMerge.size() - 1);
    end = clock();
    cout << "逆序的归并排序时间: " << 100000 * double(end - start) / CLOCKS_PER_SEC << "ms" << endl;


    // 区间查找
    double m1 = 4.0, m2 = 9.0;
    vector<Complex> rangeResult = rangeSearch(vecMerge, m1, m2);
    cout << "Range search [" << m1 << ", " << m2 << "): ";
    for (const auto& c : rangeResult) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
