//
// Created by Александр on 12.05.2020.
//
#pragma once
#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

//класс клетки на поле, на которой находится фигура
class Square {
public:
    Square(int _x, int _y);
    void SumX(int val); //переместить фигуру по оси Х на расстояние 'val'
    void SumY(int val); //аналогично по оси Y
    const int GetX(); //получить координату оси Х
    const int GetY(); //аналогично, оси Y

private:
    int x;
    int y;
};
#endif //CHESS_SQUARE_H
