#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

class Game {
public:
    Game();
    ~Game();

    void Start(); // Start to play the game

protected:
    int isWin(); // The function of checking the end of the game
    bool CheckLines(); // The function of checking each lines of the board for the end of the game

    void PrintBoard(); // The function of printing the board of the game to the display
    void ClearBoard(); // The function of resetting values of the board

    void PrintResult(int*); // The function of printing the result of the game

    void Move(); // The function that gives the player to get move
    int CheckMove(); // The function of checking the right move

    std::pair<std::size_t, std::size_t> getAbsolutelyPosition(int*); // The function of returning the position of the board

protected:
    int** playboard_; // The playboard
    int currentPlayer_; // The current player
    int amountMoves; // Amount of moves in the game

    std::pair<std::size_t, std::size_t> absolutelyPosition; // The absolutly position
};

#endif