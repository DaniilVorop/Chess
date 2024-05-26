//
// Created by vorop on 24.10.2023.
//

#include <fstream>
#include "Board.h"

void Board::drawBoard(sf::RenderWindow& window) {       // Отрисовка шахматной доски и фигур
    window.draw(texture.board);                         // Отрисовка шахматной доски
    for (short int i = 0; i < SIZEBOARD; i++) {         // Координата по y
        for (short int j = 0; j < SIZEBOARD; j++) {     // Координата по х
            if (map[i][j] == nullptr) {     // Если клетка пустая, то перехожу к след клетки, иначе определяю тип фигуры и ее цвет
                continue;
            } else if (map[i][j]->getType() == TypeFigure::Pawn && !map[i][j]->isColorWhite()) {
                texture.pawnD.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.pawnD);
            } else if (map[i][j]->getType() == TypeFigure::Pawn && map[i][j]->isColorWhite()) {
                texture.pawnW.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.pawnW);
            } else if (map[i][j]->getType() == TypeFigure::Bishop && !map[i][j]->isColorWhite()) {
                texture.bishopD.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.bishopD);
            } else if (map[i][j]->getType() == TypeFigure::Bishop && map[i][j]->isColorWhite()) {
                texture.bishopW.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.bishopW);
            } else if (map[i][j]->getType() == TypeFigure::Knight && !map[i][j]->isColorWhite()) {
                texture.knightD.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.knightD);
            } else if (map[i][j]->getType() == TypeFigure::Knight && map[i][j]->isColorWhite()) {
                texture.knightW.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.knightW);
            } else if (map[i][j]->getType() == TypeFigure::Rook && !map[i][j]->isColorWhite()) {
                texture.rookD.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.rookD);
            } else if (map[i][j]->getType() == TypeFigure::Rook && map[i][j]->isColorWhite()) {
                texture.rookW.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.rookW);
            } else if (map[i][j]->getType() == TypeFigure::Queen && !map[i][j]->isColorWhite()) {
                texture.queenD.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.queenD);
            } else if (map[i][j]->getType() == TypeFigure::Queen && map[i][j]->isColorWhite()) {
                texture.queenW.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.queenW);
            } else if (map[i][j]->getType() == TypeFigure::King && !map[i][j]->isColorWhite()) {
                texture.kingD.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.kingD);
            } else if (map[i][j]->getType() == TypeFigure::King && map[i][j]->isColorWhite()) {
                texture.kingW.setPosition(static_cast<float>(marginLeft + j * sizeBox), static_cast<float>(marginUp + i * sizeBox) );
                window.draw(texture.kingW);
            }
        }
    }
}
            // Нарисовать доступные ходы и взятия
void Board::drawAvailableMove(sf::RenderWindow& window, const std::vector<Coordinates>& availableMove) {
    for(Coordinates coord : availableMove) {        // Координаты, на которые могу ходить
        if (map[coord.y][coord.x] == nullptr) {     // Если клетка пустая, рисую круг хода
            texture.move.setPosition(static_cast<float>(marginLeft + coord.x * sizeBox), static_cast<float>(marginUp + coord.y * sizeBox));
            window.draw(texture.move);
        }
        else {                                      // Если клетка не пустая, рисую круг взятия
            texture.hit.setPosition(static_cast<float>(marginLeft + coord.x * sizeBox), static_cast<float>(marginUp + coord.y * sizeBox));
            window.draw(texture.hit);
        }
    }
}

        // Проверка на мат и ничью
short int Board::checkOnMate() {
    if (this->checkOnDraw()) {      //  Проверка на ничью
        this->setStateGame(StateGame::Draw);
        return 1;                   // ничья
    }
    for (short int y = 0; y < SIZEBOARD; y++)       // Цикл по всей доске с получением доступных ходов
        for (short int x = 0; x < SIZEBOARD; x++)
            if (map[y][x] != nullptr && map[y][x]->isColorWhite() == this->itWhiteMoveNow())
                if (!map[y][x]->getAvailableMoveSquares(*this, true).empty())
                    return 0;                                   // Если есть доступный ход, то возвращаю 0

    if (this->itWhiteMoveNow()) {                   // Проверка на то, угрожают ли королю
        if (map[whiteKingCoord.y][whiteKingCoord.x]->testOnCheck(whiteKingCoord, *this, this->itWhiteMoveNow())) {
            setStateGame(StateGame::Draw);
            std::cout << "Pat!";
            return 1;                   // Если королю никто не угрожает, то Пат
        }
    } else if (map[darkKingCoord.y][darkKingCoord.x]->testOnCheck(darkKingCoord, *this, this->itWhiteMoveNow())) {
        std::cout << "Pat!";
        this->setStateGame(StateGame::Draw);
        return 1;                       // Если королю никто не угрожает, то Пат
    }
    std::cout << "Mat";
    if (itWhiteMoveNow())        // Если сейчас ход белых,нет доступных ходов и королю угрожают, то победили черные, иначе белые
        this->setStateGame(StateGame::BlackWin);
    else this->setStateGame(StateGame::WhiteWin);
    return 2;                           // Мат
}

        // Перемещение фигуры, на шахматной доске
void Board::move(Coordinates& oldCoord, Coordinates& newCoord) {
    this->addFenInDeq(this->generationFenString());
    this->changeSpecialCondition(oldCoord,newCoord);   // Меняю специальное состояние фигур, если необходимо

    if (map[oldCoord.y][oldCoord.x]->getType() ==
        TypeFigure::King) {        // Если хожу королем, то меняю его координаты в Board
        changeCoordinatesKing(oldCoord, newCoord);
        if (abs(newCoord.x - oldCoord.x) == 2)      // Проверка на рокировку
            this->castling(oldCoord, newCoord);
    }
    else if (map[oldCoord.y][oldCoord.x]->getType() == TypeFigure::Pawn) {
        if (map[newCoord.y][newCoord.x] == nullptr &&
            oldCoord.x != newCoord.x) {             // Проверка если это было взятие на проходе
            captureEnPassant(oldCoord, newCoord);
        }
    }

    if (map[newCoord.y][newCoord.x] != nullptr)     // Очистка новой координаты
        delete map[newCoord.y][newCoord.x];
    map[newCoord.y][newCoord.x] = map[oldCoord.y][oldCoord.x];  // Перемещение фигуры
    map[newCoord.y][newCoord.x]->setCoordinates(newCoord);      // Установка новых координат
    map[oldCoord.y][oldCoord.x] = nullptr;

    this->moveTransition();                         // Передача хода другому игроку
}

    // Реализует выбор фигуры при проходе пешки
void Board::pawnPromotion(sf::RenderWindow& window,Coordinates& coordinates) {      // Проход пешки
    drawBoard(window);                      // Отрисовать доску
    int y, x;
    if (coordinates.y == 0) {               // Белая фигура прошла
        y = static_cast<float>(marginUp);
        texture.promotion.setTexture(texture.promotionWhitePawnImg);     // Установка текстуры
    }
    else {                                   // черная фигура прошла
        y = (marginUp + (coordinates.y - 3) * sizeBox);
        texture.promotion.setTexture(texture.promotionBlackPawnImg);     // Установка текстуры
    }
    x = (coordinates.x * sizeBox + marginLeft);
    // Установка координат
    texture.promotion.setPosition(static_cast<float>(x), static_cast<float>(y));
    window.draw(texture.promotion);     // Отрисовка блока вывода
    window.display();
    //  выбор фигуры и замена
    sf::Event event{};
    while (window.waitEvent(event)) {           // Ожидание действия
        if(event.type == sf::Event::Closed)     // Если закрыли окно, закрываю программу
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed && // Если была нажата ЛКМ
            event.mouseButton.button == sf::Mouse::Left) {
                // Определение координаты нажатия
            if (event.mouseButton.x > x && event.mouseButton.x < x + sizeBox && event.mouseButton.y > y && event.mouseButton.y < y + 4 * sizeBox) {
                delete map[coordinates.y][coordinates.x];
                int numbFigure = (event.mouseButton.y - y) / sizeBox;
                switch (numbFigure) {       // Вид фигуры
                    case 0: map[coordinates.y][coordinates.x] = new Queen(!bool(coordinates.y) ,coordinates.y ,coordinates.x ,false); break;
                    case 1: map[coordinates.y][coordinates.x] = new Knight(!bool(coordinates.y) ,coordinates.y ,coordinates.x ,false); break;
                    case 2: map[coordinates.y][coordinates.x] = new Rook(!bool(coordinates.y) ,coordinates.y ,coordinates.x ,false); break;
                    case 3: map[coordinates.y][coordinates.x] = new Bishop(!bool(coordinates.y) ,coordinates.y ,coordinates.x ,false); break;
                }
                return;
            }
        }
    }
}
        // Взятие на проходе, удаляет взятую фигуры
void Board::captureEnPassant(Coordinates& oldCoord,Coordinates& newCoord){
    if (oldCoord.x > newCoord.x) {
        delete map[oldCoord.y][oldCoord.x - 1];
        map[oldCoord.y][oldCoord.x - 1] = nullptr;
    }
    else {
        delete map[oldCoord.y][oldCoord.x + 1];
        map[oldCoord.y][oldCoord.x + 1] = nullptr;
    }
}

    // Изменение координаты короля
void Board::changeCoordinatesKing(Coordinates& oldCoord, Coordinates& newCoord){
        if( map[oldCoord.y][oldCoord.x]->isColorWhite() )
            whiteKingCoord = newCoord;
        else
            darkKingCoord = newCoord;
}
    // меняю специальное состояние фигур
void Board::changeSpecialCondition(Coordinates& oldCoordinates,Coordinates& newCoordinates) {
    // Цикл по всей доске и изменение спец. состояния пешек на false
    for (int y = 0; y < SIZEBOARD; y++)
        for (int x = 0; x < SIZEBOARD; x++) {
            if (this->map[y][x] != nullptr && this->map[y][x]->getType() == TypeFigure::Pawn)
                map[y][x]->setSpecialCondition(false);
        }
    // Правило 50 ходов, если ходила пешка, или было взятие фигуры, то счетчик = 0
    if ( this->map[oldCoordinates.y][oldCoordinates.x]->getType() == TypeFigure::Pawn || this->map[newCoordinates.y][newCoordinates.x] != nullptr )
        this->count50moves = 0;
    else count50moves++;
    // увеличиваю кол-во ходов, когда ходят черные
    if ( !this->map[oldCoordinates.y][oldCoordinates.x]->isColorWhite() )
        numberOfMoves++;
    // Если ходила пешка, ставлю спец. состояние true
    // Если ходила ладья или король ставлю false
    switch (this->map[oldCoordinates.y][oldCoordinates.x]->getType()) {
        case TypeFigure::Pawn:
            if (abs(newCoordinates.y - oldCoordinates.y) == 2)
                map[oldCoordinates.y][oldCoordinates.x]->setSpecialCondition(true);
            break;
        case TypeFigure::Rook:
            map[oldCoordinates.y][oldCoordinates.x]->setSpecialCondition(false);
            break;
        case TypeFigure::King:
            map[oldCoordinates.y][oldCoordinates.x]->setSpecialCondition(false);
            break;
        default:
            break;
    }
}
    // Переставляю ладью при рокировке
void Board::castling(Coordinates& oldCoord, Coordinates& newCoord) {
    Coordinates newCoordRook{};
    Coordinates oldCoordRook{};
    if (newCoord.x > oldCoord.x) {
        newCoordRook = Coordinates(static_cast<short>(oldCoord.y), static_cast<short>(newCoord.x-1) );
        oldCoordRook = Coordinates(static_cast<short>(oldCoord.y), static_cast<short>(newCoord.x+1) );
    }
    else{
        newCoordRook = Coordinates(static_cast<short>(oldCoord.y), static_cast<short>(newCoord.x+1) );
        oldCoordRook = Coordinates(static_cast<short>(oldCoord.y), static_cast<short>(newCoord.x-2) );
    }
        // Меняю специальное состояние
    this->changeSpecialCondition(oldCoord,newCoord);
    // Переставляю ладью и изменяю ее координаты
    map[newCoordRook.y][newCoordRook.x] = map[oldCoordRook.y][oldCoordRook.x];
    map[newCoordRook.y][newCoordRook.x]->setCoordinates(newCoordRook);
    map[oldCoordRook.y][oldCoordRook.x] = nullptr;
}


std::string Board::generationFenString() const {
    std::string fen;                              // Итоговый fen
    std::string turnNow;                          // Кто сейчас ходит
    std::string availableCastling;                // Доступные рокировки
    std::string passableField("-");               // Проходимое поле

    int count = 0;
    for(int y = 0; y < SIZEBOARD; y++, count = 0)
        for(int x = 0; x < SIZEBOARD; x++) {
            if (this->map[y][x] != nullptr) {
                switch (this->map[y][x]->getType()) {

                    case TypeFigure::Pawn:
                        if (this->map[y][x]->isColorWhite())
                            fen += 'P';
                        else fen += 'p';
                        if ( this->map[y][x]->getSpecialCondition() ) { // координата проходной клетки
                            passableField = ('a' + x);        // буква проходной клетки
                            if (y == 4)                       // цифра проходной клетки
                                passableField += ('8' - y - 1);
                            else
                                passableField += ('8' - y + 1);
                        }
                        break;

                    case TypeFigure::Knight:
                        if (this->map[y][x]->isColorWhite())
                            fen += 'N';
                        else fen += 'n';
                        break;

                    case TypeFigure::Bishop:
                        if (this->map[y][x]->isColorWhite())
                            fen += 'B';
                        else fen += 'b';
                        break;

                    case TypeFigure::Rook:
                        if (this->map[y][x]->isColorWhite())
                            fen += 'R';
                        else fen += 'r';
                        break;

                    case TypeFigure::Queen:
                        if (this->map[y][x]->isColorWhite())
                            fen += 'Q';
                        else fen += 'q';
                        break;

                    case TypeFigure::King:
                        if (this->map[y][x]->isColorWhite())
                            fen += 'K';
                        else fen += 'k';
                        break;
                }
            }
            else {              // Если не фигура, увеличиваю кол-во пустых
                count++;
                if (x == 7 || this->map[y][x+1] != nullptr){
                    fen += '0' + count;
                    count = 0;
                }
            }
            if (x == 7 && y != 7)
                fen += '/';
        }
    // Ходят белые либо черные
    if (this->itWhiteMoveNow())
        turnNow = "w";
    else turnNow = "b";

    // AvailableCastling for white
    if (this->map[7][4] != nullptr && this->map[7][4]->getType() == TypeFigure::King && this->map[7][4]->getSpecialCondition() ){
        if (this->map[7][7] != nullptr && this->map[7][7]->getType() == TypeFigure::Rook && this->map[7][7]->getSpecialCondition())
            availableCastling = "K";
        else
            availableCastling = "-";
        if (this->map[7][0] != nullptr && this->map[7][0]->getType() == TypeFigure::Rook && this->map[7][0]->getSpecialCondition())
            availableCastling += "Q";
        else
            availableCastling += "-";
    }
    else availableCastling = "--";

    if (this->map[0][4] != nullptr && this->map[0][4]->getType() == TypeFigure::King && this->map[0][4]->getSpecialCondition() ){
        if (this->map[0][7] != nullptr && this->map[0][7]->getType() == TypeFigure::Rook && this->map[0][7]->getSpecialCondition())
            availableCastling += "k";
        else
            availableCastling += "-";
        if (this->map[0][0] != nullptr && this->map[0][0]->getType() == TypeFigure::Rook && this->map[0][0]->getSpecialCondition())
            availableCastling += "q";
        else
            availableCastling += "-";
    }
    else availableCastling += "--";
    fen += ' ' + turnNow + ' ' + availableCastling + ' ' + passableField + ' ' + std::to_string(count50moves) + ' ' + std::to_string(numberOfMoves) + '\n';
    return fen;
}

    // Добавление FEN в Дек
void Board::addFenInDeq(const std::string& fen) {
    dequeFen.push_back(fen);
}

    // Извлечь FEN из конца дека
std::string Board::extractFenOfEndDeq() {
    std::string fen = dequeFen.back();
    dequeFen.pop_back();
    return fen;
}
    // Извлечь FEN из начала дека
std::string Board::extractFenOfBeginDeq() {
    std::string fen = dequeFen.front();
    dequeFen.pop_front();
    return fen;
}

    // Установк доски исходя из FEN
void Board::setBoardByFen(std::string fen) {
    short int y, x;
    int index = 0;
    for (y = 0; y < SIZEBOARD; y++)     // Очистка доски
        for (x = 0; x < SIZEBOARD; x++)
            if (this->map[y][x] != nullptr){
                delete map[y][x];
                map[y][x] = nullptr;
            }
    y = 0;  x = 0;
    for (index = 0; y < 8; index++) {   // Заполнение позиций
        switch (fen[index]) {
            case 'p':
                this->map[y][x] = new Pawn(false, y, x, false);
                x++;
                break;
            case 'r':
                this->map[y][x] = new Rook(false, y, x, false);
                x++;
                break;
            case 'n':
                this->map[y][x] = new Knight(false, y, x, false);
                x++;
                break;
            case 'b':
                this->map[y][x] = new Bishop(false, y, x, false);
                x++;
                break;
            case 'q':
                this->map[y][x] = new Queen(false, y, x, false);
                x++;
                break;
            case 'k':
                this->map[y][x] = new King(false, y, x, false);
                darkKingCoord.y = y;
                darkKingCoord.x = x;
                x++;

                break;
            case 'P':
                this->map[y][x] = new Pawn(true, y, x, false);
                x++;
                break;
            case 'R':
                this->map[y][x] = new Rook(true, y, x, false);
                x++;
                break;
            case 'N':
                this->map[y][x] = new Knight(true, y, x, false);
                x++;
                break;
            case 'B':
                this->map[y][x] = new Bishop(true, y, x, false);
                x++;
                break;
            case 'Q':
                this->map[y][x] = new Queen(true, y, x, false);
                x++;
                break;
            case 'K':
                this->map[y][x] = new King(true, y, x, false);
                whiteKingCoord.y = y;
                whiteKingCoord.x = x;
                x++;
                break;
            case '/':
                y++;
                x = 0;
                break;
            case ' ':
                y = 8;
                break;
            default:
                if (fen[index] < '9' && fen[index] > '0')
                    x += fen[index] - '0';  // Пропуск пустых клеток
        }
    }

    if (fen[index] == 'w')        // Ход белых либо черных
        whiteMoveNow = true;
    else whiteMoveNow = false;
    index += 2;                     // Рокировка белых
    if (fen[index++] == 'K') {
        this->map[whiteKingCoord.y][whiteKingCoord.x]->setSpecialCondition(true);
        this->map[7][7]->setSpecialCondition(true);
    }
    if (fen[index++] == 'Q') {
        this->map[whiteKingCoord.y][whiteKingCoord.x]->setSpecialCondition(true);
        this->map[7][0]->setSpecialCondition(true);
    }
    if (fen[index++] == 'k') {
        this->map[darkKingCoord.y][darkKingCoord.x]->setSpecialCondition(true);
        this->map[0][7]->setSpecialCondition(true);
    }
    if (fen[index++] == 'q') {
        this->map[darkKingCoord.y][darkKingCoord.x]->setSpecialCondition(true);
        this->map[0][0]->setSpecialCondition(true);
    }
    ++index;
    if (fen[index] <= 'h' && fen[index] >= 'a'){           //  взятие на проходе
        x = fen[index] - 'a';
        y = '8' - fen[++index];
        if (y == 2) y++;
        else if (y == 5) y--;
        this->map[y][x]->setSpecialCondition(true);
    }
    index += 2;
    if (fen[index + 1] != ' ')      // Правило 50ти полу-ходов
        count50moves = (fen[index] - '0') * 10 + ( fen[++index] - '0' );
    else count50moves = fen[index] - '0';
    index +=2;
    int i;                          // Общее кол-во ходов
    for(i = 1; fen[index + i] <= '9' && fen[index + i] >= '0'; i++);
    numberOfMoves = stoi(fen.substr(index,index + i - 1) );
}

bool Board::checkOnDraw() {         // Проверка на ничью:
                                    // Троекратное повторение позиции; 50 ходов без улучшения позиции;
                                    // Король и король+одна лёгкая фигура (конь/слон); Король и король+конь+конь; Король+король
    if (count50moves >= 50)
        return true;
    bool knightW{false};
    bool knightD{false};
    bool bishopW{false};
    bool bishopD{false};
    for (int y = 0; y < SIZEBOARD; y++)
        for (int x = 0; x < SIZEBOARD; x++)
            if (this->map[y][x] != nullptr) {
                switch (this->map[y][x]->getType()) {
                    case TypeFigure::Pawn:
                        return false;
                    case TypeFigure::Knight:
                        if (this->map[y][x]->isColorWhite()) knightW = true;
                        else knightD = true;
                        break;
                    case TypeFigure::Bishop:                    // Если две ладьи, то false
                        if (this->map[y][x]->isColorWhite()) {
                            if (bishopW)
                                return false;
                            else bishopW = true;
                        }
                        else {
                            if (bishopD)
                                return false;
                            else bishopD = true;
                        }
                        break;
                    case TypeFigure::Rook:
                        return false;
                    case TypeFigure::Queen:
                        return false;
                    case TypeFigure::King:
                        break;
                }
            }
    if ( ( (knightW || bishopW) && (knightD || bishopD) ) || (knightW && bishopW) || (knightD && bishopD) )
        return false;
    return true;
}
    // Деструктор очистки доски
Board::~Board() {
    this->clearBoard();
    this->dequeFen.clear();
}

    // Шаг назад, откат дека
void Board::stepBack() {
    if (this->deqFenSize() == 0)
        return;
    this->setBoardByFen(this->extractFenOfEndDeq());
}
    // Сдаться, присвоение победы
void Board::giveUp() {
    if (this->itWhiteMoveNow())
        this->setStateGame(StateGame::BlackWin);
    else
        this->setStateGame(StateGame::WhiteWin);
}
    // Очистка доски
void Board::clearBoard() {
    for (int y = 0; y < SIZEBOARD; y++)
        for (int x = 0; x < SIZEBOARD; x++)
            if (map[y][x] != nullptr){
                delete map[y][x];
                map[y][x] = nullptr;
            }
    // Очистка дека
    while(this->deqFenSize())
        this->extractFenOfEndDeq();
}

void Board::writeDeqInFile(std::ofstream& fileName) const {
        for(const auto & i : this->dequeFen)
            fileName << i;
    fileName << generationFenString();
}
