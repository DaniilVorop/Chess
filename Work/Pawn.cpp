//
// Created by vorop on 30.10.2023.
//
#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(bool color, short y, short x,bool specialCondition) : Figure(color, y, x,specialCondition){}
TypeFigure Pawn::getType()  {  return TypeFigure::Pawn;    }
    // Получить доступные ходы
bool Pawn::isAvailableSquare(Coordinates& tempCoord, Board& board) {
    if (this->isColorWhite() && tempCoord.y > this->coordinates.y ||
        !this->isColorWhite() && tempCoord.y < this->coordinates.y)
        return false;   // запрещаю ход назад
    else if (tempCoord.x != this->coordinates.x) {
        if (board.map[tempCoord.y][tempCoord.x] != nullptr &&
            board.map[tempCoord.y][tempCoord.x]->isColorWhite() != this->isColorWhite())
            return true;     // разрешаю ходить наискосок, если там фигура другого цвета
        else if (board.map[this->coordinates.y][tempCoord.x] != nullptr &&
                 board.map[this->coordinates.y][tempCoord.x]->getType() == TypeFigure::Pawn &&
                 board.map[this->coordinates.y][tempCoord.x]->isColorWhite() != this->isColorWhite() &&
                 board.map[this->coordinates.y][tempCoord.x]->getSpecialCondition() )
            return true;    // взятие на проходе
    } else if (tempCoord.x == this->coordinates.x && board.map[tempCoord.y][tempCoord.x] == nullptr) {
        if ((tempCoord.y + this->coordinates.y) % 2 == 1)
            return true;     // разрешаю ход вперед на одну клетку, если там нет фигуры
        else if ((this->coordinates.y == 1 && !this->isColorWhite() ||
                  this->coordinates.y == 6 && this->isColorWhite()) &&
                 board.map[(tempCoord.y + coordinates.y) / 2][coordinates.x] == nullptr)
            return true;     // Разрешаю ход на две клетки в начале игры
    }
    return false;
}
    // Получить координаты сдвигов
std::vector<Coordinates>&  Pawn::getCoordinatesShift(){
    return shift;
}
