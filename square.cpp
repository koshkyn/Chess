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
int Square::GetX() const {return x;}
int Square::GetY() const {return y;}