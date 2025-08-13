#include "Config.h"

Config g_config{
    {Vector2{64.0f, 64.0f}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT} * 0.5f, 750.0f,
     350.0f, 500.0f, 0.02f, ToRadians(45), -ToRadians(15), 21.0f, 13.5f, 1.5f,
     "Resources/Bird.png", "Resources/Bird.png"},
    {Vector2{100.0f, 600.0f}, 300.0f, 200.0f, "Resources/Pipe.png"},
    {2.0f, -300.0f, 300.0f},
    {Vector2{2.0f, 2.0f}, 3.0f, Color::Black, Vector2u{5, 7}},
    {80.0f, 4u, "Resources/bg2.png"},
    {Vector2{2, SCREEN_HEIGHT - 23}, 3.0f, Color::Black, Vector2u{5, 7}}

};