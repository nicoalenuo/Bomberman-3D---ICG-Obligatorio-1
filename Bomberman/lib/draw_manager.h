#pragma once
#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "hud.h"
#include "global.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Draw {
    
    private:
        // Singleton
        Draw();

    public:
        // Constructor and singleton method
        Draw(Draw const&) = delete;
        void operator=(Draw const&) = delete;
        static Draw& get_instance();

        void DrawHUD(HUDComponent top_left, HUDComponent top_right, HUDComponent top_center);
        void DrawHUDComponent(HUDComponent component);
};

#endif
