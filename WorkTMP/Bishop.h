//
// Created by vorop on 26.10.2023.
//
#pragma once
#ifndef COURSEWORK_BISHOP_H
#define COURSEWORK_BISHOP_H

#include "Figure.h"

class Bishop : virtual public Figure{       // Класс "Слона"
protected:
    std::vector<Coordinates> shift = {Coordinates(1, 1), Coordinates(2, 2), Coordinates(3, 3),      // Возможные координаты сдвигов
                                      Coordinates(4, 4), Coordinates(5, 5), Coordinates(6, 6), Coordinates(7, 7),
                                      Coordinates(-1, -1), Coordinates(-2, -2), Coordinates(-3, -3),
                                      Coordinates(-4, -4), Coordinates(-5, -5), Coordinates(-6, -6), Coordinates(-7, -7),
                                      Coordinates(-1, 1), Coordinates(-2, 2), Coordinates(-3, 3),
                                      Coordinates(-4, 4), Coordinates(-5, 5), Coordinates(-6, 6), Coordinates(-7, 7),
                                      Coordinates(1, -1), Coordinates(2, -2), Coordinates(3, -3),
                                      Coordinates(4, -4), Coordinates(5, -5), Coordinates(6, -6), Coordinates(7, -7)   };
public:
    Bishop(bool color, short int y,short int x, bool specialCondition);
    Bishop() = default;
    ~Bishop() override = default;
    TypeFigure getType() override;          // Получить тип фигуры
    std::vector<Coordinates>& getCoordinatesShift() override;   // Получить возможные координаты сдвигов
    bool isAvailableSquare(Coordinates& tempCoord, Board& board) override;  // Проверка на возможность перемещения
};

#endif //COURSEWORK_BISHOP_H
