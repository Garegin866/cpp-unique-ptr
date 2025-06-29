#pragma once

#include <utility>
#include <memory>
#include <type_traits>
#include <cstddef>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    unique_ptr() noexcept
            : ptr_(nullptr) {}

    explicit unique_ptr(T* ptr) noexcept
            : ptr_(ptr) {}

    unique_ptr(T* ptr, Deleter deleter) noexcept
            : ptr_(ptr), deleter_(std::move(deleter)) {}

    ~unique_ptr() noexcept {
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

    constexpr T& operator*() const noexcept {
        return *ptr_;
    }

    constexpr T* operator->() const noexcept {
        return ptr_;
    }

    constexpr explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    Deleter& get_deleter() noexcept { return deleter_; }
    const Deleter& get_deleter() const noexcept { return deleter_; }

    void swap(unique_ptr& other) noexcept {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(deleter_, other.deleter_);
    }

    constexpr T* get() const noexcept {
        return ptr_;
    }

    T* release() noexcept {
        return std::exchange(ptr_, nullptr);
    }

    void reset(T* new_ptr = nullptr) noexcept {
        deleter_(std::exchange(ptr_, new_ptr));
    }

private:
    T* ptr_ = nullptr;
    Deleter deleter_;
};

template <typename T, typename Deleter>
class unique_ptr<T[], Deleter> {
public:
    unique_ptr() noexcept
            : ptr_(nullptr) {}

    explicit unique_ptr(T* ptr) noexcept
            : ptr_(ptr) {}

    unique_ptr(T* ptr, Deleter deleter) noexcept
            : ptr_(ptr), deleter_(std::move(deleter)) {}

    ~unique_ptr() noexcept {
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

    T& operator[](std::size_t i) const noexcept {
        return ptr_[i];
    }

    constexpr explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    Deleter& get_deleter() noexcept { return deleter_; }
    const Deleter& get_deleter() const noexcept { return deleter_; }

    void swap(unique_ptr& other) noexcept {
        using std::swap;
        swap(ptr_, other.ptr_);
        swap(deleter_, other.deleter_);
    }

    constexpr T* get() const noexcept {
        return ptr_;
    }

    T* release() noexcept {
        return std::exchange(ptr_, nullptr);
    }

    void reset(T* new_ptr = nullptr) noexcept {
        deleter_(std::exchange(ptr_, new_ptr));
    }

private:
    T* ptr_ = nullptr;
    Deleter deleter_;
};

template <typename T, typename... Args>
std::enable_if_t<!std::is_array<T>::value, unique_ptr<T>>
make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
std::enable_if_t<std::is_array<T>::value && std::extent<T>::value == 0, unique_ptr<T>>
make_unique(std::size_t size) {
    using U = typename std::remove_extent<T>::type;
    return unique_ptr<T>(new U[size]);
}