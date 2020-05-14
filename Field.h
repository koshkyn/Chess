//
// Created by Александр on 14.05.2020.
//

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H
#pragma once
#include "Figure.h"


//Структура запросов на ход, содержит в себе объект, вектор смещения и точку отсчета времени
struct Query {
    int vec_pos; //индекс в векторе фигур
    Square move_vector; //на сколько сместить фигуру
    std::chrono::steady_clock::time_point start;
};

//Класс шахматного поля
class Field {
public:
    //Конструктор, принимающий значение шахматного поля(по умолчанию 8х8)
    Field(int _fsize = 8);
    //Метод добавления фигуры, на вход принимает ID фигуры для enumeratora
    void AddFigure(int type);
    //Вывод текущего положения фигур на поле. При выводе оси Х и Y перепутаны.
    //В дальнейшем, для наглядности, в некоторых методах они поменяны местами.
    void PrintField() const;
    //Метод, запускающий случайное движение всех фигур
    void StartMoving();
    //Метод, выполняющий движение фигуры
    void MoveFigure(int i, int delta_x, int delta_y);
    //Проверка на возможность перемещения фигуры (есть ли на пути другие фигуры)
    bool TryMove(int i, int delta_x, int delta_y);
private:
    std::vector<std::vector<int>> fld; //матрица шахматного поля (значение клетки -1 означает, что на ней нет фигуры)
    std::vector<Figure*> Figures; //вектор фигур на шахматном поле
    int FieldSize;
};

//Фабричный метод создания фигур
Figure* CreateFigure(int type, int _x, int _y);

//Функция, очищающая очередь запросов, которым больше 5 секунд
void ClearQuery(std::queue<Query>& queries, std::vector<int>& inQuery);

std::ostream& operator<<(std::ostream& out, const Query& current);



#endif //CHESS_FIELD_H
