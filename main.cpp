#include <iostream>
#include "Library.h"
using namespace std;
int main() {
	Library lib;
	int f = 1;
	while (f != 0) {

		cout << "--------ͼ�����ϵͳ--------" << endl;
		cout << "         1.�ɱ����" << endl;
		cout << "         2.��������" << endl;
		cout << "         3.ͼ�����" << endl;
		cout << "         4.ͼ��黹" << endl;
		cout << "         5.��ʾ����ͼ��" << endl;
		cout << "         6.����ͼ��" << endl;
		cout << "         0.�˳�   " << endl;
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