#pragma once
class Date {
	int m_year;
	int m_month;
	int m_day;
public:
	~Date() {}
	Date(int year, int month, int day) :m_year(year), m_month(month), m_day(day) {}
	Date(const Date&) = default;
};