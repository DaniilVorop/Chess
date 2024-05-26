//
// Created by vorop on 26.10.2023.
//
#pragma once
#ifndef COURSEWORK_ROOK_H
#define COURSEWORK_ROOK_H
#include "Figure.h"


class Rook : virtual public Figure{
protected:
    std::vector<Coordinates> shift = {Coordinates(1, 0), Coordinates(2, 0), Coordinates(3, 0),  // Координаты сдвигов
                                      Coordinates(4, 0), Coordinates(5, 0), Coordinates(6, 0), Coordinates(7, 0),
                                      Coordinates(-1, 0), Coordinates(-2, 0), Coordinates(-3, 0),
                                      Coordinates(-4, 0), Coordinates(-5, 0), Coordinates(-6, 0), Coordinates(-7, 0),
                                      Coordinates(0, 1), Coordinates(0, 2), Coordinates(0, 3),
                                      Coordinates(0, 4), Coordinates(0, 5), Coordinates(0, 6), Coordinates(0, 7),
                                      Coordinates(0, -1), Coordinates(0, -2), Coordinates(0, -3),
                                      Coordinates(0, -4), Coordinates(0, -5), Coordinates(0, -6), Coordinates(0, -7)   };
public:
    Rook(bool color, short int y,short int x,bool specialCondition);
    Rook() = default;
    ~Rook() override = default;
    TypeFigure getType() override;                   // Получить тип фигуры
    std::vector<Coordinates>& getCoordinatesShift() override;       // Получить координаты сдвига
    bool isAvailableSquare(Coordinates& tempCoord, Board& board) override;  // Проверка на возможность перемещения
};


#endif //COURSEWORK_ROOK_H
