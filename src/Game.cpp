#include "Game.hpp"

Game::Game()
{
    /*
        0x1 - zero
        0x2 - cross
    */

    currentPlayer_ = 0x2;

    playboard_ = new int*[3];

    for (int i(0); i < 3; i++) {
        playboard_[i] = new int;
    }

    ClearBoard();
}

Game::~Game()
{
    if (playboard_) {
        for (int i(0); i < 3; i++) {
            delete[] playboard_[i];
        }
    }
}

void Game::Start()
{
    if (amountMoves != 0) {
        ClearBoard();
    }

    while (true) {
        PrintBoard();
        Move();

        if (isWin() != 0x3) {
            break;
        }
    }

    PrintBoard();
    PrintResult();
}

void Game::PrintBoard()
{
    system("clear");

    int counter = 1;

    if (playboard_) {
        for (int i(0); i < 3; i++) {
            std::cout << "| ";
            for (int j(0); j < 3; j++) {
                switch (playboard_[i][j]) {
                case 0x1:
                    std::cout << "O | ";
                    break;
                case 0x2:
                    std::cout << "X | ";
                    break;
                default:
                    std::cout << counter << " | ";
                    break;
                }

                counter++;
            }
            std::cout << std::endl;
        }
    } else {
        throw "THE_BOARD_DOES_NOT_EXIST";
    }
}

void Game::ClearBoard()
{
    if (playboard_) {
        for (int i(0); i < 3; i++) {
            for (int j(0); j < 3; j++) {
                playboard_[i][j] = 0x0;
            }
        }

        amountMoves = 0;
    } else {
        throw "THE_BOARD_DOES_NOT_EXIST";
    }
}

int Game::isWin()
{
    /*
        0x0 - draw
        0x1 - zero
        0x2 - cross
        0x3 - the play is continuing;
    */

    if (amountMoves < 5) {
        return 0x3;
    } else if (amountMoves == 9) {
        return 0x0;
    }

    if (CheckLines()) {
        return currentPlayer_;
    }

    return 0x3;
}

bool Game::CheckLines()
{
    for (int i(0); i < 3; i++) {
        if (playboard_[0][i] == currentPlayer_ && playboard_[1][i] == currentPlayer_ && playboard_[2][i] == currentPlayer_) {
            return true;
        } else if (playboard_[i][0] == currentPlayer_ && playboard_[i][1] == currentPlayer_ && playboard_[i][2] == currentPlayer_) {
            return true;
        }
    }

    if (playboard_[0][0] == currentPlayer_ && playboard_[1][1] == currentPlayer_ && playboard_[2][2] == currentPlayer_) {
        return true;
    } else if (playboard_[0][2] == currentPlayer_ && playboard_[1][1] == currentPlayer_ && playboard_[2][0] == currentPlayer_) {
        return true;
    }

    return false;
}

void Game::PrintResult()
{
    switch (currentPlayer_) {
    case 0x1:
        std::cout << "Выиграли нолики!" << std::endl;
        break;
    case 0x2:
        std::cout << "Выиграли крестики!" << std::endl;
        break;
    default:
        std::cout << "Упс! Ничья!" << std::endl;
        break;
    }

    std::cout << "Игра окончена!" << std::endl;
}

void Game::Move()
{
    currentPlayer_ = currentPlayer_ == 0x1 ? 0x2 : 0x1;

repeatForIdiots:
    std::cout << "Текущий ход ";

    if (currentPlayer_ == 0x1) {
        std::cout << " ноликов: ";
    } else {
        std::cout << " крестиков: ";
    }

    if (CheckMove() == 0x0) {
        std::cout << "Некорректный ввод данных! Пожалуйста, повторите попытку ввода!" << std::endl;
        goto repeatForIdiots;
    }

    amountMoves++;
}

int Game::CheckMove()
{
    int movePosition = 0;
    std::cin >> movePosition;

    if (std::cin.fail() || (movePosition - 1) < 0 || (movePosition - 1) >= 9) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0x0;
    } else {
        absolutlyPosition = getApsolutlyPosition(&movePosition);

        if (playboard_[absolutlyPosition.first][absolutlyPosition.second] != 0x0) {
            return 0x0;
        } else {
            playboard_[absolutlyPosition.first][absolutlyPosition.second] = currentPlayer_;
            return 0x1;
        }
    }

    return 0x0;
}

std::pair<std::size_t, std::size_t> Game::getApsolutlyPosition(int* movePosition)
{
    size_t _x = (*movePosition);
    size_t _y = 0;

    if ((*movePosition) > 3 && (*movePosition) <= 6) {
        _y = 1;
    } else if ((*movePosition) > 6) {
        _y = 2;
    }

    if (_y == 1) {
        _x = (*movePosition) - 3;
    } else if (_y == 2) {
        _x = (*movePosition) - 3 * 2;
    }

    return { _y, _x - 1 };
}