//
// Created by Александр on 12.05.2020.
//

#include "Figure.h"

Figure::Figure(int _x, int _y, const std::string& _t, int p_size) : position(Square(_x, _y)), type(_t), PlateSize(p_size) {}

Square Figure::GetPosition() const {return position;}

std::string Figure::GetType() const {return type;}

Rook::Rook(int _x, int _y) : Figure(_x, _y, "Rook") {}

bool Rook::Motion(int x = 0, int y = 0) {
    //Проверка на выход за пределы поля
    if(
            (position.GetX() + x >= PlateSize) || (position.GetX() + x < 0) ||
            (position.GetY() + y >= PlateSize) || (position.GetY() + y < 0) ||
            (x != 0 && y != 0)
            )
    {
        return false;
    }
    position.SumX(x);
    position.SumY(y);
    ++counter; //увеличиваем счетчик ходов фигуры
    return true;
}

bool Figure::TryCounter() const {return counter >= 50;}

Square Figure::GenerateDeltas() const {
    //В данном методе реализована случайная генерация вектора перемещения фигуры
    //
    //
    //Текущие координаты фигуры
    int cur_x = GetPosition().GetX();
    int cur_y = GetPosition().GetY();
    //Генерируется случайное положительное значение(random_value), меньшее размера поля.
    std::mt19937 rm(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    int random_value = abs(rm()) % PlateSize;
    //Вычисляется дельта смещения.
    //Если сумма числа и текущей координаты больше размеров поля(т.к. они хранятся в массиве, то размер поля -1),
    //то берем остаток от деления этой суммы, если нет, то оставляем это число.
    int x_delta = (cur_x + random_value) >= PlateSize ? (cur_x + random_value) % PlateSize : random_value;
    int y_delta = (cur_y + random_value) >= PlateSize ? (cur_y + random_value) % PlateSize : random_value;
    //Если сгенерированное число четное, то перемещение будет по оси Х, если нечетное, то по оси Y.
    int x_or_y = random_value % 2;
    if (x_or_y == 0) {
        if (x_delta == 0) { x_delta = 1; } //отсеиваем вариант, когда дельта равна 0, чтобы не было пустых ходов
        //Если сумма получившейся дельты с координатой больше размеров поля, то дельта будет отрицательной
        //Если меньньше, то положительной.
        //Таким образом получается достичь валидной дельты и направления перемещения при каждой генерации случайного значения
        x_delta *= (cur_x + x_delta > PlateSize - 1) ? -1 : 1;
        y_delta = 0;
    } else {
        if (y_delta == 0) { y_delta = 1; }
        y_delta *= (cur_y + y_delta > PlateSize - 1) ? -1 : 1;
        x_delta = 0;
    }
    return Square(x_delta, y_delta);
}

Figure* CreateFigure(int t, int _x, int _y) {
    FiguresType type = static_cast<FiguresType>(t);
    switch(type) {
        case FiguresType::ROOK : return new Rook(_x, _y);
        default: return new Rook(_x, _y);
    }
}

