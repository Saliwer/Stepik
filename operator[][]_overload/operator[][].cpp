#include <iostream>

using namespace std;

class class1 {
public:
	class1() 
	{
		mas = new int*[10];
		for (int i = 0; i < 10; ++i) 
			mas[i] = new int[10];

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				mas[i][j] = i+j;
				cout << mas[i][j] << ' ';
			}
			cout << endl;
		}
	}
	~class1() 
	{
		for (int i = 0; i < 10; ++i)
			delete[] mas[i];
		delete[] mas;
	}
private:
		class class2 
		{
		public:
			class2(int *arr) : arr(arr) {}

			int operator[](int index) 
			{
				return arr[index];
			}

		private:
			int *arr;
		};

public:
	class2 operator[](int index) {
		return class2(mas[index]);	
	}
	

private:
	int**mas;
};

int main() {
	class1 a;

	//a[x] returns value class2's type then clas2::operator[] is invoked
	cout << "a[1][3] = " << a[1][3];		

	return 0;
}