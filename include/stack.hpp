#pragma once

#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "utils.hpp"

namespace stack_ {
    template <typename data_t>
    class Stack {
            size_t size_;
            size_t capacity_;
            data_t *data_;

            bool ok() const;
            void augment();
            void diminish();

        public:
            Stack ();
            ~Stack();

            Stack (const Stack& s);
            Stack (Stack&& s);

            size_t size() const;
            size_t capacity() const;

            Stack<data_t>& operator=(const Stack& other);
            Stack<data_t>& operator=(Stack&& other);

            bool operator==(const Stack& other) const;
            bool operator==(Stack&& other) const;

            void push(const data_t& value);
            void push(data_t&& value);
            void pop();
            data_t& top();
    };

    template <typename data_t>
    void Stack<data_t>::augment() {
        VERIFY_CONTRACT(this->ok(), "Invalid stack");

        capacity_ *= 2;
        data_t *buffer = new data_t[capacity_];;
        VERIFY_CONTRACT(buffer != nullptr, "Unable to allocate memory");

        for (size_t i = 0; i < size_; i++) {
            buffer[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = buffer;
        buffer = nullptr;
    }

    template <typename data_t>
    void Stack<data_t>::diminish() {
        VERIFY_CONTRACT(this->ok(), "Invalid stack");

        capacity_ /= 2;
        data_t* buffer = new data_t[capacity_];;
        VERIFY_CONTRACT(buffer != nullptr, "Unable to allocate memory");

        for (size_t i = 0; i < size_; i++) {
            buffer[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = buffer;
        buffer = nullptr;
    }

    template <typename data_t>
    bool Stack<data_t>::ok() const {
        bool flag = (data_ != nullptr) && \
                    (size_ <= capacity_) && \
                    (capacity_ > 0);

        return flag;
    }

    template <typename data_t>
    Stack<data_t>::Stack() :
        size_(0),
        capacity_(2),
        data_(new data_t[capacity_])
    {
        VERIFY_CONTRACT(this->ok(), "Unable to perform constructor");
    }

    template <typename data_t>
    Stack<data_t>::Stack(const Stack<data_t>& other) :
        size_(other.size_),
        capacity_(other.capacity_)
    {
        VERIFY_CONTRACT(other.ok(), "Unable to perform copy semantic");

        data_ = new data_t[other.capacity_];
        VERIFY_CONTRACT(data_ != nullptr, "Unable to allocate memory");

        std::copy_n(other.data_, other.size_, data_);

        VERIFY_CONTRACT(this->ok(), "Unable to perform copy semantic");
    }

    template <typename data_t>
    Stack<data_t>::Stack(Stack<data_t>&& other) {
        VERIFY_CONTRACT(other.ok(), "Unable to perform move semantic");

        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        VERIFY_CONTRACT(this->ok(), "Unable to perform move semantic");
    }

    template <typename data_t>
    Stack<data_t>::~Stack () {
        if (data_ != nullptr) {
            delete[] data_;
        }
        size_ = 0;
        capacity_ = 0;
    }

    template <typename data_t>
    Stack<data_t>& Stack<data_t>::operator=(const Stack<data_t>& other) {
        VERIFY_CONTRACT(this->ok() && other.ok(), "Unable to perform copy assignment");

        if (*this == other) {
            return *this;
        }

        delete[] data_;

        data_ = new data_t[other.capacity_];
        VERIFY_CONTRACT(data_ != nullptr, "Unable to allocate memory");

        size_ = other.size_;
        capacity_ = other.capacity_;
        std::copy_n(other.data_, other.size_, data_);

        VERIFY_CONTRACT(this->ok(), "Unable to perform copy assignment");
        return *this;
    }

    template <typename data_t>
    Stack<data_t>& Stack<data_t>::operator=(Stack<data_t>&& other) {
        VERIFY_CONTRACT(this->ok() && other.ok(), "Unable to perform move assignment");


        if (*this == other) {
            return *this;
        }

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;


        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        VERIFY_CONTRACT(this->ok() && !other.ok(), "Unable to perform move assignment");
        return *this;
    }

    template <typename data_t>
    bool Stack<data_t>::operator==(const Stack& other) const {
        if (size_ == other.size()) {
            if (capacity_ == other.capacity()) {
                return true;
            }
        }
        return false;
    }

    template <typename data_t>
    bool Stack<data_t>::operator==(Stack&& other) const {
        if (size_ == other.size()) {
            if (capacity_ == other.capacity()) {
                return true;
            }
        }
        return false;
    }

    template <typename data_t>
    size_t Stack<data_t>::size() const {
        VERIFY_CONTRACT(this->ok(), "Unable to get stack size");
        return size_;
    }

    template <typename data_t>
    size_t Stack<data_t>::capacity() const {
        VERIFY_CONTRACT(this->ok(), "Unable to get stack capacity");
        return capacity_;
    }

    template <typename data_t>
    void Stack<data_t>::push(const data_t& value) {
        VERIFY_CONTRACT(this->ok(), "Unable to perform copy push command");

        if (size_ == capacity_) {
            augment();
        }

        data_[size_] = value;
        ++size_;
        VERIFY_CONTRACT(this->ok(), "Unable to perform copy push command");
    }


    template <typename data_t>
    void Stack<data_t>::push(data_t&& value) {
        VERIFY_CONTRACT(this->ok(), "Unable to perform move push command");

        if (size_ == capacity_) {
            augment();
        }

        data_[size_] = std::move(value);
        ++size_;
        VERIFY_CONTRACT(this->ok(), "Unable to perform move push command");
    }


    template <typename data_t>
    void Stack<data_t>::pop() {
        VERIFY_CONTRACT(this->ok(), "Unable to perform pop command");

        if (size_ == 0) {
            return;
        }

        if (4 * size_ < capacity_) {
            diminish();
        }
        --size_;
        VERIFY_CONTRACT(this->ok(), "Unable to perform pop command");
    }


    template <typename data_t>
    data_t& Stack<data_t>::top() {
        VERIFY_CONTRACT(this->ok() && size_ != 0, "Unable to perform top command");
        return data_[size_ - 1];
    }
} // namespace stack_

