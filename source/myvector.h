#pragma once

template<typename T>
class myVector {
private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;

public:
	myVector() : m_data(nullptr), m_size(NULL), m_capacity(NULL) {}

	explicit myVector(size_t size) : m_data(new T[size]), m_size(size), m_capacity(size) {}

	myVector(const myVector& other) : m_data(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
		for (size_t i = 0; i < m_size; ++i) {
			m_data[i] = other.m_data[i];
		}
	}

	T& operator[](size_t index) {
		return m_data[index];
	}

	const T& operator[](size_t index) const {
		return m_data[index];
	}

	myVector<T>& operator=(const myVector<T>& other) {
		if (this != &other) {
			delete[] m_data;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = new T[m_capacity];
			for (size_t i = 0; i < m_size; ++i) {
				m_data[i] = other.m_data[i];
			}
		}
		return *this;
	}


	void reserve(size_t new_capacity) {
		if (new_capacity <= m_capacity) {
			return;
		}

		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < m_size; ++i) {
			new_data[i] = m_data[i];
		}

		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}

	void resize(size_t new_size) {
		if (new_size > m_capacity) {
			reserve(new_size);
		}
		for (size_t i = m_size; i < new_size; ++i) {
			m_data[i] = T();
		}
		m_size = new_size;
	}

	size_t size() const {
		return m_size;
	}

	bool isEmpty() const {
		return m_size == 0;
	}

	void push_back(const T& value) {
		if (m_size == m_capacity) {
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);
		}
		m_data[m_size] = value;
		m_size++;
	}

	void pop_back() {
		if (m_size > 0) {
			m_size--;
		}
	}

	~myVector() {
		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
	}
};