#pragma once
#include "MyVector.h"
#include "Book.h"
#include "BTree.h"
#include <fstream>
#include <assert.h>
class Library {
	MyVector<Book> library;
	BTree<Book> btree;
public:
	Library() {} 
	Library(const Library&) = delete;
	~Library() {}
	void Book_Entry(){
		Book newbook;
		cout << "Load files or manually Input" << endl;
		bool flag;
		cin >> flag;
		if (flag == true) {
			ifstream infile;
			infile.open("1.txt");
			assert(infile.is_open());
			int i = library.getsize();
			while (!infile.eof()) {
				infile >> newbook;
				library.push_back(newbook);
				btree.BTree_insert(newbook, i);
				i++;
			}
			infile.close();
			cout << "Added successfully" << endl;
			library.show();
			return;
		}
		else cin >> newbook;
		int m = btree.contain(newbook);
		if (m == -1) {
			library.push_back(newbook);
			int a = library.getsize();
			btree.BTree_insert(newbook,a);
			cout << "Added successfully" << endl;
		}
		else {
			library[m].bookentry();
			cout << "There is already in the storehouse. The amount of stock is increased by one. " << endl;
		}
	}
	bool Book_Delete() {
			cout << "Please inout the ID of book" << endl;
			string bookname;
			cin >> bookname;
			Book oldbook(bookname);
			int m = btree.contain(oldbook);
			if (m == -1) {  cout << "There is no book in the warehouse" << endl;return false; }
			else {
				cout << library[m] <<"Delete Success" <<endl;
				library.erase(m);
				btree.BTree_delete(oldbook);
				return true;
			}
		}
	void lend() {
		cout << "Please inout the ID of book" << endl;
		string bookname;
		cin >> bookname;
		Book book(bookname);
		int m = btree.contain(book);
		if (m==-1) cout << "There is no book in the warehouse" << endl;
		else {
			library[m].lend();
			cout <<library[m]<< "Borrow Success" << endl;
			}
		}
	void returnbook() {
		cout << "Please inout the ID of book" << endl;
		string bookname;
		cin >> bookname;
		Book book(bookname);
		int m = btree.contain(book);
		if (m==-1)cout << "There is no book in the warehouse" << endl;
		else {
			library[m].returnbook();
			cout << library[m] << "Return Success" << endl;
		}
	}
	void kucun() {
		cout << "Please inout the ID of book" << endl;
		string bookname;
		cin >> bookname;
		Book book(bookname);
		int m = btree.contain(book);
		if ( m == -1) cout << "There is no book in the warehouse" << endl;
		else {
			cout << library[m] << endl;
		}
	}
	void OutPut() {
		for (unsigned int i = 0; i < library.getsize(); i++) {
			cout << library[i] << endl;
		}
	}
};