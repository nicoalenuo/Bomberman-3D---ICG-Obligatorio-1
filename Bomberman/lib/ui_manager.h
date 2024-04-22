#pragma once
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <string> 
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>
#include "global.h"

#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class UI {

    private:
        // Singleton
        UI();
        
        static UI* instancia;

        // References
        Draw* draw_manager;

        // Basic properties
        TTF_Font* top_font;
        TTF_Font* bottom_font;
        HUDComponent score;
        HUDComponent coins;
        HUDComponent game_over;

        // Basic methods
        void set_message_on_component(string message, TTF_Font* font, HUDComponent* component);
    
    public:
        // Constructor and singleton method
        //UI(UI const&) = delete;
        //void operator=(UI const&) = delete;
        static UI* getInstance();

        // Main methods
        void draw();
        void clean_memory();

        // Setters
        void set_score(int score_number);
        void set_coins(int coins_number);
        void set_game_over(bool is_game_over);
};

#endif
