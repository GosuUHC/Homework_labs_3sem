#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
using namespace std;

struct datetime {
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;

	void Info(datetime*, int);
	void GetNextDate(datetime*, datetime*, int);
	void GetPrevDate(datetime*, datetime*, int);
	
};
struct timedelta {
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
};


int is_leap_year(int year) 
{
	if ((year % 4) == 0 && (year % 4000) != 0 &&
		((year % 100) != 0 || (year % 400) == 0))
		return 1;
	else  return 0;
}
void datetime::Info(datetime* arr, int x)
{
	cout << endl;
    cout << arr[x].second << "sec " << arr[x].minute << "min " << arr[x].hour << "h " 
	     << arr[x].day << " " << arr[x].month << " " << arr[x].year<<" ";
    cout << endl;
	
}

void datetime::GetPrevDate(datetime* arr,datetime* arr1, int n)
{
	int d = arr[n].day;
	int d1 = d - 1;
	int m = arr[n].month;
	int m1 = m;
	int y = arr[n].year;
	int y1 = y;
	if (d1 == 0) {
		m1--;

		if (m1 == 2) {
			if (is_leap_year(y)) d1 = 29;

			else               d1 = 28;
		}
		else if (m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11) d1 = 30;

		else d1 = 31;

		if (m1 == 0) {
			m1 = 12;
			y1--;
		}
	}
	arr1[n].second = arr[n].second;
	arr1[n].minute = arr[n].minute;
	arr1[n].hour = arr[n].hour;
	arr1[n].day = d1;
	arr1[n].month = m1;
	arr1[n].year = y1;
	datetime::Info(arr1, n);
}
void datetime::GetNextDate(datetime* arr, datetime* arr1, int n)
{
	int d = arr[n].day;
	int d1 = d;
	int m = arr[n].month;
	int m1 = m;
	int y = arr[n].year;
	int y1 = y;

	int maxd[12]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (is_leap_year(y)) maxd[1] = 29;

	int i;

	for (i = 0; i < 12;i++)
		if (i + 1 == m1 && d1 == maxd[i]) {
			d1 = 1;
			m1++;
			break;
		}
	if (i == 12) d1++;

	if (m1 == 13) {
		m1 = 1;
		y1++;
	}
	
	arr1[n].second=arr[n].second;
	arr1[n].minute = arr[n].minute;
	arr1[n].hour = arr[n].hour;
	arr1[n].day = d1;
	arr1[n].month = m1;
	arr1[n].year = y1;
	datetime::Info(arr1, n);


}

int GetNumber()
{
	int x = 0;
	ifstream f("file.txt");
	string da;
	while (getline(f, da)) {
		x++;
	}
	return x;
}
void GetArr(datetime* arr, int x)
{
	ifstream f("file.txt");
	string da;
	int i = 0;
	while (getline(f, da)) {
		istringstream da1(da);
		da1 >> arr[i].second >> arr[i].minute >> arr[i].hour >> arr[i].day >> arr[i].month >> arr[i].year;
		i++;
	}

}
void outALL(datetime* arr, datetime* arr1, int n)
{
	for (int i = 0;i < n;i++) {


		cout << endl << "Number " << i + 1 << endl;
		cout << "current: ";

		arr->Info(arr, i);

		cout << "next: ";

		arr->GetNextDate(arr, arr1, i);

		cout << "prev: ";

		arr->GetPrevDate(arr, arr1, i);
	}
}
void outSingle(datetime* arr, datetime* arr1, int n, int i)
{

		cout << endl << "Number " << i + 1 << endl;
		cout << "current: ";

		arr->Info(arr, i);

		cout << "next: ";

		arr->GetNextDate(arr, arr1, i);


	

}
void out(datetime a)
{
	cout << endl;
	cout << a.day << "d." << a.month << "m." << a.year << endl;
	cout << a.hour << "h:" << a.minute << "min:" << a.second << endl;

}
void out2(timedelta a)
{
	cout << endl;
	cout << a.day << "d." << a.month << "m." << a.year << endl;
	cout << a.hour << "h:" << a.minute << "min:" << a.second << endl;

}
void fun1(datetime a, datetime b, timedelta& c)
{
	c.second = a.second - b.second;
	c.minute = a.minute - b.minute;
	c.hour = a.hour - b.hour;
	c.day = a.day - b.day;
	c.month = a.month - b.month;
	c.year = a.year - b.year;

	out2(c);
}
void fun2(datetime a, datetime& b, timedelta c)
{
	
	if (c.year<=0) {
		cout << "plus" << endl;
		b.second = a.second + c.second;
		b.minute = a.minute + c.minute;
		b.hour = a.hour + c.hour;
		b.day = a.day + c.day;
		b.month = a.month + c.month;
		b.year = a.year + c.year;

		out(b);
	}

	else if (c.year>0) {
		cout << "minus" << endl;
		b.second = a.second - c.second;
		b.minute = a.minute - c.minute;
		b.hour = a.hour - c.hour;
		b.day = a.day - c.day;
		b.month = a.month - c.month;
		b.year = a.year - c.year;

		out(b);
	}

	else 
		 cout << "Something went wrong! Try again" << endl;
}
void fun3(timedelta a, timedelta b, timedelta& c)//прототип
{
	int x;
	cout << "What do you want?\n1 - plus\n2 - minus\n";cin >> x;

	if (x == 1) {

		cout << "Plus" << endl;

		c.second = a.second + b.second;
		c.minute = a.minute + b.minute;
		c.hour = a.hour + b.hour;
		c.day = a.day + b.day;
		c.month = a.month + b.month;
		c.year = a.year + b.year;

	}

	else if (x == 2) {

		cout << "Minus" << endl;

		c.second = a.second - b.second;
		c.minute = a.minute - b.minute;
		c.hour = a.hour - b.hour;
		c.day = a.day - b.day;
		c.month = a.month - b.month;
		c.year = a.year - b.year;
	}

	else
		cout << "Something went wrong! Try again!" << endl;
}
datetime Normalno(datetime& a)
{
	const time_t tm = time(NULL);

	struct tm* T = localtime(&tm);
	a.year = T->tm_year + 1900;
	a.month = T->tm_mon + 1;
	a.day = T->tm_mday;
	a.hour = T->tm_hour;
	a.minute = T->tm_min;
	a.second = T->tm_sec;
	return a;
}
void copy(datetime* arr, datetime& buff, int i)
{
	buff.second = arr[i].second;
	buff.minute = arr[i].minute;
	buff.hour = arr[i].hour;
	buff.day = arr[i].day;
	buff.month = arr[i].month;
	buff.year = arr[i].year;
}
void CheckYear(datetime* arr1, datetime* arr, int n) //var 4. ver 1
{
	cout <<endl<< "4 var task" << endl;

	for (int i = 0;i < n;i++) {
		if (arr[i].month != 12 && arr[i].day != 31) {

			outSingle(arr, arr1, n, i);

		}
		else {
			cout <<endl<< "31 of December. Print is prohibited!" << endl;

		}
	}
}
bool CheckData(datetime* arr, int n)
{
	for (int i = 0;i < n;i++) {
		if (arr[i].second > 60 || arr[i].second < 0
			|| arr[i].minute>60 || arr[i].minute < 0
			|| arr[i].hour>23 || arr[i].hour < 0
			|| arr[i].day>31 || arr[i].day < 0
			|| arr[i].month>12 || arr[i].year < 0) {
			cout << "ENTERED WRONG DATA. TRY ELSE!" << endl;
			return false;
		}
	}
	return true;
}
int main()
{
	int n;
	n=GetNumber();
	datetime* arr = new datetime[n];
	datetime* arr1 = new datetime[n];
	GetArr(arr, n);
	if (CheckData(arr, n)) {
		datetime a = Normalno(a);
		datetime b;
		timedelta c;
		copy(arr, b, 1);
		out(a);
		out(b);
		//outALL(arr, arr1, n);
		//CheckYear(arr1, arr, n);
		fun1(b, a, c);
		fun2(a, b, c);
	}
	else cout << "GG WP" << endl;
	return 0;
}
