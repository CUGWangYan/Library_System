#pragma once
#include "MyVector.h"
#include "Book.h"
#include "BTree.h"
#include <fstream>
#include <assert.h>
class Library {
	MyVector<Book> library;
	MyVector<Person> Student;
	BTree<Book> btree;
public:
	Library();
	Library(const Library&) = delete;
	~Library() {}
	void Book_Entry();
	bool Book_Delete();
	void lend();
	void returnbook();
	void kucun();
	void OutPut();
};
