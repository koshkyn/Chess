//
// Created by Александр on 14.05.2020.
//

#include "Field.h"

Field::Field(int _fsize) :
        FieldSize(_fsize), fld(std::vector<std::vector<int>>(_fsize, std::vector<int>(_fsize, -1))) {}

void Field::AddFigure(int type) {
    while(true) {
        //Генерируется случайная клетка. Если она свободна, то выходит из цикла.
        std::mt19937 rm(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        int x = rm() % FieldSize;
        int y = rm() % FieldSize;
        if(fld[x][y] == -1) {
            fld[x][y] = Figures.size();
            Figures.push_back(CreateFigure(type, x, y));
            break;
        }
    }
}

void Field::PrintField() const {
    for(auto row = fld.rbegin(); row != fld.rend(); row++) {
        for(auto& col : *row) {
            if(col != -1) {
                std::cout << col << " ";
            } else {
                std::cout << "x" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Field::StartMoving() {
    int DELAY_TIME = 200; //Параметр задержки времени между двумя ходами
    std::queue<Query> Queries; //Очередь ходов фигур, которые заблокированы другими фигурами
    std::vector<int> inQuery(Figures.size(), 0); //Вектор - индикатор, находится ли фигура в очереди ходов
    PrintField();
    bool Got50 = false; //Достигли ли все фигуры 50 ходов или нет
    while(!Got50) {
        bool temp_counter = true;
        for(int i = 0; i < Figures.size(); ++i) {
            ClearQuery(Queries, inQuery);
            if(!Figures[i]->TryCounter() && inQuery[i] == 0) { // Проверяем, сделала ли фигура 50 ходов и находится ли в очереди ходов
                Square deltas = Figures[i]->GenerateDeltas();
                int x_delta = deltas.GetX();
                int y_delta = deltas.GetY();
                if (TryMove(i, x_delta, y_delta)) { //Если ход возможен, то перемещаем фигуру
                    MoveFigure(i, x_delta, y_delta);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_TIME)); //Делаем задержку времени
                    ClearQuery(Queries, inQuery); //Очищаем очередь ходов от тех, которым больше 5 сек
                    for(int i = 0; i < Queries.size(); ++i) { //И пытаемся сделать ходы из очереди
                        Query current = Queries.front();
                        Queries.pop();
                        //Если фигура освободилась, то очищаем её из очереди, делаем ход и делаем задержку.
                        if(TryMove(current.vec_pos, current.move_vector.GetX(), current.move_vector.GetY())) {
                            MoveFigure(current.vec_pos, current.move_vector.GetX(), current.move_vector.GetY());
                            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_TIME));
                            inQuery[current.vec_pos] = 0;
                            std::cout << current << " used." << std::endl;
                        } else {
                            //Если не освободилась, то отправляем её обратно в очередь
                            Queries.push(current);
                        }
                    }
                } else {
                    //Ход невозможен, значит добавляем этот ход в очередь и индикатор нахождения фигуры в очереди делаем 1.
                    Queries.push({i, Square(x_delta, y_delta), std::chrono::steady_clock::now() });
                    std::cout << Queries.back() << " created." << std::endl;
                    inQuery[i] = 1;
                }
            }
            //Если все фигуры достигнут 50 ходов, то этот параметр будет true, но если хотя бы одна фигура сделала меньше 50 ходов, то он будет false.
            temp_counter = temp_counter && Figures[i]->TryCounter();
        }
        Got50 = temp_counter;
    }
}

void ClearQuery(std::queue<Query>& queries, std::vector<int>& inQuery) {
    for(int i = 0; i < queries.size(); ++i) {
        std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
        Query current = queries.front();
        queries.pop();
        if(std::chrono::duration_cast<std::chrono::seconds>(current_time - current.start).count() < 5) {
            queries.push(current);
        } else {
            inQuery[current.vec_pos] = 0;
            std::cout << current << " deleted (time limit). " << std::endl;
        }
    }
}
void Field::MoveFigure(int i, int delta_x, int delta_y) {
    int x = Figures[i]->GetPosition().GetX();
    int y = Figures[i]->GetPosition().GetY();
    if(Figures[i]->Motion(delta_x, delta_y)) { //Если фигура не переместится за пределы шахматной доски, то перемещаем
        std::swap(fld[x][y], fld[x + delta_x][y + delta_y]);

        //Генерируем сообщение о перемещении фигуры. Х и Y здесь поменяны местами для ясности перемещения в консоли.
        std::string result =
                (delta_x != 0) ? (((delta_x > 0) ? " up " : " down ") + std::to_string(abs(delta_x))) : "" +
                (delta_y != 0) ? (((delta_y > 0) ? " right " : " left ") + std::to_string(abs(delta_y))) : "" ;
        std::cout << std::endl << "Figure " << Figures[i]->GetType() << " N" << i << " moves"
                  << result << std::endl << std::endl;
        PrintField();
    }
}

bool Field::TryMove(int i, int delta_x, int delta_y) {
    int x = Figures[i]->GetPosition().GetX();
    int y = Figures[i]->GetPosition().GetY();
    for(int f = 0; f < Figures.size(); ++f) {
        if(f != i) {
            Square fig_pos = Figures[f]->GetPosition();
            if(delta_x < 0 || delta_y < 0) {
                if( //Проверка на наличие фигур при движении вперед(то есть с положительной дельтой)
                        x >= fig_pos.GetX() && (x + delta_x) <= fig_pos.GetX() &&
                        y >= fig_pos.GetY() && (y + delta_y) <= fig_pos.GetY()
                        )
                { return false; }
            } else { //проверка на наличие фигур при движении назад(то есть с отрицательной дельтой)
                if (
                        x <= fig_pos.GetX() && (x + delta_x) >= fig_pos.GetX() &&
                        y <= fig_pos.GetY() && (y + delta_y) >= fig_pos.GetY()
                        )
                { return false; }
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const Query& current) {
    out << "Query: {" << current.vec_pos << ", {" << current.move_vector.GetX() << ", "
              << current.move_vector.GetY() << "} }" ;
    return out;
}