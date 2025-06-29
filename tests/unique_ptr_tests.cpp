#include "unique_ptr.h"

#include <cassert>
#include <iostream>

struct Bar {
    Bar() { std::cout << "Bar constructed\n"; }
    ~Bar() { std::cout << "Bar destructed\n"; }
    int value = 42;
};

void test_basic() {
    unique_ptr<Bar> p = make_unique<Bar>();
    assert(p->value == 42);
    assert((*p).value == 42);
}

void test_move() {
    unique_ptr<Bar> p1 = make_unique<Bar>();
    unique_ptr<Bar> p2 = std::move(p1);

    assert(!p1);
    assert(p2);
}

void test_reset() {
    unique_ptr<Bar> p = make_unique<Bar>();
    p.reset(new Bar()); // old Bar should be destructed
    assert(p);
}

void test_release() {
    unique_ptr<int> p = make_unique<int>(42);
    int* raw = p.release();
    assert(raw && !p);
    delete raw; // you must clean up yourself now!
}

struct Widget {
    Widget() { std::cout << "Widget constructed\n"; }
    ~Widget() { std::cout << "Widget destructed\n"; }
    void hello() const { std::cout << "Hello from Widget\n"; }
};

void test_custom_deleter() {
    bool deleterCalled = false;

    auto myDeleter = [&deleterCalled](Widget* w) {
        std::cout << "Custom deleter called!\n";
        deleterCalled = true;
        delete w;
    };

    {
        unique_ptr<Widget, decltype(myDeleter)> p(new Widget(), myDeleter);
        p->hello();
        assert(p);
    } // p goes out of scope → custom deleter should run

    assert(deleterCalled);
    std::cout << "Custom deleter test passed!\n";
}

int main() {
    std::cout << "Running tests...\n";

    test_basic();
    test_move();
    test_reset();
    test_release();
    test_custom_deleter();

    std::cout << "All tests passed!\n";
    return 0;
}
