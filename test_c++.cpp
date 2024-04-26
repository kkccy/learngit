#include <iostream>
#include <iomanip>
#include <string.h>
#include <math.h>
using namespace std;

class Student {
public:
	string name;
	int year;
	int month;
	int day;

	Student() {};
	Student(string n, int y, int m, int d) :name(n), year(y), month(m), day(d) {
	}
	friend int compare(Student &s1,Student &s2);
};

int isLeap(int y) {
	if ((y % 4 == 0 && y % 100) || y % 400 == 0) {
		return 1;
	}
	return  0;
}

int operator-(Student& s1, Student& s2) {
	int result = 0;
	int tmp;
	int begin_sum = 0, end_sum = 0;


	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


	for (int j = s1.year; j < s2.year; j++) {
		if (isLeap(j) == 1) {
			result += 366;
		}
		else {
			result += 365;
		}
	}
	
	

	if (s2.month == 1) {
		result += s2.day;
	}
	else
	{
		for (int i = 1; i < s2.month; i++) {
			if (isLeap(s2.year)) {
				m[1] = 29;
			}
			result += m[i - 1];
		}
		result += s2.day;
	}
	m[1] = 28;


	for (int k = 0; k < s1.month - 1; k++) {
		if (isLeap(s1.year)) {
			m[1] = 29;
		}
		end_sum += m[k];
	}
	end_sum += s1.day;

	result -= end_sum;

	return result;
}

int compare(Student &s1,Student &s2){
	if(s1.year==s2.year){
		if(s1.month == s2.month){
			if(s1.day > s2.day){
				return 0;
			}else{
				return 1;
			}
		}else if(s1.month>s2.month){
			return 0;
		}else{
			return 1;
		}
	}else if(s1.year>s2.year){
		return 0;
	}else{
		return 1;
	}
}

int main()
{
	int t, min = 10000;
	string name, min_n1, min_n2;
	int year;
	int month;
	int day;
	cin >> t;
	Student* stu = new Student[t];
	for (int i = 0; i < t; i++) {
		cin >> stu[i].name >> stu[i].year >> stu[i].month >> stu[i].day;
	}
	min_n1 = stu[0].name;
	min_n2 = stu[0].name;
	for (int i = 0; i < t - 1; i++) {
		for (int j = i + 1; j < t; j++) {
			if(compare(stu[i],stu[j])==1){
				if (abs(stu[i] - stu[j]) < min) {
					min = abs(stu[i] - stu[j]);
					min_n1 = stu[i].name;
					min_n2 = stu[j].name;
				}
			}else{
				if (abs(stu[j] - stu[i]) < min) {
					min = abs(stu[j] - stu[i]);
					min_n1 = stu[i].name;
					min_n2 = stu[j].name;
				}
			}
			
		}
	}
	cout << min_n1 << "和" << min_n2 << "年龄相差最小，为" << min << "天。" << endl;

	return 0;
}
