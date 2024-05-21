//
// Created by vorop on 26.10.2023.
//
#pragma once
#ifndef COURSEWORK_KNIGHT_H
#define COURSEWORK_KNIGHT_H
#include "Figure.h"

class Knight : public Figure{                  // Класс фигуры "Конь"
    std::vector<Coordinates> shift = {Coordinates(2, 1), Coordinates(-2, 1), Coordinates(2, -1), Coordinates(-2, -1),   // Возможные координаты сдвигов
                                      Coordinates(1, 2), Coordinates(-1, 2), Coordinates(1, -2), Coordinates(-1, -2)  };
public:
    Knight() = default;
    Knight(bool color, short int y,short int x,bool specialCondition);
    ~Knight() override = default;
    TypeFigure getType() override;                              // Получить тип фигуры
    std::vector<Coordinates>& getCoordinatesShift() override;   // Получить координаты сдвигов
};


#endif //COURSEWORK_KNIGHT_H
