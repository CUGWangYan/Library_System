#pragma once
#include <string>
#include "Date.h"
using namespace std;
class Person {
	string m_Id;
	string m_Name;
	Date m_Date;
public:
	~Person() {}
	Person(const Person&per) = delete;
	Person(string id, string name, Date date) :m_Id(id), m_Name(name), m_Date(date) {}
	string getId() {
		return this->m_Id;
	}
	string getName() {
		return this->m_Name;
	}
	Date getDate() {
		return this->m_Date;
	}
};