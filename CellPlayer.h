#ifndef CELLPLAYER_H
#define CELLPLAYER_H
#include <string>
class StatePlayer {
    std::string name_player;
    int hp{100};
    public:
    StatePlayer() = default;
    explicit StatePlayer(const std::string& str) noexcept : name_player(str) {}
    int get_hp() const;
    void TakeDmg();
    const std::string& get_name() const;
    void set_name(const std::string&);
};


#endif