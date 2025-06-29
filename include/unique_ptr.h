#pragma once

#include <utility>
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    unique_ptr() : ptr_(nullptr) {}

    explicit unique_ptr(T* ptr) : ptr_(ptr) {}

    unique_ptr(T* ptr, Deleter deleter)
            : ptr_(ptr), deleter_(deleter) {}

    ~unique_ptr() {
        if (ptr_) deleter_(ptr_);
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& oth) noexcept
            : ptr_(oth.ptr_), deleter_(std::move(oth.deleter_)) {
        oth.ptr_ = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& oth) noexcept {
        if (this != &oth) {
            deleter_(ptr_);
            ptr_ = oth.ptr_;
            deleter_ = std::move(oth.deleter_);
            oth.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    void swap(unique_ptr& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }

    T* get() const {
        return ptr_;
    }

    T* release() {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    void reset(T* new_ptr = nullptr) {
        deleter_(ptr_);
        ptr_ = new_ptr;
    }

private:
    T* ptr_ = nullptr;
    Deleter deleter_;
};


template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}