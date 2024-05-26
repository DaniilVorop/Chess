//
// Created by vorop on 25.10.2023.
//
#pragma once
#ifndef COURSEWORK_PAWN_H
#define COURSEWORK_PAWN_H


#include "Figure.h"

class Pawn : public Figure {        // Класс фигуры "Пешка"
protected:
    std::vector<Coordinates> shift = {Coordinates(1, 0), Coordinates(1, 1), Coordinates(1, -1), Coordinates(2, 0),  // Возможные координаты сдвига
                                      Coordinates(-1, 0), Coordinates(-1, 1), Coordinates(-1, -1), Coordinates(-2, 0),};
public:
    Pawn() = default;
    Pawn(bool color, short int y,short int x,bool specialCondition);
    ~Pawn() override = default;
    TypeFigure getType() override;                      // Получить тип
    bool isAvailableSquare(Coordinates& tempCoord, Board& board) override;  // Проверить на возможность перемещения
    std::vector<Coordinates>& getCoordinatesShift() override;               // Получить координаты сдвига
};




#endif //COURSEWORK_PAWN_H
