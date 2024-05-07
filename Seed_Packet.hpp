#include <algorithm>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Block;
class Plant;
class Sun_Plant;
class Invasive_Plant;
class Defender_Plant;
class Row;
class Pea;
class Game;
class Seed_Packet;

using namespace std;
using namespace sf;



class Seed_Packet
{
    private:
    pair<Texture, Texture> light_dark_images;
    Sprite sprite;
    Font lilita_one;
    Font mplus1;
    Time remaning_time = seconds(0);
    int price = 10;


    public:
    Seed_Packet(string light_path, string dark_path, Vector2f pos);
    Text get_remaining_time();
    Text get_price();
    Sprite get_sprite();
};
