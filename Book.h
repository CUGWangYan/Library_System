#pragma once
#include <iostream>
#include <string>
using namespace std;
class Book {
	string m_Id;
	string m_Name;
	string m_author;
	int m_stock;
	int m_store;
public:
	Book(string id, string name, string author, int stock, int store) :m_Id(id), m_Name(name), m_author(author), m_stock(stock), m_store(store) {}
	Book(string id) :m_Id(id) {}
	Book() = default;
	Book(const Book&) = default;
	~Book() {}
	void lend() {
		this->m_stock--;
	}
	void returnbook() {
		this->m_stock++;
	}
	void bookentry() {
		this->m_store++;
	}
	friend istream& operator>>(istream&in, Book&book) {
		in >> book.m_Id >> book.m_Name >> book.m_author >> book.m_stock >> book.m_store;
		return in;
	}
	friend ostream& operator<<(ostream&out, const Book&book) {
		out <<" ID of Book£º "<< book.m_Id << " Name of Book£º "<<book.m_Name<<" Author of Book£º "<<book.m_author <<" Stock of Book: " <<book.m_stock <<" Store of Book: "<< book.m_store;
		return out;
	}
	bool operator<(const Book&right) {
		if (this->m_Id < right.m_Id) return true;
		else return false;
	}
	bool operator>(const Book&left) {
		if (this->m_Id > left.m_Id) return true;
		else return false;
	}
	bool operator==(const Book&book) {
		if (this->m_Id == book.m_Id) return true;
		else return false;
	}
	bool operator<=(const Book&book) {
		if (this->m_Id <= book.m_Id) return true;
		else return false;
	}
};