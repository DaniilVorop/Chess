#include "King.h"
#include "Board.h"

King::King(bool color, short int y,short int x, bool specialCondition): Figure(color,y,x,specialCondition) {}
TypeFigure King::getType() {    return TypeFigure::King;    }  // Получение типа
    // Получить координат сдвига
std::vector<Coordinates>& King::getCoordinatesShift() {
    return shift;
}
    // Получить доступные для перемещения клетки
bool King::isAvailableSquare(Coordinates& tempCoord, Board& board) {
    // Проверка на рокировку
    if (abs(tempCoord.x - coordinates.x) == 2 ) {
        if (board.itWhiteMoveNow() == isColorWhite() && checkCastling(tempCoord, board)) {
            return true;
        }
        else return false;
    } else if (board.map[tempCoord.y][tempCoord.x] == nullptr ||
               this->isColorWhite() != board.map[tempCoord.y][tempCoord.x]->isColorWhite()) {
        return true;                                // Если клетка пустая, либо там находится фигура др. цвета
    }
    return false;
}
    // Проверка на рокировку
bool King::checkCastling(Coordinates& newCoord, Board& board) {
    if (testOnCheck(coordinates, board, isColorWhite())) {          // Если королю нет шаха
        short int i;
        if (newCoord.x - coordinates.x == 2) i = 1;                 // ближняя рокировка
        else i = -2;                                                // дальняя рокировка
        if (board.map[newCoord.y][newCoord.x] == nullptr &&
            getSpecialCondition() &&
            board.map[coordinates.y][newCoord.x + i] != nullptr &&
            board.map[coordinates.y][newCoord.x + i]->getType() == TypeFigure::Rook &&
            board.map[coordinates.y][newCoord.x + i]->getSpecialCondition()) {     // Король и ладья не двигались

            if (newCoord.x - coordinates.x == 2) {                   // Если рокировка вправо
                i = 1;
                if (board.map[coordinates.y][coordinates.x + 1] != nullptr) {      // Если клетки не пустые
                    return false;
                }
            }
            else {                                                   // Рокировка влево
                i = -1;
                if (board.map[coordinates.y][coordinates.x - 1] != nullptr ||
                    board.map[coordinates.y][coordinates.x - 3] != nullptr) {      // Если клетки не пустые
                    return false;
                }
            }
            Coordinates wayCoord(static_cast<short>(coordinates.y),static_cast<short>(coordinates.x + i));
            if (testOnCheck(wayCoord, board, isColorWhite()) )                     // Проверяю проходные клетки находятся ли под ударом
                return true;
        }
    }
    return false;
}
