#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <chrono>
#include <random>

#include "Figure.h"


int main() {
    int q = 0;
    std::cin >> q;
    Field f;
    for(int i = 0; i < q; ++i) {
        f.AddFigure(0);
    }
    f.PrintField();
    return 0;
}
