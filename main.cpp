#include <iostream>
#include "Game.h"
#include <ctime>
#include <string> 
#include <windows.h>
#include <iomanip>
  int main() { 
    srand(time(nullptr));
    std::string str;
    std::cout << "* . . . * . . * . . . . *\n";
  std::cout << "  _ _ . . . . * . . * . .\n";
 std::cout <<"  ( . . )  . . . . . . . . .\n";
  std::cout <<" (   _  ) . . . @ . . <--> . . .\n";
  std::cout <<"  | _  /  . . .||. . . . <^ | > . . .\n";
  std::cout << "  | _/  .. . . || . . . .\n";
 std::cout << ". |_/ . . . . .|| . .  . . . .\n";
    Sleep(7000);   
          system("cls"); 
        std::cout << "complete silence, disappointment, you, an alien planet, and your broken ship...\n";
        Sleep(4000);
     system("cls"); 
       std::cout << std::setw(4) << "SURVIVE\n"; 
       std::cout << "load game...\n";
       Sleep(1400);
       system("cls");
  std::cout << "Hello, write your id(nickname):\n";
  std::cin >> str;
  std::cout << "Okay, your ID : " << str << "\n" << " Right || No? \n";
  std::string answer;
  std::cin >> answer;
Game g1(str);
  if(answer == "yes" || answer == "YES" || answer == "y" ) {
g1.RunSys();
  } else if(answer == "N" || answer == "no" || answer == "n") {
    std::cout << "Well, edit ur name... \n";
    std::cin >> str;
    g1.user.set_name(str);
    g1.RunSys();
  }
  else 
  {
    std::cout << "\n\n\n" << " PLZ WRITE Y OR N! exiting... \n";
  }
    
    return 0;
  }