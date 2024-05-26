//
// Created by vorop on 30.10.2023.
//

#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(bool color, short int y,short int x, bool specialCondition): Figure(color,y,x,specialCondition) {}

TypeFigure Bishop::getType() {  return TypeFigure::Bishop;  }      // Получить тип фигуры

std::vector<Coordinates>&  Bishop::getCoordinatesShift() { return shift;    }   // Получить координаты сдвига

bool Bishop::isAvailableSquare(Coordinates& tempCoord, Board& board) {  // Получить доступные для перемещения клетки
    int i{1};
    // Если клетка пустая, либо занята фигурой противоположного цвета
    if (board.map[tempCoord.y][tempCoord.x] == nullptr || board.map[tempCoord.y][tempCoord.x]->isColorWhite() !=
                                                          board.map[coordinates.y][coordinates.x]->isColorWhite()) {
        // Проверка, на то, свободны ли клетки, которые стоят на пути перемещения
        if (tempCoord.x > coordinates.x) {      // Направление движения по х
            if (tempCoord.y > coordinates.y)
                for ( ; board.map[coordinates.y + i][coordinates.x + i] == nullptr && coordinates.x + i < tempCoord.x; i++);
            else      // если tempCoord.y < coordinates.y
                for (; board.map[coordinates.y - i][coordinates.x + i] == nullptr && coordinates.x + i < tempCoord.x; i++);
            if (i + coordinates.x == tempCoord.x)   return true;
            else                    return false;
        }
        else if(tempCoord.x < coordinates.x) {  // Направление движения по х
            if (tempCoord.y > coordinates.y)
                for ( ; board.map[coordinates.y + i][coordinates.x - i] == nullptr && coordinates.x - i > tempCoord.x; i++);
            else      // если tempCoord.y < coordinates.y
                for ( ; board.map[coordinates.y - i][coordinates.x - i] == nullptr && coordinates.x - i > tempCoord.x; i++);
            if (coordinates.x - i == tempCoord.x)   return true;
            else                    return false;
        }
    }
    return false;
}