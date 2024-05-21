//
// Created by vorop on 30.10.2023.
//
#include "Figure.h"
#include "Board.h"

Figure :: Figure() = default;
Figure :: Figure(bool color,short int y, short int x, bool specialCondition): color(color),coordinates(y,x) , specialCondition(specialCondition) {}
    // Получить доступные ходы
std::vector<Coordinates> Figure::getAvailableMoveSquares(Board& board, bool testCheck){
    std::vector<Coordinates> LegalMove;     // Вектор легальных ходов
    Coordinates newCoordinates{};           // Проверяемые координаты
    for(Coordinates shift : getCoordinatesShift()) {
        if (coordinates.isCanShift(shift)) {    // Не выходят ли координаты за границы
            newCoordinates = coordinates.newCoordinates(shift);
            if (isAvailableSquare(newCoordinates, board)) { // Доступна ли клетка для сдвига
                if (testCheck) {                            // Не ставит ли ход короля под удар
                    if (testOnCheck(newCoordinates, board, board.map[coordinates.y][coordinates.x]->isColorWhite()))
                        LegalMove.push_back(coordinates.newCoordinates(shift));
                }
                else LegalMove.push_back(coordinates.newCoordinates(shift));
            }
        }
    }
    return LegalMove;
}

    // Проверка на шах
bool Figure::testOnCheck(Coordinates newCoordinates, Board& board, bool whiteColorMove) { //true
    Figure* tempFigure = board.map[newCoordinates.y][newCoordinates.x]; // делаю копию фигуры
    // меняю координаты короля, если ход королем
    if (board.map[coordinates.y][coordinates.x]->getType() == TypeFigure::King) {
        if (board.map[coordinates.y][coordinates.x]->isColorWhite())
            board.whiteKingCoord = newCoordinates;
        else
            board.darkKingCoord = newCoordinates;
    }
    // Передвигаю фигуру
    if( !(coordinates == newCoordinates)) {
        board.map[newCoordinates.y][newCoordinates.x] = board.map[coordinates.y][coordinates.x];
        board.map[coordinates.y][coordinates.x] = nullptr;
    }

    // Проверка угрожают ли королю
    for(int y = 0; y < SIZEBOARD ; y++){    // Цикл по шахматной доске
        for(int x = 0; x < SIZEBOARD; x++){
            // Получаю доступные ходы фигур другого цвета и проверяю пересечение с координатой короля
            if( board.map[y][x] != nullptr && board.map[y][x]->isColorWhite() != whiteColorMove ) {
                for (Coordinates tempCoord: board.map[y][x]->getAvailableMoveSquares(board, false)) {
                    if (whiteColorMove && ( tempCoord == board.whiteKingCoord )) {  // Если координаты совпадают
                        // Возврат доски в прежнее состояние
                        board.map[coordinates.y][coordinates.x] = board.map[newCoordinates.y][newCoordinates.x];
                        if (board.map[coordinates.y][coordinates.x]->getType() == TypeFigure::King) {
                            if (board.map[coordinates.y][coordinates.x]->isColorWhite())
                                board.whiteKingCoord = coordinates;
                            else
                                board.darkKingCoord = coordinates;
                        }
                        board.map[newCoordinates.y][newCoordinates.x] = tempFigure;
                        return false;
                    }
                    if (!whiteColorMove && ( tempCoord == board.darkKingCoord )) {  // Если координаты совпадают
                        // Возврат доски в прежнее состояние
                        board.map[coordinates.y][coordinates.x] = board.map[newCoordinates.y][newCoordinates.x];
                        if (board.map[coordinates.y][coordinates.x]->getType() == TypeFigure::King) {
                            if (board.map[coordinates.y][coordinates.x]->isColorWhite())
                                board.whiteKingCoord = coordinates;
                            else
                                board.darkKingCoord = coordinates;
                        }
                        board.map[newCoordinates.y][newCoordinates.x] = tempFigure;
                        return false;
                    }
                }
            }
        }
    }
    // Если королю не угрожают вернуть доску в прежнее состояние
    board.map[coordinates.y][coordinates.x] =  board.map[newCoordinates.y][newCoordinates.x];
    if (board.map[coordinates.y][coordinates.x]->getType() == TypeFigure::King) {
        if (board.map[coordinates.y][coordinates.x]->isColorWhite())
            board.whiteKingCoord = coordinates;
        else
            board.darkKingCoord = coordinates;
    }
    board.map[newCoordinates.y][newCoordinates.x] = tempFigure;
    return true;
}

    // Проверка доступна ли клетка для смещения, если она пустая или в ней находится фигура противоположного цвета
bool Figure::isAvailableSquare(Coordinates& tempCoord, Board& board) {
    if (board.map[tempCoord.y][tempCoord.x] == nullptr || this->isColorWhite() != board.map[tempCoord.y][tempCoord.x]->isColorWhite()) return true;
    else return false;
}

    // Вернуть цвет фигуры
bool Figure :: isColorWhite() const       {  return this->color;   }

