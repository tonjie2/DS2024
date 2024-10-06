#include <iostream>
#include <stdexcept>

typedef int Rank; // ��
#define DEFAULT_CAPACITY 3 // Ĭ�ϵĳ�ʼ����

template <typename T>
class Vector {
protected:
    Rank _size;         // ��ǰ��С
    int _capacity;      // ��ǰ����
    T* _elem;          // ����ָ��

    void copyFrom(T const* A, Rank lo, Rank hi);  // ������������ A[lo, hi)
    void expand();    // ����
    void shrink();    // ����
    bool bubble(Rank lo, Rank hi); // ɨ�轻��
    void bubbleSort(Rank lo, Rank hi); // ð�������㷨
    Rank max(Rank lo, Rank hi); // ѡȡ���Ԫ��
    void selectionSort(Rank lo, Rank hi); // ѡ�������㷨
    void merge(Rank lo, Rank mi, Rank hi); // �鲢�㷨
    void mergeSort(Rank lo, Rank hi); // �鲢�����㷨
    Rank partition(Rank lo, Rank hi); // ��㹹���㷨
    void quickSort(Rank lo, Rank hi); // ���������㷨
    void heapSort(Rank lo, Rank hi); // ������

public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0); // ����Ϊ c����СΪ s������Ԫ�س�ʼ��Ϊ v
    Vector(T const* A, Rank lo, Rank hi); // �������临��
    Vector(T const* A, Rank n); // �������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi); // �������临��
    Vector(Vector<T> const& V); // �������帴��

    ~Vector(); // ��������

    // �����ʽӿ�
    Rank size() const { return _size; } // ��ǰ��С
    bool empty() const { return _size == 0; } // �Ƿ�Ϊ��
    Rank find(T const& e) const; // ���������������
    Rank find(T const& e, Rank lo, Rank hi) const; // ���������������

    // ��д���ʽӿ�
    T& operator[](Rank r) const; // �����±������
    Vector<T>& operator=(Vector<T> const&); // ���ظ�ֵ������
    T remove(Rank r); // ɾ����Ϊ r ��Ԫ��
    Rank insert(Rank r, T const& e); // ����Ԫ��
    Rank insert(T const& e) { return insert(_size, e); } // ��ΪĩԪ�ز���
    void sort(Rank lo, Rank hi); // �� [lo, hi) ����
    void sort() { sort(0, _size); } // ��������
    void traverse(void (*visit)(T&)); // ������ʹ�ú���ָ�룩
    template <typename VST> void traverse(VST& visit); // ������ʹ�ú�������
};

template <typename T>
Vector<T>::Vector(int c, int s, T v) : _size(s), _capacity(c) {
    _elem = new T[_capacity];
    for (_size = 0; _size < s; _size++) {
        _elem[_size] = v; // ��ʼ������Ԫ��
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _elem; // �ͷ��ڲ��ռ�
}

// ������������ A[lo, hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _capacity = hi - lo; // �趨����Ϊ hi - lo
    _elem = new T[_capacity];
    _size = 0;
    for (Rank i = lo; i < hi; i++) {
        _elem[_size++] = A[i]; // �������
    }
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return; // ����ռ��㹻�򷵻�
    T* oldElem = _elem; // ���ݾ�����
    _capacity = (_capacity < 1) ? 1 : 2 * _capacity; // ����
    _elem = new T[_capacity]; // ���·����ڴ�
    for (Rank i = 0; i < _size; i++) {
        _elem[i] = oldElem[i]; // ���ƾ����鵽������
    }
    delete[] oldElem; // �ͷž������ڴ�
}

template <typename T>
T& Vector<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size) throw std::out_of_range("Index out of range");
    return _elem[r]; // ���ص� r ��Ԫ��
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
    if (this != &V) { // ���Ҹ�ֵ���
        delete[] _elem; // �ͷž�����
        copyFrom(V._elem, 0, V._size); // ����������
    }
    return *this; // ��������
}

template <typename T>
T Vector<T>::remove(Rank r) {
    if (r < 0 || r >= _size) throw std::out_of_range("Index out of range");
    T e = _elem[r]; // ���ݴ�ɾ��Ԫ��
    for (Rank i = r + 1; i < _size; i++) {
        _elem[i - 1] = _elem[i]; // ǰ��
    }
    _size--; // ��ģ��С
    _elem[_size].~T(); // ����������������� T ��Ҫ��
    if (_size < _capacity / 4) shrink(); // ������Ҫ����
    return e; // ���ر�ɾ����Ԫ��
}

// �����㷨�����򡢲��ҵȣ����Լ���ʵ��

template <typename T>
void Vector<T>::shrink() {
    if (_size * 4 > _capacity) return; // ���װ�����Ӵ��� 1/4������
    T* oldElem = _elem; // ���ݾ�����
    _capacity = _capacity / 2; // ����Ϊһ��
    _elem = new T[_capacity]; // ���·����ڴ�
    for (Rank i = 0; i < _size; i++) {
        _elem[i] = oldElem[i]; // ���ƾ����鵽������
    }
    delete[] oldElem; // �ͷž������ڴ�
}

template <typename T>
Rank Vector<T>::find(T const& e) const {
    for (Rank i = 0; i < _size; i++) {
        if (_elem[i] == e) return i; // �ҵ���������
    }
    return -1; // δ�ҵ����� -1
}
