#include <algorithm>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


/////STATUS
#define DYING "Dying"
#define DIE "Die"
#define IDLE "Idle"
#define RUN "Run"
#define WALK "Walk"
#define EAT "Eat"
#define ATTACK "Attack"


/////Main Items
#define PRICE_TEXT_POSITION sprite.getPosition().x + 66, sprite.getPosition().y + 31
#define REMANING_TIME_POSITION sprite.getPosition().x + 78, sprite.getPosition().y + 7
#define BUDGET_POSITION sprite.getPosition().x + 100, sprite.getPosition().y + 28
#define PRICE_TEXT_SIZE 20
#define REMAINING_TIME_TEXT_SIZE 14
#define BUDGET_TEXT_SIZE 28
#define BLOCK_LENGHT 87
#define BLOCK_WIDTH 108
#define FIRST_BLOCK_DEPTH 170
#define LINE_ONE_START_POSITION Vector2f(980, 50)
#define LINE_TOW_START_POSITION Vector2f(980, 158)
#define LINE_THREE_START_POSITION Vector2f(980, 266)
#define LINE_FOUR_START_POSITION Vector2f(980, 374)
#define LINE_FIVE_START_POSITION Vector2f(980, 482)
#define SEED_PACKET_SCALE 0.5, 0.5
#define HOUSE_BORDER 100
#define TEXT_COLOR Color::White
#define DEFAULT_COLOR Color(0, 0, 0, 0)
#define HIGHLIGHT_COLOR Color(255, 255, 255, 50)
#define REGULAR_PEA_IMAGE "./Pics/Main Items/Pea.png"
#define FROZEN_PEA_IMAGE "./Pics/Main Items/Frozen Pea.png"
#define LILITA_FONT "./Fonts/LilitaOne.ttf"
#define MPLUS_FONT "./Fonts/MPLUS.ttf"


/////Type
#define MOBILE "Mobile"
#define FIX "Fix_Sun"
#define REGULAR "Regular"
#define FROZEN "Frozen"
#define ANGRY "Angry"
#define FROZEN_PEASHOOTER "Frozen PeaShooter"
#define PEASHOOTER "PeaShooter"
#define WALLNUT "WallNut"
#define SUNFLOWER "SunFlower"
#define MELON "Melon"
#define MENU "menu"
#define GAMEPLAY "gameplay"


/////SUNFLOWER
#define SUNFLOWER_SCALE 0.47,0.47
#define SUNFLOWER_ANIMATION "./Pics/SunFlower Plant"
#define FIX_SUN_POSITION sprite_position.x+40,sprite_position.y+50
#define SUN_IMAGE "./Pics/Main Items/Sun.png"
#define SUN_SCALE 0.6, 0.6


/////Wall-Nut
#define WALLNUT_SCALE 0.24, 0.24
#define WALLNUT_POSITION block->get_position().x - 35, block->get_position().y - 30
#define HIGH_HEALTH_UPPER_BOUND 0.80
#define HIGH_HEALTH_LOWER_BOUND 0.60
#define MEDIUM_HEALTH_LOWER_BOUND 0.45
#define PERFECT_HEALTH_IMAGE "./Pics/WallNut Plant/Full.png"
#define HIGH_HEALTH_IMAGE "./Pics/WallNut Plant/80.png"
#define MEDIUM_HEALTH_IMAGE "./Pics/WallNut Plant/60.png"
#define LOW_HEALTH_IMAGE "./Pics/WallNut Plant/45.png"


/////Pea-Shooter
#define FIRED_PEA_POSITION start_x, 164 + BLOCK_WIDTH * (line - 1)
#define PEA_FRAME_RATE 0.1f
#define PEASHOOTER_SCALE 0.18, 0.18
#define PEA_SCALE 0.5
#define PEASHOOTER_ANIMATION "./Pics/PeaShooter Plant"
#define FROZEN_PEASHOOTER_ANIMATION "./Pics/Frozen PeaShooter Plant"


/////Zombies
#define ZOMBIE_ANIMATION_SPEED seconds(0.2f)
#define ZOMBIE_SCALE 0.5, 0.5
#define REGULAR_ZOMBIE_ANIMATION "./Pics/Regular Zombie"
#define ANGRY_ZOMBIE_ANIMATION "./Pics/Angry Zombie"