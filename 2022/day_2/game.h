#ifndef GAME_H
#define GAME_H

#include <string>

namespace NamespaceGame {

    class Game {
        int mod_result=0;

    public:
        int calculate( std::string opponent, std::string me);
        int reverse_calculate( std::string opponentm, std::string outcome);

    private:
        // Not needed, but to try out private functions
        int modulus( int first, int second);

    }; // class Game

} // namespace game

#endif // GAME_H
