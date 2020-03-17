#include <iostream>
#include <functional> //std::function
#include <typeinfo>
#include <memory>

/*Define a varibale square_fun storing an anonymous function 
which squared received value

Example:

int m[10] = {1,2,3,4,5,6,7,8,9,10};

for_each_int(m, m + 10, square_fun); // m = {1,4,9,16,25,36,49,64,81,100};
*/

template<typename T>
void for_each_int(int *p, int *q, T f) {
	for (; p != q; ++p)
		f(*p);
}


/*
2.
Define a variable gen_finder storing an anonymous function which receive 
array of int values via two pointers and returns anonymous function 
which receive an int value and checks is there the value in received array

Example:
int primes[5] = {2,3,5,7,11};

int m[10] = {0,0,1,1,4,6,7,8,9,10};

// first_prime will be pointed at 7
int * first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));

*/

template<class F>
int * find_if(int * p, int * q, F f)
{
	for (; p != q; ++p)
		if (f(*p))
			return p;
	return q;
}

int main() {
	//1.
	int m[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto square_fun = [](int &x) { x = x*x; };
	for_each_int(m, m + 10, square_fun);	// for_each_int(m, m + 10, [](int &x) {x *= x; });
	for (auto const &x : m)
		std::cout << x << " ";
	std::cout << '\n';


	//2.
	int primes[5] = { 2,3,5,7,11 };

	int m_2[10] = { 0,0,1,1,4,6,7,8,9,10 };

	auto gen_finder = [](int *x, int *y) 
	{ 
		return [x, y](int z) 
		{ 
		int *temp_ptr = x;		//bz  x already int * CONST * - const ptr
		for (; temp_ptr != y; ++temp_ptr) 
			if (*temp_ptr == z) 
				return true; 
			return false; 
		}; 
	};
	int *first_find = find_if(m_2, m_2 + 10, gen_finder(primes, primes + 5));

	std::cout << "*first_find=" << *first_find << '\n';



	return 0;
}