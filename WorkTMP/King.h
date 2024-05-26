//
// Created by vorop on 26.10.2023.
//
#pragma once
#ifndef COURSEWORK_KING_H
#define COURSEWORK_KING_H
#include "Figure.h"


class King : public Figure{             // Класс короля
    std::vector<Coordinates> shift = {Coordinates(1, 0), Coordinates(1, 1), Coordinates(1, -1), // Возможные сдвиги
                                      Coordinates(-1, 0), Coordinates(-1, 1), Coordinates(-1, -1),
                                      Coordinates(0, 1), Coordinates(0, -1),
                                      Coordinates(0, 2), Coordinates(0, -2) };
public:
    King(bool color, short int y,short int x,bool specialCondition);
    King() = default;
    ~King() override = default;
    TypeFigure getType() override;                                              // Получить тип фигуры
    std::vector<Coordinates>& getCoordinatesShift() override;                   // Получить координаты сдвигов
    bool isAvailableSquare(Coordinates& tempCoord, Board& board) override;      // Проверить на возможность перемещения
    bool checkCastling(Coordinates& newCoord, Board& board);                    // Проверка на возможность рокировки
};
#endif //COURSEWORK_KING_H
