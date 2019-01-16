#include <iostream>

class Moveable {
public:
    Moveable(): i(new int(3)) {}
    ~Moveable() { delete i; }
    Moveable(const Moveable& m): i(new int(*m.i)) {}
    Moveable(Moveable&& m): i(m.i) { m.i = nullptr; }

    int* i;
};

int main() {
    Moveable a;
    Moveable c(std::move(a)); // call Moveable(Moveable&& m)
    std::cout << *a.i << std::endl;
}
