#include"Bank System.h"
int main() {
	BankingApplication run;
}

//// FCAI – Programming 1 – 2022
//// Author: Sama Ahmed
//#include"iostream"
//#include<string>
////#include"C:\\Users\\admin\\source\\repos\\code\\code\\login.cpp"
//
////implicit convergent : what the compiler is allowed
////to do is perform one implicit conversion
//
//class Entity {
//	std::string name;
//	int age;
//public:
//	explicit Entity(const std::string& n):name(n),age(-1){}
//	explicit Entity(int m):age(m),name("unkown") {}
//};
//void printEntity(const Entity& entity) {}


/*
you can write explicit before the constructor when you want
your constructor to be explicity called insted of allowing thec++
compiler to implicitly convert any integer into entity by basically
calling this constructor every time
*/

//	printEntity(22);//it calls the constructor
/*
the compiler will convert from  int to Entity remeber
that the copiler is allowed to do just one conversion
so if i printEntity("sama") will get an error as the
compiler will do two conversion and it's not allowed BUT
I CAN  printEntity(std::string("sama"))=printEntity(Entity("sa"))
*/

//namespace app {
//	void print(const char* c) {
//		cout<< c<<"app";
//	}
//}
//
//namespace ap {
//	namespace func {
//		void print(const char* c) {
//			cout << c << "ap";
//		}
//	}
//}
//
//int main() {
////using app::print;  mean in every time print is just written 
////it will know it's from app namespace
//	namespace a = app;
//	a::print("app");//it will be insted of writing app::
//	ap::func::print("dlkwa");
//	namespace c = ap::func ;
//	c::print("dfd");
//Entity va("sama");//Entity a = "sa";
//	Entity k = (Entity)77;
//  //  char a[100];
////	cin.getline(a);
//}
//template<>


//struct User {
//std::string name;
//
//	User(string name) {
//		name = name;
//	}
//	void show() {
//		std::cout << name;
//	}
//};
//struct User {
//	string name;
//	User() = default;
//	User(string name) : name(name) {
//	}
//};
//int main() {
//	//User u("Michael");
//	const char* name = "Michael";
//	User u(name);

	/*User u("sa");
	u.show();*/
//#include<fstream>
//#include<string>
//
//
//void load(const char* filename, double matr[][10], int& row, int& col) {
//	fstream file;
//	file.open(filename,ios::in);
//	if (!file.is_open()) {
//		cout << "file is not exist";
//	}
//	else {
//		file >> row;
//		file >> col;
//		for (int i = 0; i < row; i++) {
//			for (int j = 0; j < col; j++) {
//
//				file >> matr[i][j];
//			}
//		}
//	}
//}
//int main() {
//	double arr[10][10];
//	const char* name = "data.txt";
//	int row, col;
//	load(name, arr, row, col);
//	
//}
//struct Float {
//	int integer,fraction;
//	Float(int n = 0, int fr = 0) : integer{ n }, fraction{ abs(fr) } {}
//};
//
//istream& operator>>(istream& my_stream, Float& f) {
//	char dummy_char;
//	my_stream >> f.integer >> dummy_char >> f.fraction;
//	return my_stream;
//}
//#include<algorithm>
//#include<cstdlib>
//#include<sstream>
//#include<iomanip>
//#include<fstream>
//bool copy1(char* source, char* target) {
//	ifstream inFile(source);
//	ofstream outFile(target);
//	if (!inFile or !outFile)
//		return false;
//	while (!inFile.eof())
//		outFile.put(inFile.get());
//	return true;
//}
//#include<array>
//template<typename T, int size>
//array<T, size> fill_zeros(array<T, size>& cpp)
//{
//	for (T& element : cpp)
//	{
//		element = 0;
//	}
//
//	return cpp;
//}
//struct student {
//	int n;
//	string name;
//};
//struct special {
//	string id;
//	student stu;
//};
//union dog {
//	int y;
//	int v;
//};
//#include<string>
//struct s {
//	int c;
//	char g;
//	s(int b);
//	void cal();
//};
//s::s(int b) {
//	c = b;
//}
//void s::cal() {
//	if (c != 0) {
//		g = 'm';
//		cout << g;
//	}
//}
//#include <iostream>
//using namespace std;
//namespace FCAI1 {
//	void greeting();
//}
//namespace FCAI2 {
//	void greeting();
//}
//void bigGreeting();
//
//#include"declar.h"
//int addnum(int num1, int num2) {
//	int sum = num1 + num2;
//	std::cout << "jk";
//	return sum;
////}
//#include <iostream>
//#include <iomanip>
//#include <vector>
//#include<fstream>

using namespace std;
//int main() {
//	fstream datafile;
//	datafile.open("saa.txt");
//}

//#define forevery(item) for (int item
//#define in(data) : data) {
//#define print(item, x) cout << item << " "
//#define endfor }
//#define println cout<<endl
//#define square1(x) (x*x)
//#define square2(x) ((x)*(x))


//int main2()
//{

	//vector<int> data = { 1,2,4,5,5,6 };
	//cout << 64 / square1(4) << endl; // Expected 4 got 64
	//cout << 64 / square2(2 + 2) << endl; // Expected 4 got 38
	// This code uses macros and when expanded, it becomes normal C++
	/*forevery(item)in(data)
		item *= 2;
	print(item, " ");
	endfor*/
	//println;


	//return 0;
//}
//int* get_ptr(&x){
//	return x;
//}




//int main() {
//struct u{
//public:
//	union {
//		float a; 
//		int b;
//	};
//};
//	u c;
//	c.b = 97;
//	cout << c.b<<"    "<<c.a;
//	float x = 3455.4415;
//	cout << "\n" << x;
	//vector<int>v{ 2,4,5,7 };
	//for_each(v.begin(), v.end(), [](int i) {cout << " " << i;});
//}



//reverse double

//#include<iostream>
//#include<cmath>
//using namespace std;
//#include<vector>
//void reverse(int& k, double arr[])
//{
//	for (int i = 0; i < k; i++) {
//		swap(arr[i], arr[k - 1]);
//			k--;
//	}
//}
//int main()
//{
//	double list[]{ 2.3, 5.6, 6.6, 7.8 };
//	int n = 4;
//	reverse(n, list);
//	cout << list[0];
//}

