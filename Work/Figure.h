#pragma once
#ifndef COURSEWORK_FIGURE_H
#define COURSEWORK_FIGURE_H
#include "iostream"
#include "Coordinates.h"
#include "Header.h"
class Board;

class Figure {                          // Абстрактный класс фигур
private:
    bool specialCondition;              // Специальное состояние фигуры
    bool color;                         // Цвет фигуры
protected:
    Coordinates coordinates;            // Координаты фигуры
public:
    Figure();
    Figure(bool color, short int y, short int x, bool specialCondition);
    virtual ~Figure() = default;

    bool testOnCheck(Coordinates newCoordinates, Board& board, bool whiteColorMove);    // Проверить на шах
    std::vector<Coordinates> getAvailableMoveSquares(Board &board, bool testCheck);     // Получить доступные ходы
    void setSpecialCondition(bool condition) {  specialCondition = condition;   }       // Установить спец. состояние фигуры
    bool getSpecialCondition() const {    return specialCondition;    }                 // Получить спец. состояние фигуры
    virtual TypeFigure getType() = 0;                                                   // Получить тип фигуры
    bool isColorWhite() const;                                                          // Получить цвет фигуры
    void setCoordinates(Coordinates newCoord) { coordinates = newCoord; }               // Установить координаты

protected:
    virtual std::vector<Coordinates>& getCoordinatesShift() = 0;                        // Получить возможные координаты сдвигов
    virtual bool isAvailableSquare(Coordinates &tempCoord, Board &board);               // Проверить клетку на возможность перемещения
};
#endif //COURSEWORK_FIGURE_H



