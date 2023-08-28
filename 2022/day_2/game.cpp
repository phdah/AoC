#include "game.h"
#include <iostream>

constexpr int num_plays=3;
namespace NamespaceGame {

    int Game::calculate( std::string opponent, std::string me) {
        int opponent_play = static_cast<int>(opponent[0])-65;
        int my_play = static_cast<int>(me[0])-65-23;
        int winner;

        if ( opponent_play == my_play ) {
            winner = 3;
        }
        else {
            // opponent winner
            if ( modulus(my_play+1, num_plays) == opponent_play ) {
                winner = 0;
            }
            // I'm winner
            else {
                winner = 6;
            }

        }

        return my_play+1 + winner;
    }

    int Game::reverse_calculate( std::string opponent, std::string outcome) {
        int opponent_play = static_cast<int>(opponent[0])-65;
        int winner = (static_cast<int>(outcome[0])-65-23)*3;

        int my_play;
        // I'm winner
        if ( winner == 6 ) {
            my_play = modulus(opponent_play+1, num_plays);
        }
        // opponent winner
        else if ( winner == 0 ) {
            my_play = modulus(opponent_play+2, num_plays);
        }
        else {
            my_play = opponent_play;
        }

        return my_play+1 + winner;
    }

    int Game::modulus( int first, int second) {
        if ( second == 0 ) {
            std::cerr << "Division by zero, not possible to do: x % 0" << std::endl;
            return 1;
        }
        this->mod_result = first % second; // just to try out `this`

        return this->mod_result;
    }

} // namespace game
