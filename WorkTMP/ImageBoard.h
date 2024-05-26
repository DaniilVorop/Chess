//
// Created by vorop on 26.10.2023.
//
#ifndef COURSEWORK_IMAGEBOARD_H
#define COURSEWORK_IMAGEBOARD_H
#include <SFML/Graphics.hpp>

class ImageBoard{               // Класс изображений доски
private:
    sf::Texture boardImg, pawnDImg, knightDImg, bishopDImg, rookDImg,queenDImg,kingDImg,    // Текстуры
    pawnWImg, knightWImg, bishopWImg, rookWImg, queenWImg, kingWImg, moveImg, hitImg;
    bool blackStyle;
public:
    sf::Texture promotionWhitePawnImg, promotionBlackPawnImg;
    sf::Sprite board, pawnD, knightD, bishopD, rookD, queenD, kingD,          // Спрайты
    pawnW, knightW, bishopW, rookW, queenW, kingW,move,hit, promotion;
    ImageBoard(){                                           // Загрузка изображений и установка в спрайты
        blackStyle = true;
        boardImg.loadFromFile("image/chessBoardDarkStyle.png");

        promotionBlackPawnImg.loadFromFile("image/blackPromotionDarkStyle.png");
        promotionWhitePawnImg.loadFromFile("image/whitePromotionDarkStyle.png");

        pawnDImg.loadFromFile("image/pawnD.png");
        pawnWImg.loadFromFile("image/pawnW.png");

        knightDImg.loadFromFile("image/knightD.png");
        knightWImg.loadFromFile("image/knightW.png");

        bishopDImg.loadFromFile("image/bishopD.png");
        bishopWImg.loadFromFile("image/bishopW.png");

        rookDImg.loadFromFile("image/rookD.png");
        rookWImg.loadFromFile("image/rookW.png");

        queenDImg.loadFromFile("image/queenD.png");
        queenWImg.loadFromFile("image/queenW.png");

        kingDImg.loadFromFile("image/kingD.png");
        kingWImg.loadFromFile("image/kingW.png");

        moveImg.loadFromFile("image/move.png");
        hitImg.loadFromFile("image/hit.png");

        board.setTexture(boardImg);

        pawnW.setTexture(pawnWImg);
        pawnD.setTexture(pawnDImg);

        knightW.setTexture(knightWImg);
        knightD.setTexture(knightDImg);

        bishopW.setTexture(bishopWImg);
        bishopD.setTexture(bishopDImg);

        rookW.setTexture(rookWImg);
        rookD.setTexture(rookDImg);

        queenW.setTexture(queenWImg);
        queenD.setTexture(queenDImg);

        kingW.setTexture(kingWImg);
        kingD.setTexture(kingDImg);

        move.setTexture(moveImg);
        hit.setTexture(hitImg);

        board.setPosition(0,0);
    }
    void changeStyle(){
        if (blackStyle){
            boardImg.loadFromFile("image/chessBoardWhiteStyle.png");

            promotionBlackPawnImg.loadFromFile("image/blackPromotionWhiteStyle.png");
            promotionWhitePawnImg.loadFromFile("image/whitePromotionWhiteStyle.png");
        }
        else{
            boardImg.loadFromFile("image/chessBoardDarkStyle.png");

            promotionBlackPawnImg.loadFromFile("image/blackPromotionDarkStyle.png");
            promotionWhitePawnImg.loadFromFile("image/whitePromotionDarkStyle.png");
        }
        blackStyle = !blackStyle;
    }
};

#endif //COURSEWORK_IMAGEBOARD_H
