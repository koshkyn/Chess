//
// Created by Александр on 12.05.2020.
//
#pragma once

#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

#include "square.h"


enum FiguresType { //тут перечислять все типы фигур, используется при создании фабричным методом
    ROOK = 0,
};

class Figure { //aбстрактный класс всех фигур
public:
    virtual bool Motion(int x, int y) = 0; //Виртуальный метод, описывающий ход фигуры. Возвращает сделан ли ход.
    Square GetPosition() const; //Получение текущей позиции фигуры
    std::string GetType() const; //Получение типа фигуры
    bool TryCounter() const; //Проверка, сделала ли эта ладья 50 ходов
    Square GenerateDeltas() const; //Метод генерации дельты перемещения фигуры
protected:
    //Конструктор, принимающий начальные координаты фигуры, тип и размер поля(по умолчанию 8х8)
    Figure(int _x, int _y, const std::string& _t, int p_size = 8);
    Square position;
    std::string type;
    int PlateSize;
    int counter = 0;
};

class Rook : public Figure { //класс Ладьи
public:
    Rook(int _x, int _y);
    bool Motion(int x, int y) override;
};




#endif //CHESS_FIGURE_H
