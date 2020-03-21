#include <iostream>
#include <cstddef>

template<typename T>
class Array {
private:
	size_t m_size;
	T* m_data;

public:
	explicit Array(size_t size = 0, const T& value = T(0)) {
		m_size = size;
		m_data = static_cast<T*>(operator new[] (m_size * sizeof(T)));
		for (size_t i = 0; i < m_size; ++i)
			new (m_data + i) T(value);
		
	}

	Array(const Array& other) {
		m_size = other.m_size;
		m_data = static_cast<T*>(operator new[] (m_size * sizeof(T)));
		for (size_t i = 0; i < m_size; ++i)
			new (m_data + i) T(other.m_data[i]);
	}

	~Array() {
		for (size_t i = 0; i < m_size; ++i)
			m_data[i].~T();
		operator delete[] (m_data);
	}

	Array& operator=(const Array& other) {
		if (this == &other)
			return *this;
		this->~Array();
		this->m_size = other.m_size;
		m_data = static_cast<T*>(operator new[] (m_size * sizeof(T)));
		for (size_t i = 0; i < this->m_size; ++i)
			new (m_data + i) T(other.m_data[i]);
		return *this;
	}

	size_t size() const {
		return m_size;
	}

	T& operator[](size_t index) {
		return m_data[index];
	}

	const T& operator[](size_t index) const {
		return m_data[index];
	}

};


int main() {

	Array<double> temp_value(5, 5.5);
	Array<double> b(2, 2.4);
	Array<double> c(3, 4.8);
	b = temp_value;
	temp_value = b;
	temp_value = c;

	return 0;
}