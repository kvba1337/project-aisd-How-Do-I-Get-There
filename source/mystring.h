#pragma once
#include <iostream>
#include <cstring>
#include "consts.h"

class myString {
private:
	char* data;
	size_t size;

public:
	myString() : data(nullptr), size(0) {}

	myString(const char* str) : data(nullptr), size(0) {
		size = strlen(str);
		data = new char[size + 1];
		strcpy(data, str);
	}

	myString(const myString& other) : data(nullptr), size(0) {
		size = other.size;
		data = new char[size + 1];
		strcpy(data, other.data);
	}

	myString& operator=(const myString& other) {
		if (this != &other) {
			delete[] data;
			size = other.size;
			data = new char[size + 1];
			strcpy(data, other.data);
		}
		return *this;
	}

	bool operator==(const char* str) const {
		return strcmp(data, str) == 0;
	}

	myString& operator+=(char c) {
		char* new_data = new char[size + 2];
		memcpy(new_data, data, size);
		new_data[size] = c;
		new_data[size + 1] = '\0';
		delete[] data;
		data = new_data;
		size += 1;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const myString& str) {
		return os << str.data;
	}

	friend std::istream& operator>>(std::istream& is, myString& str) {
		char buffer[STRING_BUFFER];
		is >> buffer;
		str = myString(buffer);
		return is;
	}

	bool isEmpty() const {
		return size == 0 || data[0] == '\0';
	}

	size_t hash() const {
		size_t result = 0;
		for (size_t i = 0; i < size; i++) {
			result += data[i];
			result *= LARGE_PRIME_NUMBER;
		}
		result %= HASH_TABLE_SIZE;

		return result;
	}

	~myString() {
		delete[] data;
		data = nullptr;
		size = 0;
	}
};