#include <iostream>

#include "Field.h"


int main() {
    int q = 0;
    std::cout << "Insert count of figures: ";
    std::cin >> q;
    Field f;
    for(int i = 0; i < q; ++i) {
        f.AddFigure(0);
    }
    f.StartMoving();
    return 0;
}
