#include <iostream>
#include "Game.h"
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <process.h>
const char details_glyphs[] = {'&', '<', '>', 'T', '/', '|'}; // массив для хранения ловушек, это все виды ловушек,
const int size_details = sizeof(details_glyphs)/sizeof(details_glyphs[0]); // размер массива путем вычисления на байты 
   void Game::drawField() { // метод для отрисовки поля
     for(int i = 0; i < HEIGHT; ++i) { 
            for(int j = 0; j < WIDTH; ++j) { 
                if(i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
                field[i][j] = '#'; // заполняем границы отмечая их 
                else 
                field[i][j] = '.'; // заполняем пустоту - полом .
            }
        }
         for(auto it = details.cbegin(); it != details.cend(); ++it) { 
             field[it->y][it->x] = it->glyph; // отрисовываем детали 
         }
           for(auto it = player.cbegin(); it != player.cend(); ++it) { 
              field[it->y][it->x] = 'p'; // отрисовываем самого игрока 
           } 
           for(const auto& p : portal) { 
              field[p.y][p.x] = '@'; // отрисовываю портал
           }
            for(auto& tr : traps) { 
                field[tr.y][tr.x] = 'X'; // отрисовка ловушки 
            }
        for(int i = 0; i < HEIGHT; ++i) { 
            for(int j = 0; j < WIDTH; ++j) { 
                std::cout << field[i][j]; // выводим готовое поле в консоль
            }
            std::cout << std::endl;
        }
    } 
      void Game::moveTraps() {  // метод для движения ловушек 
        int dy[] = {1,-1, 0, 0}; // массив с координатами строки для ловушек
        int dx[] = {0, 0, -1, 1}; // массив с координатами столбцов для ловушек
          for(std::size_t i = 0; i < traps.size(); ++i) {   
             coords& curr_trap = traps[i]; // отмечаем текущую ловушку каждую итерацию
            coords next_pos = curr_trap; // также копируем текущую в другой объект 
                bool moved = false; // для логики движения как метка
                int tryies = 5; // попытки для движения и попасть не в игрока или в другой объект
                bool trap_rem = false;
                while(!moved && tryies-- > 0) { 
                     int dir = rand() % 4;  // движение будущий индекс для наших массивов
                     next_pos.y = curr_trap.y + dy[dir]; 
                     next_pos.x = curr_trap.x + dx[dir];
                     auto colusion_portals = std::any_of(portal.cbegin(), portal.cend(), [&] (const coords& c){ // используем метод для того чтобы следить что объекты не попадают друг на друга
                        return c.y == next_pos.y && c.x == next_pos.x;
                     });
                     if(colusion_portals) continue;
                     auto colusion_details = std::any_of(details.cbegin(), details.cend(), [&] (const coords& c){
                        return c.y == next_pos.y && c.x == next_pos.x;
                     });
                     if(colusion_details) continue;
                      if(player.front().y == next_pos.y && player.front().x == next_pos.x){
                        user.TakeDmg();
                        system("cls");
                        std::cout << "The trap has caught you, be careful (-15 from current HP)\n";
                        Sleep(2000);
                        traps.erase(traps.begin() + i);
                        moved = true;
                        trap_rem = true;
                        break;
                      }

                      if(next_pos.y == 0 || next_pos.y == HEIGHT - 1 || next_pos.x == 0 ||
                    next_pos.x == WIDTH - 1 ) continue;
                    bool trap_colusion = false;
                       for(std::size_t j = 0; j < traps.size(); ++j) { 
                        if(i != j) {
                            if(traps[j].y == next_pos.y && traps[j].x == next_pos.x){
                                trap_colusion = true; break;
                            }
                         }
                       }
                       if(trap_colusion) continue; 
                       curr_trap.y = next_pos.y;
                       curr_trap.x = next_pos.x;
                         moved = true;
                }
                if(!trap_rem) {
                    ++i;
                } else { continue; }
          }
      }  

     void Game::Input() { 
         coords head = player.front();
        if(kbhit()) { 
            char dir = 'D';
            while(kbhit()){
                dir = getch();
            }
            switch(dir) { 
                case 'w': case 'W': head.y--; break;
                case 's': case 'S': head.y++; break;
                case 'a': case 'A': head.x--; break;
                case 'd': case 'D': head.x++; break;
            }
              if(head.y == 0 || head.y == HEIGHT - 1 || head.x == 0 || head.x == WIDTH -1) 
              return;
                     for(auto& p : portal) { 
                        if(head.y == p.y && head.x == p.x) { 
                            level_completed = true;
                            break;
                        }
                     }
                      for(auto it = details.begin(); it != details.end(); ++it) { 
                        if(head.y == it->y && head.x == it->x) { 
                            details.erase(it);
                            if(details.empty()) {
                                system("cls");
                                std::cout << "You've collected all the matching parts on the level\n" <<
                                 "and a portal will appear. \n";
                                Sleep(2500);
                                portal.push_back({HEIGHT / 2, WIDTH / 2});
                            } else {
                            system("cls");
                            std::cout << "You've found the part, it's just a matter of fixing the delivery \n";
                            Sleep(1500);}
                            break;
                        }
                      }
                       for(auto it = traps.begin(); it != traps.end(); ++it) { 
                        if(head.y == it->y && head.x == it->x) { 
                            traps.erase(it);
                            user.TakeDmg();
                            system("cls");
                             std::cout << "You've taken damage, so don't fall into the traps. \n";
                            Sleep(2000);
                            break;
                        }
                      }

              player.insert(player.begin(), head);
              player.pop_back();
        } 
   }
     void Game::LegendCosmic() const { 
        system("cls");
   std::cout << "========================================================\n";
    std::cout << "=============  The Last Rebel =========\n";
    std::cout << "========================================================\n\n";
    
    std::cout << "SYNOPSIS:\n";
    std::cout << "You are a rebel engineer, the last survivor of the crew\n";
    std::cout << "Your task is to survive, collect all the parts to repair the ship and escape through the portals\n";
    std::cout << "That the alien planet has prepared for you\n";
    std::cout << "\n\n"; 

    std::cout << "FIELD SYMBOLS:\n";
    std::cout << "  [#] : Impassable wall/compartment boundary\n"; // English translation
    std::cout << "  [p] : You (P - player) \n"; 
    std::cout << "  [X] : Merciless electric traps (-15 HP)\n"; 
    std::cout << "  [@] : Active Portal (Level Goal)\n";
    std::cout << "  [&, <, T...] : Parts for ship repair\n"; 
    std::cout << "  [.] : floor (Empty space)\n\n"; 

    std::cout << "OBJECTIVE:\n"; 
    std::cout << "1.A prologue to understand the game mechanics. The whole game will be leveled. (Level 0) \n"; 
    std::cout << "2.In the following levels the portal is closed, to open it you need to collect all the parts\n"; 
    std::cout << "Fix the ship, escape.\n\n"; 
    
    std::cout << "CONTROLS: W A S D (movement)\n"; 
    std::cout << "========================================================\n";
    std::cout << "Press any key to start...\n";
    getch();
     }
     void Game::RunSys()  {
        LegendCosmic();
          while(true) { 
            Input();
            if(init_level >= 3 ) {
                moveTraps();
            }
        if(level_completed == true) { 
                system("cls");
                std::cout << "\n\n\n";
             std::cout << " <><><><><><>\n";
            std::cout << "<><><><><>YOU PASSED LEVEL<><><><" << getLVL() << "><>" << "\n";
                 std::cout << " <><><><><><>\n";
                Sleep(1500); 
                 init_level++;
                  initLVL();
                   level_completed = false;
                   continue;
            }
            system("cls"); 
            drawField();
            std::cout <<"===============\n";
            std::cout << "====+Exercise+====\n";
            std::cout << "====Find all the details, to enter the portal====\n";
            std::cout << "================\n";
            std::cout << "================\n";
            std::cout << "UR ID: " << user.get_name() << "\n" << "and ur current health: " << user.get_hp() << "\n";
            Sleep(150);
        }
     }
   
    void Game::initLVL() {
            player.clear();
            portal.clear();
            player.push_back({1,2});
           switch(init_level) { 
            case 1: 
            spawn_elements(3);
            break;
            case 2:
            spawn_traps(2);
            spawn_elements(5);
            break;
            case 3:
             spawn_traps(2);
                spawn_elements(4);
                break;
                case 4:
                spawn_traps(3);
                spawn_elements(4);
                break;
                case 5:
                spawn_traps(5);
                spawn_elements(3);
                break;
                case 6:
                spawn_traps(6);
                spawn_elements(4);
                break;
                case Win_level:
                 system("cls");
              std::cout << "\n\n\n";
              std::cout << "<><><><><><><><><><><><><><><>\n";
                std::cout << "=========YOU[1011001]ESCAPED, exiting system.....\n";
                std::cout << "<><><><><><><><><><><><><><><>\n";
                Sleep(4000);
                exit(0);
                default:
                throw std::out_of_range("Error303");
           }
    }
 int Game::getLVL() const { return init_level;} 
    coords Game::save_coords() {
        coords new_obj;
          bool valid = false;
          while(!valid) { 
             new_obj.y = rand() % (HEIGHT - 2 ) + 1;
             new_obj.x = rand() % (WIDTH - 2) + 1;
             valid = true;
              if(std::any_of(player.cbegin(), player.cend(), [&] (const coords& c) { return c.y == new_obj.y && c.x == new_obj.x;})) {   
              valid = false; continue;
            } if(std::any_of(portal.cbegin(), portal.cend(), [&] (const coords& c) { return c.y == new_obj.y && c.x == new_obj.x;})) {
                valid = false; continue;
            } if(std::any_of(traps.cbegin(), traps.cend(), [&] (const coords& c) { return c.y == new_obj.y && c.x == new_obj.x;})){
                valid = false; continue; 
            } if(std::any_of(details.cbegin(), details.cend(), [&] (const coords& c) { return c.y == new_obj.y && c.x == new_obj.x;})){
                valid = false; continue; 
            } 
          }
          new_obj.glyph = details_glyphs[rand() % size_details];
          return new_obj;
    }
       void Game::spawn_traps(int count_traps) { 
        for(int i = 0; i < count_traps; ++i) { 
             traps.push_back(save_coords());
        }
       }
       void Game::spawn_elements(int count_details) { 
        for(int i = 0; i < count_details; ++i) { 
             details.push_back(save_coords());
        }
       }
