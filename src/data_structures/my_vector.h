#pragma once
#include <cstddef>
#include <utility>

template<typename T>
class MyVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:
    MyVector() noexcept : data_(nullptr), size_(0), capacity_(0) {}
    explicit MyVector(size_t size) : data_(size > 0 ? new T[size] : nullptr),
                                   size_(size),
                                   capacity_(size) {}

    MyVector(const MyVector& other) : data_(other.size_ > 0 ? new T[other.capacity_] : nullptr),
                                    size_(other.size_),
                                    capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    MyVector(MyVector&& other) noexcept : data_(other.data_),
                                        size_(other.size_),
                                        capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    MyVector<T>& operator=(const MyVector<T>& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = size_ > 0 ? new T[capacity_] : nullptr;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    MyVector<T>& operator=(MyVector<T>&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void Resize(size_t new_size) {
        if (new_size > capacity_) {
            Reserve(new_size);
        }
        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = T();
        }
        size_ = new_size;
    }

    size_t size() const noexcept {
        return size_;
    }

    size_t capacity() const noexcept {
        return capacity_;
    }

    bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    T* data() noexcept {
        return data_;
    }

    const T* data() const noexcept {
        return data_;
    }

    void PushBack(const T& value) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_] = value;
        size_++;
    }

    void PushBack(T&& value) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_] = std::move(value);
        size_++;
    }

    void PopBack() {
        if (size_ > 0) {
            size_--;
        }
    }

    ~MyVector() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
};
