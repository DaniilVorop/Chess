//
// Created by vorop on 09.12.2023.
//

#ifndef COURSEWORK_IMAGEMENU_H
#define COURSEWORK_IMAGEMENU_H
#include <SFML/Graphics.hpp>

class ImageMenu{                // Класс изображений меню
private:
    sf::Texture startMenuImg, sidebarInProcessWatchImg, confirmationImg, inputFileNameImg,
    chooseHostOrClientImg, waitConnectionImg, inputIpImg; // текстуры
    bool blackStyle;
public:
    sf::Texture sidebarInProcessGameOnlineImg,sidebarInProcessGameImg, sidebarEndGameImg, sidebarEndGameOnlineImg;
    sf::Font fontInput,fontPlayer;                                                                      // Шрифт
    sf::Image icon;                                                                     // Иконка
    sf::Text playerText, white,black, ipAddress, resultGame, nowMove;                                       // Текст
    sf::Sprite startMenu, sidebarInProcessGame, sidebarInProcessWatch,                    // Спрайты
    confirmation, inputFileName, sidebarEndGame,  chooseHostOrClient, waitConnection, inputIp;

    ImageMenu(){                                       // Загрузка, установка изображений и координат
        blackStyle = true;
        icon.loadFromFile("image/icon.png");
        fontInput.loadFromFile("image/font/arial_bolditalicmt.ttf");
        fontPlayer.loadFromFile("image/font/ofont.ru_Open Sans.ttf");

        playerText.setFont(fontInput);
        playerText.setCharacterSize(24);
        playerText.setFillColor(sf::Color::Black);

        ipAddress.setFont(fontInput);
        ipAddress.setCharacterSize(23);
        ipAddress.setFillColor(sf::Color::Black);

        resultGame.setFont(fontInput);
        resultGame.setCharacterSize(23);
        resultGame.setFillColor(sf::Color::Black);

        white.setFont(fontPlayer);
        white.setCharacterSize(23);
        white.setFillColor(sf::Color::White);

        nowMove.setFont(fontPlayer);
        nowMove.setCharacterSize(22);
        nowMove.setFillColor(sf::Color::Black);

        black.setFont(fontPlayer);
        black.setCharacterSize(23);
        black.setFillColor(sf::Color::Black);

        startMenuImg.loadFromFile("image/startMenuDarkStyle.png");

        sidebarInProcessGameImg.loadFromFile("image/sidebarInProcessGameDarkStyle.png");
        sidebarEndGameImg.loadFromFile("image/sidebarEndGameDarkStyle.png");
        sidebarInProcessWatchImg.loadFromFile("image/sidebarInProcessWatchDarkStyle.png");
        confirmationImg.loadFromFile("image/confirmationDarkStyle.png");
        inputFileNameImg.loadFromFile("image/inputFileNameDarkStyle.png");


        chooseHostOrClientImg.loadFromFile("image/chooseHostOrClientDarkStyle.png");
        waitConnectionImg.loadFromFile("image/waitConnectionDarkStyle.png");
        inputIpImg.loadFromFile("image/inputIpDarkStyle.png");

        sidebarInProcessGameOnlineImg.loadFromFile("image/sidebarInProcessGameOnlineDarkStyle.png");
        sidebarEndGameOnlineImg.loadFromFile("image/sidebarEndGameOnlineDarkStyle.png");


        startMenu.setTexture(startMenuImg);
        sidebarInProcessWatch.setTexture(sidebarInProcessWatchImg);
        confirmation.setTexture(confirmationImg);
        inputFileName.setTexture(inputFileNameImg);
        sidebarInProcessGame.setTexture(sidebarInProcessGameImg);
        sidebarEndGame.setTexture(sidebarEndGameImg);

        chooseHostOrClient.setTexture(chooseHostOrClientImg);
        waitConnection.setTexture(waitConnectionImg);
        inputIp.setTexture(inputIpImg);

        startMenu.setPosition(-4,0);
        sidebarInProcessWatch.setPosition(920,0);
        sidebarEndGame.setPosition(920, 0);
        sidebarInProcessGame.setPosition(920, 0);
        confirmation.setPosition(0,0);
        inputFileName.setPosition(0,0);
        chooseHostOrClient.setPosition(0,0);
        waitConnection.setPosition(0,0);
        inputIp.setPosition(0,0);

        playerText.setPosition(465,458);
        ipAddress.setPosition(465,458);
        nowMove.setPosition(993, 173);
        resultGame.setPosition(1010,200);
    }

    void changeStyle(){
        if (blackStyle){
            startMenuImg.loadFromFile("image/startMenuWhiteStyle.png");
            sidebarInProcessGameImg.loadFromFile("image/sidebarInProcessGameWhiteStyle.png");
            sidebarEndGameImg.loadFromFile("image/sidebarEndGameWhiteStyle.png");
            sidebarInProcessWatchImg.loadFromFile("image/sidebarInProcessWatchWhiteStyle.png");
            confirmationImg.loadFromFile("image/confirmationWhiteStyle.png");
            inputFileNameImg.loadFromFile("image/inputFileNameWhiteStyle.png");

            chooseHostOrClientImg.loadFromFile("image/chooseHostOrClientWhiteStyle.png");
            waitConnectionImg.loadFromFile("image/waitConnectionWhiteStyle.png");
            inputIpImg.loadFromFile("image/inputIpWhiteStyle.png");

            sidebarInProcessGameOnlineImg.loadFromFile("image/sidebarInProcessGameOnlineWhiteStyle.png");
            sidebarEndGameOnlineImg.loadFromFile("image/sidebarEndGameOnlineWhiteStyle.png");

        }
        else{
            startMenuImg.loadFromFile("image/startMenuDarkStyle.png");
            sidebarInProcessGameImg.loadFromFile("image/sidebarInProcessGameDarkStyle.png");
            sidebarEndGameImg.loadFromFile("image/sidebarEndGameDarkStyle.png");
            sidebarInProcessWatchImg.loadFromFile("image/sidebarInProcessWatchDarkStyle.png");
            confirmationImg.loadFromFile("image/confirmationDarkStyle.png");
            inputFileNameImg.loadFromFile("image/inputFileNameDarkStyle.png");

            chooseHostOrClientImg.loadFromFile("image/chooseHostOrClientDarkStyle.png");
            waitConnectionImg.loadFromFile("image/waitConnectionDarkStyle.png");
            inputIpImg.loadFromFile("image/inputIpDarkStyle.png");

            sidebarInProcessGameOnlineImg.loadFromFile("image/sidebarInProcessGameOnlineDarkStyle.png");
            sidebarEndGameOnlineImg.loadFromFile("image/sidebarEndGameOnlineDarkStyle.png");

        }
        blackStyle = !blackStyle;
    }
};

#endif //COURSEWORK_IMAGEMENU_H
