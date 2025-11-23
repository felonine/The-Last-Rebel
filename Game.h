#ifndef GAME_H
#define GAME_H
#include <vector>
#include "CellPlayer.h"
#include <string>
struct coords {
    int y{0}, x{0};
    char glyph{' '};
};

 class Game {
    int init_level{0};
    static constexpr int HEIGHT{10};
    static constexpr int WIDTH{20};
    char field[HEIGHT][WIDTH];
    std::vector<coords> player{{1,3}};
    std::vector<coords> portal{{HEIGHT / 2, WIDTH / 2}};
    std::vector<coords> traps;
    std::vector<coords> details;
    bool level_completed = false;
    public:
    Game() = default;
    explicit Game(const std::string& str) : user(str) {}
    StatePlayer user;
    void drawField();
    void Input();
    void RunSys();
    coords save_coords();
    void initLVL();
    int getLVL() const;
    void LegendCosmic() const ;
    void spawn_elements(int count_details);
    void spawn_traps(int count_traps);
    void moveTraps();
 };


#endif