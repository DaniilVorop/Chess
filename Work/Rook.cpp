//
// Created by vorop on 26.10.2023.
//

#include "Rook.h"
#include "Board.h"
Rook::Rook(bool color, short int y,short int x,bool specialCondition): Figure(color,y,x,specialCondition) {}
TypeFigure Rook::getType() {    return TypeFigure::Rook;    }

std::vector<Coordinates>&  Rook::getCoordinatesShift() {
    return shift;   // Возможные сдвиги
}
    // Получить доступные перемещения
bool Rook::isAvailableSquare(Coordinates& tempCoord, Board& board) {
    int i;
    // Если клетка пустая, либо занята фигурой противоположного цвета
    if (board.map[tempCoord.y][tempCoord.x] == nullptr || board.map[tempCoord.y][tempCoord.x]->isColorWhite() !=
                                                          board.map[coordinates.y][coordinates.x]->isColorWhite()) {
        // Проверить пустые ли клетки, стоящие на пути смещения
        if (tempCoord.x == coordinates.x) {
            if (tempCoord.y > coordinates.y)
                for (i = coordinates.y + 1; board.map[i][tempCoord.x] == nullptr && i < tempCoord.y; i++);
            else      // если tempCoord.y < coordinates.y
                for (i = coordinates.y - 1; board.map[i][tempCoord.x] == nullptr && i > tempCoord.y; i--);
            if (i == tempCoord.y)   return true;
            else                    return false;
        }
        if (tempCoord.y == coordinates.y) {     // Пустые клетки на пути смещения
            if (tempCoord.x > coordinates.x)
                for (i = coordinates.x + 1; board.map[tempCoord.y][i] == nullptr && i < tempCoord.x; i++);
            else      // если tempCoord.y < coordinates.y
                for (i = coordinates.x - 1; board.map[tempCoord.y][i] == nullptr && i > tempCoord.x; i--);
            if (i == tempCoord.x)   return true;
            else                    return false;
        }
    }
    return false;
}