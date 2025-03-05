#pragma once
#include <iostream>
#include <cstring>
#include "../consts.h"

class MyString {
private:
    char* data_;
    size_t size_;

public:
    MyString() noexcept : data_(nullptr), size_(0) {}

    MyString(const char* str) : data_(nullptr), size_(0) {
        if (str) {
            size_ = strlen(str);
            data_ = new char[size_ + 1];
            strcpy(data_, str);
        }
    }

    MyString(const MyString& other) : data_(nullptr), size_(0) {
        if (other.data_) {
            size_ = other.size_;
            data_ = new char[size_ + 1];
            strcpy(data_, other.data_);
        }
    }

    MyString(MyString&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;

            if (other.data_) {
                size_ = other.size_;
                data_ = new char[size_ + 1];
                strcpy(data_, other.data_);
            }
        }
        return *this;
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    MyString& operator=(const char* str) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;

        if (str) {
            size_ = strlen(str);
            data_ = new char[size_ + 1];
            strcpy(data_, str);
        }
        return *this;
    }

    bool operator==(const char* str) const {
        if (data_ == nullptr && str == nullptr) return true;
        if (data_ == nullptr || str == nullptr) return false;
        return strcmp(data_, str) == 0;
    }

    bool operator==(const MyString& other) const {
        if (data_ == nullptr && other.data_ == nullptr) return true;
        if (data_ == nullptr || other.data_ == nullptr) return false;
        return strcmp(data_, other.data_) == 0;
    }

    MyString& operator+=(char c) {
        char* new_data = new char[size_ + 2];
        if (data_) {
            memcpy(new_data, data_, size_);
        }
        new_data[size_] = c;
        new_data[size_ + 1] = '\0';
        delete[] data_;
        data_ = new_data;
        size_ += 1;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        if (str.data_) {
            os << str.data_;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, MyString& str) {
        char buffer[Constants::kStringBuffer];
        is >> buffer;
        str = MyString(buffer);
        return is;
    }

    bool IsEmpty() const noexcept {
        return size_ == 0 || data_ == nullptr || data_[0] == '\0';
    }

    size_t Length() const noexcept {
        return size_;
    }

    const char* CStr() const noexcept {
        return data_ ? data_ : "";
    }

    size_t Hash() const {
        size_t result = 0;
        if (data_) {
            for (size_t i = 0; i < size_; i++) {
                result += data_[i];
                result *= Constants::kLargePrimeNumber;
            }
        }
        result %= Constants::kHashTableSize;
        return result;
    }

    ~MyString() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
    }
};
