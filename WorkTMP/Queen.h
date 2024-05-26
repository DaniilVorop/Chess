//
// Created by vorop on 26.10.2023.
//
#pragma once
#ifndef COURSEWORK_QUEEN_H
#define COURSEWORK_QUEEN_H
#include "Figure.h"
#include "Rook.h"
#include "Bishop.h"

class Queen : public Rook, public Bishop{       // Класс фигуры "Ладья"
std::vector<Coordinates> shift;                 // Координаты возможных сдвигов
public:
    Queen(bool color, short int y,short int x,bool specialCondition);
    Queen() = default;
    ~Queen() override = default;
    TypeFigure getType() override;              // Получить тип фигуры
    std::vector<Coordinates>& getCoordinatesShift() override;   // Получить координаты сдвигов
    bool isAvailableSquare(Coordinates& tempCoord, Board& board) override;  // Проверить возможность перемещения
};
#endif //COURSEWORK_QUEEN_H
