//
// Created by Александр on 12.05.2020.
//

#include "Figure.h"

Figure::Figure(int _x, int _y, const std::string& _t, int p_size) : position(Square(_x, _y)), type(_t), PlateSize(p_size) {}

Square Figure::GetPosition() const {return position;}

std::string Figure::GetType() const {return type;}

Rook::Rook(int _x, int _y) : Figure(_x, _y, "Rook") {}
bool Rook::Motion(int x = 0, int y = 0) {
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
    counter++;
    return true;
}

bool Rook::TryCounter() const {return counter == 50;}

Figure* CreateFigure(int t, int _x, int _y) {
    FiguresType type = static_cast<FiguresType>(t);
    switch(type) {
        case FiguresType::ROOK : return new Rook(_x, _y);
        default: return new Rook(_x, _y);
    }
}

Field::Field(int _fsize) :
    FieldSize(_fsize), fld(std::vector<std::vector<int>>(_fsize, std::vector<int>(_fsize, -1))) {}

void Field::AddFigure(int type) {
    while(true) {
        int x = rand() % FieldSize;
        int y = rand() % FieldSize;
        if(fld[x][y] == -1) {
            fld[x][y] = Figures.size();
            Figures.push_back(CreateFigure(type, x, y));
            break;
        }
    }
}

void Field::PrintField() const {
    for(auto& row : fld) {
        for(auto& col : row) {
            if(col != -1) {
                std::cout << Figures[col]->GetType()[0] << " ";
            } else {
                std::cout << "x" << " ";
            }
        }
        std::cout << std::endl;
    }
}