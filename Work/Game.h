//
// Created by vorop on 02.11.2023.
//

#ifndef COURSEWORK_GAME_H
#define COURSEWORK_GAME_H
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "iostream"
#include "StockFish.h"
#include "Network.h"
#include <fstream>
#include <thread>
#include "ImageMenu.h"
#include <condition_variable>
//#include <arpa/inet.h>
//#include <sys/socket.h>
#include "pthread.h"
#include <csignal>
#include <atomic>
#include <mutex>

class Game {
private:
    Board board;                                        // game board
    StockFish stockFish;                                // play with computer
    bool colorPlayer1IsWhite{true};
    bool colorPlayer2IsWhite{false};                  // or computer
    sf::RenderWindow window;                            // окно приложения
    sf::Event event{};                                    // Обработчик событий
    ImageMenu texture;                                  // изображения
    bool opponentComputer{};                            // установка компьютера соперником
    Network network;
    std::mutex mutex;
public:
    void start();                                       // начало игры
    Game() = default;
    ~Game();
private:
    void newGameWithComputer();                         // начать новую игру с компьютером
    void newGameWithFriend();                           // начать новую игру с другим игроком
    void newOnlineGame();
    void restoreGameWithFriend();                       // восстановить игру с игроком
    void restoreGameWithComputer();                     // восстановить игру с компьютером
    void processWatchGame();                            // просмотр сохраненных игр

    void changeStyle();                                 // Change white or dark style


    void processGameWithFriend();                       // Цикл игры с игроком
    void processGameWithComputer();                     // цикл игры с компьютером
    void processNetworkGame(NetworkClient typeClient, std::atomic<bool>* newMsg);

    void movePlayer();                                  // получение хода от игрока
    bool saveOrReturnGame(bool saveGame);               // сохранение/восстановление игры с файла
    bool endGame();                                     // окончание игры
    void stepBack();                                    // отмена хода

    void drawStartMenu();                               // отрисовка стартового меню
    void drawGame();                                    // Отрисовка в процессе игры

    bool writeInFile(std::string& nameFile);            // запись в файл истории игры
    bool readFromFile(std::string& nameFile);           // чтение из файла истории игры

    SelectStartMenu getCoordinatesClickStartMenu() const;   // получение координат нажатия игрока
    bool getCoordinatesPressedBox(Coordinates& coordinates) const;  // получение координат нажатой клетки
    bool clickSidebar();                                 // нажатие на боковое меню в процессе игры
    SidebarForWatch clickSidebarForWatch() const;       // нажатие на поковое меню в процессе просмотра игр
    ClickToSaveOrReturnFile clickToInputString();          // ввод и сохранение файла
    bool confirmation();                                // подтверждение действия


    void setDifficultyBot(int diff);                    // установить уровень игры компьютера
    void getMoveComputer(Coordinates& oldCoord, Coordinates& newCoord); // получение хода от компьютера
    void moveComputer();                                // ход компьютера
    bool waitClick();                                   // ожидание нажатия Левой кнопки мыши

    NetworkClient selectTypeClient();
    bool waitConnect(const int *result);

    void playerAction(NetworkClient typeClient, std::atomic<bool>* newMsg);
    void opponentAction(NetworkClient typeClient,std::atomic<bool>* newMsg);
    ActionInternetOpponent waitOpponentAction(std::atomic<bool> *newMsg, char *msg) const;

    bool clickSidebarInNetworkGame(NetworkClient typeClient);
    bool waitClickWithRefresh(std::atomic<bool>* newMsg);
    void endNetworkGame();
    bool setConnection();
    bool inputServerIp(std::string* ipAddress);
};


#endif //COURSEWORK_GAME_H
