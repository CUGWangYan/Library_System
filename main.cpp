#include <iostream>
#include "Library.h"
using namespace std;
int main() {
	Library lib;
	int f = 1;
	while (f != 0) {

		cout << "--------图书管理系统--------" << endl;
		cout << "         1.采编入库" << endl;
		cout << "         2.清除书库库存" << endl;
		cout << "         3.图书借阅" << endl;
		cout << "         4.图书归还" << endl;
		cout << "         5.显示所有图书" << endl;
		cout << "         6.查阅图书" << endl;
		cout << "         0.退出   " << endl;
		cout << "----------------------------" << endl;
		cin >> f;
		switch (f) {
		case 1: lib.Book_Entry(); break;
		case 2: lib.Book_Delete(); break;
		case 3: lib.lend(); break;
		case 4: lib.returnbook(); break;
		case 5: lib.OutPut(); break;
		case 6: lib.kucun();break;
		case 0:cout << "EXIT" << endl; break;
		}
	}
	int a;
	cin >> a;
	return 0;
}