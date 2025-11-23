#include "CellPlayer.h"
#include <iostream>
#include <windows.h>
#include <process.h>
#include <string> 

int StatePlayer::get_hp() const { return hp; }
void StatePlayer::TakeDmg() { 
    hp -= 15;
    if(hp <= 0) {
          system("cls");
                std::cout << "\n\n\n";
             std::cout << " <><><><><><>\n";
            std::cout << "<><><><><>YOU LOOSE GAME, ZERO HP<><><><><> " << "\n";
                 std::cout << " <><><><><><>\n";
                Sleep(3000); 
                exit(0);
    }
} 
  const std::string& StatePlayer::get_name() const { return name_player; } 
   void StatePlayer::set_name(const std::string& str) { name_player = str; }