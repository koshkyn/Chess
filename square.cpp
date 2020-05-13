//
// Created by Александр on 12.05.2020.
//

#include "square.h"

Square::Square(int _x, int _y) : x(_x), y(_y) {}

void Square::SumX(int val) {
    x += val;
}
void Square::SumY(int val) {
    y += val;
}
const int Square::GetX() {return x;}
const int Square::GetY() {return y;}