#include "unique_ptr.h"

#include <iostream>

struct Foo {
    Foo() { std::cout << "Foo constructed\n"; }
    ~Foo() { std::cout << "Foo destructed\n"; }
    void say() const { std::cout << "Hello from Foo!\n"; }
};

int main() {
    unique_ptr<Foo> ptr = make_unique<Foo>();
    ptr->say();

    // Transfer ownership with move
    unique_ptr<Foo> ptr2 = std::move(ptr);
    if (!ptr) {
        std::cout << "ptr is now empty.\n";
    }
    ptr2->say();

    return 0;
}
