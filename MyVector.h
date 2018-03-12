#pragma once
#pragma once
#include <iostream>
using namespace std;
template<typename T>
class MyVector {
private:
	T *m_date;
	unsigned int m_size;
	bool unsort;
public:
	~MyVector() { delete[]this->m_date; };
	MyVector(unsigned int siz = 0) :m_size(siz), unsort(true) {
		this->m_date = nullptr;
	};
	MyVector(unsigned int siz, const T &n) :m_size(siz), unsort(true) {
		this->m_size = siz;
		this->m_date = new T[siz];
		for (unsigned int i = 0; i < siz; i++)
		{
			m_date[i] = n;
		}
	};
	MyVector(const MyVector& myvector) {
		this->m_size = myvector.m_size;
		this->unsort = myvector.unsort;
		this->m_date = new T[myvector.m_size];
		for (unsigned int i = 0; i < myvector.m_size; i++)
		{
			m_date[i] = myvector.m_date[i];
		}
	};
	MyVector & operator=(const MyVector&myvector) {
		if (this->date) delete[]date;
		this->unsort = myvector.unsort;
		this->m_size = myvector.m_size;
		for (unsigned int i = 0; i <myvector.m_size; i++)
		{
			m_date[i] = myvector.m_date[i];
		}
		return *this;
	}
	inline const unsigned int getsize() const {
		return this->m_size;
	}
	void resize(unsigned int siz, const T& t) {
		if (siz == m_size) return;
		T *date = new T[m_size];
		if (this->m_date) {
			for (unsigned int i = 0; i < m_size; i++) {
				date[i] = m_date[i];
			}
			delete[]m_date;
			m_date = nullptrptr;
		}
		this->m_date = new T[siz];
		if (siz > this->m_size) {
			for (unsigned int i = m_size; i < siz; i++)
				m_date[i] = t;
			for (unsigned int i = 0; i < m_size; i++)
				m_date[i] = date[i];
		}
		else {
			for (unsigned int i = 0; i < siz; i++)
				m_date[i] = date[i];
		}
		this->m_size = siz;
		delete[]date;
		date = nullptrptr;
	}
	void resize(unsigned int siz) {
		if (siz == m_size) return;
		T *date = new T[m_size];
		if (this->m_date) {
			for (unsigned int i = 0; i < m_size; i++) {
				date[i] = m_date[i];
			}
			delete[]m_date;
			m_date = nullptr;
		}
		this->m_date = new T[siz];
		if (siz > this->m_size) {
			for (unsigned int i = 0; i < m_size; i++)
				m_date[i] = date[i];
		}
		else {
			for (unsigned int i = 0; i < siz; i++)
				m_date[i] = date[i];
		}
		this->m_size = siz;
		delete[]date;
		date = nullptr;
	}
	inline bool empty()const {
		return (this->m_size == 0) ? true : false;
	}
	inline T & operator[](unsigned int t) {
		return m_date[t];
	}
	inline const T& operator[](unsigned int t)const {
		return m_date[t];
	}
	T& at(unsigned int t) {
		if (t >= m_size) throw out_of_range("out_of_range");
		else return m_date[t];
	}
	const T& at(unsigned int t)const {
		if (t >= m_size) throw out_of_range("out_of_range");
		else return m_date[t];
	}
	T &back() {
		if (this->m_size == 0) throw length_error("length_error");
		return m_date[m_size - 1];
	}
	const T&back()const {
		if (this->m_size == 0) throw length_error("length_error");
		return m_date[m_size - 1];
	}
	T &front() {
		if (this->m_size == 0) throw length_error("length_error");
		return m_date[0];
	}
	const T &front()const {
		if (this->m_size == 0) throw length_error("length_error");
		return m_date[0];
	}
	void push_back(const T& t) {
		this->resize(this->m_size + 1);
		m_date[m_size - 1] = t;
	}
	void push_back(T& t) {
		this->resize(this->m_size + 1);
		m_date[m_size - 1] = t;
	}
	void pop_back() {
		if (this->m_size == 0) throw length_error("length_error");
		this->resize(m_size - 1);
	}
	void insert(unsigned int i, const T& t) {
		if (this->m_size == 0) throw length_error("length_error");
		if (this->m_size<i) throw length_error("length_error");
		this->resize(this->m_size + 1);
		for (unsigned int j = m_size - 1; j > i; j--)
			m_date[j] = m_date[j - 1];
		m_date[i] = t;
	}
	void insert(unsigned int i, int num, const T& t) {
		if (this->m_size == 0) throw length_error("length_error");
		if (this->m_size<i) throw length_error("length_error");
		this->resize(num + this->m_size);
		for (unsigned int j = m_size - num - 1; j >= i; j--) {
			m_date[j + num] = m_date[j];
			if (j == i) break;
		}
		for (unsigned int k = i; k < i + num; k++) {
			m_date[k] = t;
		}
	}
	void erase(unsigned int i) {
		if (this->m_size == 0) throw length_error("length_error");
		if (this->m_size<i) throw length_error("length_error");
		for (unsigned int j = i; j < m_size - 1; j++)
			m_date[j] = m_date[j + 1];
		this->resize(this->m_size - 1);
	}
	void clear() {
		this->m_size = 0;
	}
	void sort() {
		if (this->unsort == false) return;
		T in;
		for (unsigned int i = 0; i < m_size; i++)
			for (unsigned int j = 0; j < m_size - i - 1; j++) {
				if (m_date[j] > m_date[j + 1]) {
					in = m_date[j];
					m_date[j] = m_date[j + 1];
					m_date[j + 1] = in;
				}
			}
		this->unsort = false;
	}
	int binarySearch(const T& key) {
		if (this->m_size == 0) throw length_error("length_error");
		if (this->unsort == true) this->sort();
		int high = m_size - 1, low = 0, mid = -1;
		while (low <= high) {
			mid = (low + high) / 2;
			if (key < m_date[mid]) high = mid - 1;
			else if (key > m_date[mid]) low = mid + 1;
			else {
				return mid;
			}
		}
		if (!(m_date[mid] == key)) mid = -1;
		return mid;
	}
	void show() {
		for (unsigned int i = 0; i < m_size; i++) {
			cout << m_date[i] <<endl;
			//if (i == m_size - 1) cout << endl;
		}
	}
private:
	void quickSort(int, int);
};
template<typename T>
void MyVector<T>::quickSort(int l, int r)
{
	if (this->m_size == 0) throw length_error("length_error");
	if (l < r) {
		int i = l, j = r, x = m_data[l];
		while (i < j) {
			while (i < j&&m_data[j] >= x)
				j--;
			if (i < j)
				m_data[i++] = m_data[j];
			while (i < j&&m_data[i] < x)
				i++;
			if (i < j)
				m_data[j--] = data[i];
		}
		m_data = x;
		quickSort(l, i - 1);
		quickSort(i + 1, r);
	}
}
