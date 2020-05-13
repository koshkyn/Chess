//
// Created by Александр on 12.05.2020.
//
#pragma once

#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <chrono>

#include "square.h"


enum FiguresType { //тут перечислять все типы фигур, используется при создании фабричным методом
    ROOK = 0,
};

class Figure { //aбстрактный класс всех фигур
public:
    virtual bool Motion(int x, int y) = 0; //Виртуальный метод, описывающий ход фигуры. Возвращает сделан ли ход.
    Square GetPosition() const; //Получение текущей позиции фигуры
    std::string GetType() const; //Получение типа фигуры
protected:
    //Конструктор, принимающий начальные координаты фигуры, тип и размер поля(по умолчанию 8х8)
    Figure(int _x, int _y, const std::string& _t, int p_size = 8);
    Square position;
    std::string type;
    int PlateSize;
};

class Rook : public Figure { //класс Ладьи
public:
    Rook(int _x, int _y);
    bool Motion(int x, int y) override;
    //Проверка, сделала ли эта ладья 50 ходов(оставил счетчик в Ладье, но можно и в родительский класс перенести)
    bool TryCounter() const;
private:
    int counter = 0;
};

//Структура запросов на ход, содержит в себе объект, вектор смещения и точку отсчета времени
struct Query {
    Figure* obj;
    std::pair<int, int> move_vector; //на сколько сместить фигуру
    std::chrono::steady_clock::time_point start;
};

//Класс шахматного поля
class Field {
public:
    Field(int _fsize = 8);
    //Метод добавления фигуры, на вход принимает ID фигуры для enumeratora
    void AddFigure(int type);
    //Вывод текущего положения фигур на поле
    void PrintField() const;
private:
    std::vector<std::vector<int>> fld;
    std::vector<Figure*> Figures;
    int FieldSize;
};

//Фабричный метод создания фигур
Figure* CreateFigure(int type, int _x, int _y);



#endif //CHESS_FIGURE_H
