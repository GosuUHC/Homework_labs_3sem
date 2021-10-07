#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
using namespace std;

enum {s2, m2, h2, d2, mon2, y2};

class datetime {  

private:

	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
public:
	datetime(int s, int min, int h, int d, int mon, int y)
	{
		if (s >= 0 && s < 60)
		
			second = s;
		
		else  second = 0;

		if (min >= 0 && min < 60)

			minute = min;

		else minute = 0;

		if (h >= 0 && h < 24)

			hour = h;

		else hour = 0;
		if (d > 0 && d < 32)

			day = d;

		else day = 1;
		if (mon > 0 && mon < 13)

			month = mon;

		else month = 1;

		year = y;
	}

	int Get(int index)
	{
		switch (index) {
		case 0: return second;
		case 1: return minute;
		case 2: return hour;
		case 3: return day;
		case 4: return month;
		case 5: return year;
		}

	}
	int is_leap_year(int);
	
	void CheckYear(datetime*, datetime*, int); //var 4. ver 1
	void GetNextDate(datetime*, datetime*, int);
	void GetPrevDate(datetime*, datetime*, int);
	datetime Normalno(datetime&);
	datetime() {};

	~datetime() {};

};
class timedelta {
private:
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
public:
	timedelta(int s, int m, int h, int d, int mon, int y)
	{
		second = s;
		minute = m;
		hour = h;
		day = d;
		month = mon;
		year = y;
	}
	void In_Tmdlt(timedelta&);
	void fun1(datetime, datetime, timedelta&);
	void fun2(datetime, datetime&, timedelta);
	void fun3(timedelta, timedelta, timedelta&);
	timedelta() {};
	~timedelta() {};

};
class show {     // for datetime
public:
	void Info(datetime*, int);
	void outALL(datetime*, datetime*, int);
	void outSingle_ForVariant_4(datetime*, datetime*, int, int);
	void out_noArray(datetime);
};
class show_2 {   // for timedelta
public:
	void out2(timedelta);

};

int datetime::is_leap_year(int year) 
{
	if ((year % 4) == 0 && (year % 4000) != 0 &&
		((year % 100) != 0 || (year % 400) == 0))
		return 1;
	else  return 0;
}
void show::Info(datetime* arr, int x)
{
	cout << endl;
    cout << arr[x].Get(s2) << "sec " << arr[x].Get(m2) << "min " << arr[x].Get(h2) << "h " 
	     << arr[x].Get(d2) << " " << arr[x].Get(mon2) << " " << arr[x].Get(y2)<<" ";
    cout << endl;
	
}

void datetime::GetPrevDate(datetime* arr, datetime* arr1, int n)
{
	datetime dt;
	int d = arr[n].Get(d2);
	int d1 = d - 1;
	int m = arr[n].Get(mon2);
	int m1 = m;
	int y = arr[n].Get(y2);
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
	show a;
	a.Info(arr1, n);
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
	show a;
	a.Info(arr1, n);
}

void show::outALL(datetime* arr, datetime* arr1, int n)
{
	show a;
	for (int i = 0;i < n;i++) {


		cout << endl << "Number " << i + 1 << endl;
		cout << "current: ";

		a.Info(arr, i);

		cout << "next: ";

		arr->GetNextDate(arr, arr1, i);

		cout << "prev: ";

		arr->GetPrevDate(arr, arr1, i);
	}
}
void show::outSingle_ForVariant_4(datetime* arr, datetime* arr1, int n, int i)
{
	show a;

		cout << endl << "Number " << i + 1 << endl;
		cout << "current: ";

		a.Info(arr, i);

		cout << "next: ";

		arr->GetNextDate(arr, arr1, i);

}
void show::out_noArray(datetime a)
{
	cout << endl;
	cout << a.Get(d2) << "d." << a.Get(mon2) << "m." << a.Get(y2) << endl;
	cout << a.Get(h2) << "h:" << a.Get(m2) << "min:" << a.Get(s2) << endl;

}
/*void show_2::out2(timedelta a)
{
	cout << endl;
	cout << a.day << "d." << a.month << "m." << a.year << endl;
	cout << a.hour << "h:" << a.minute << "min:" << a.second << endl;

}*/
/*timedelta timedelta::fun1(datetime a, datetime b)
{
	datetime a_1, b_1;

	c.second = a.second - b.second;
	c.minute = a.minute - b.minute;
	c.hour = a.hour - b.hour;
	c.day = a.day - b.day;
	c.month = a.month - b.month;
	c.year = a.year - b.year;
	show_2 z;
	z.out2(c);
	return c;
}
void timedelta::fun2(datetime a, datetime& b, timedelta c)
{
	show z;
	if (c.year<=0) {
		cout << "plus" << endl;
		b.second = a.second + c.second;
		b.minute = a.minute + c.minute;
		b.hour = a.hour + c.hour;
		b.day = a.day + c.day;
		b.month = a.month + c.month;
		b.year = a.year + c.year;

		z.out_noArray(b);
	}

	else if (c.year>0) {
		cout << "minus" << endl;
		b.second = a.second - c.second;
		b.minute = a.minute - c.minute;
		b.hour = a.hour - c.hour;
		b.day = a.day - c.day;
		b.month = a.month - c.month;
		b.year = a.year - c.year;

		z.out_noArray(b);
	}

	else 
		 cout << "Something went wrong! Try again" << endl;
}
void timedelta::fun3(timedelta a, timedelta b, timedelta& c)//прототип
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
		
		
		show_2 z;
		z.out2(c);

	}

	else if (x == 2) {

		cout << "Minus" << endl;

		c.second = a.second - b.second;
		c.minute = a.minute - b.minute;
		c.hour = a.hour - b.hour;
		c.day = a.day - b.day;
		c.month = a.month - b.month;
		c.year = a.year - b.year;

		show_2 z;
		z.out2(c);
	}

	else
		cout << "Something went wrong! Try again!" << endl;
}*/
datetime datetime::Normalno(datetime& a)
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

void datetime::CheckYear(datetime* arr1, datetime* arr, int n) //var 4. ver 1
{
	show z;
	cout <<endl<< "4 var task" << endl;

	for (int i = 0;i < n;i++) {
		if (arr[i].month != 12 && arr[i].day != 31) {

			z.outSingle_ForVariant_4(arr, arr1, n, i);

		}
		else {
			cout <<endl<< "31 of December. Print is prohibited!" << endl;

		}
	}
}

/*void timedelta::In_Tmdlt(timedelta& a)
{
	cout << "Enter timedelta data\n";
	cout << " Sec:";cin >> a.second;
	cout << " Min:";cin >> a.minute;
	cout << " Hour:";cin >> a.hour;
	cout << " Day:";cin >> a.day;
	cout << " Mon:";cin >> a.month;
	cout << " Year:";cin >> a.year;

}*/

class Application {
public:
	void runmain();
	void runmain_tmdlt();
	datetime Enter()
	{
		int s, m, h, d, mon, y;
		cout << "sec=";cin >> s;
		cout << "min=";cin >> m;
		cout << "hour=";cin >> h;
		cout << "day=";cin >> d;
		cout << "month=";cin >> mon;
		cout << "year=";cin >> y;
		datetime a = datetime(s, m, h, d, mon, y);
		return a;
	}
	datetime* GetArr(int& n)
	{
		int s, m, h, d, mon, y;
		ifstream f("file.txt");
		string da;
		while (getline(f, da)) {
			n++;
		}
		
		datetime* arr = new datetime[n];
		
		int i = 0;
		
		f.clear();
		f.seekg(0, ios::beg);
		while (getline(f, da)) {
			istringstream da1(da);

			da1 >> s >> m >> h >> d >> mon >> y;
			arr[i] = datetime(s, m, h, d, mon, y);
			i++;
		}
		f.close();
		return arr;

	}
};
void Application::runmain()
{
	datetime z;
	show z1;
	int n=0;
	datetime* arr=GetArr(n);
	datetime* arr1 = new datetime[n];
	
	z1.outALL(arr, arr1, n);
	z.CheckYear(arr1, arr, n);
		
	delete[] arr;
	delete[] arr1;

}
/*void Application::runmain_tmdlt()
{
	cout <<endl <<"Timedelta task" << endl;
	datetime a = a.Normalno(a);
	datetime b = Enter();
	timedelta c;
	show zzz;
	
	zzz.out_noArray(a);
	zzz.out_noArray(b);
	c.fun1(b, a, c);
	c.fun2(a, b, c);

	timedelta x, y, z;
	c.In_Tmdlt(x);c.In_Tmdlt(y);
	c.fun3(x, y, z);

}*/
int main()
{
	Application app;
	app.runmain();
	//app.runmain_tmdlt();
	return 0;
}
