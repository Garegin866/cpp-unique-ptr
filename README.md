## unique-ptr

A simple implementation of std::unique_ptr in C++.
This project is for learning about smart pointers, ownership, and RAII.

## 📌 What is this? 
This is a minimal custom implementation of a smart pointer that exclusively owns a dynamically allocated object — just like C++’s std::unique_ptr.
When the unique_ptr goes out of scope, it automatically deletes the managed object.

## ✨ Features 
✅ Exclusive ownership of a resource \
✅ Automatic cleanup (RAII) \
✅ Move semantics (no copy) \
✅ Custom deleter support (optional, stretch goal)

## 📂 Project structure 

```css
.
├── include/
│   └── unique_ptr.hpp
├── src/
│   └── main.cpp
├── tests/
│   └── unique_ptr_tests.cpp
└── README.md
```

## 🚀 Build & Run
``` md
# Clone the repo
git clone https://github.com/yourusername/unique-ptr.git
cd unique-ptr

# Compile
g++ -std=c++20 src/main.cpp -Iinclude -o main

# Run
./main

```
## 🧩 Example usage

``` cpp
#include "unique_ptr.hpp"
#include <iostream>

struct Test {
    Test() { std::cout << "Created\n"; }
    ~Test() { std::cout << "Destroyed\n"; }
    void sayHello() { std::cout << "Hello!\n"; }
};

int main() {
    unique_ptr<Test> ptr(new Test());
    ptr->sayHello();
    // Automatic destruction when ptr goes out of scope
    return 0;
}
```

## ⚖️ License
**MIT** — use it, learn from it, modify it!