// Reference: https://stackoverflow.com/questions/30016083/sdl2-opengl-sdl2-ttf-displaying-text

// HEADERS
// -----------------------------------------------------------------------------------
#include "../lib/ui_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

UI* UI::instancia = nullptr;

UI::UI() {
	draw_manager = &Draw::get_instance();
	
	int ttf = TTF_Init();
	if (ttf == -1) {
		cerr << "[SDL TTF Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	top_font = TTF_OpenFont("../OpenSans-Regular.ttf", 24); //this opens a font style and sets a size
	if (top_font == nullptr) {
		cerr << "TTF_OpenFont error: " << SDL_GetError() << endl;
		return;
	}
	bottom_font = TTF_OpenFont("../OpenSans-Regular.ttf", 12); //this opens a font style and sets a size
	if (bottom_font == nullptr) {
		cerr << "TTF_OpenFont error: " << SDL_GetError() << endl;
		return;
	}
	score.message_color = { 255, 255, 255 };
	coins.message_color = { 255, 255, 0 };
	game_over.message_color = { 255, 255, 255 };

	score.position = HUDComponentIs::top_left;
	coins.position = HUDComponentIs::top_right;
	game_over.position = HUDComponentIs::top_center;

	set_score(0);
	set_coins(0);
	set_game_over(false);
}

UI* UI::getInstance() {
	if (instancia == nullptr)
		instancia = new UI();

	return instancia;
}

// Main methods
// -----------------------------------------------------------------------------------

void UI::draw() {
	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

	draw_manager->DrawHUD(score, coins, game_over);

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();
}

void UI::clean_memory() {
	SDL_FreeSurface(score.surface_message);
	SDL_FreeSurface(score.rgb_surface);
	SDL_FreeSurface(coins.surface_message);
	SDL_FreeSurface(coins.rgb_surface);
	TTF_CloseFont(top_font);
	TTF_CloseFont(bottom_font);
}

// Getters & Setters
// -----------------------------------------------------------------------------------

void UI::set_score(int score_number) {
	string message = "Score: " + to_string(score_number);
	set_message_on_component(message, top_font, &score);
}

void UI::set_coins(int coins_number) {
	string message = "Coins: " + to_string(coins_number);
	set_message_on_component(message, top_font, &coins);
}

void UI::set_game_over(bool is_game_over) {
	string message;
	if (is_game_over) {
		message = "GAME OVER!";
	} else {
		message = "  ";
	}
	set_message_on_component(message, top_font, &game_over);
}

void UI::set_message_on_component(string message, TTF_Font* font, HUDComponent* component) {
	glColor3f(component->message_color.r, component->message_color.g, component->message_color.b);
	component->surface_message = TTF_RenderText_Blended(font, message.c_str(), { 255, 255, 255 });
	if (component->surface_message == NULL) {
		cerr << "TTF_RenderText error: " << SDL_GetError() << endl;
		return;
	}

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &(component->texture_id));
		glBindTexture(GL_TEXTURE_2D, component->texture_id);
	
		TTF_SizeText(font, message.c_str(), &(component->width), &(component->height));
	
		//Create a surface to the correct size in RGB format, and copy the old image
		component->rgb_surface = SDL_CreateRGBSurface(0, component->width, component->height, 32, 0, 0x0000ff00, 0x000000ff, 0xff000000);
		if (component->rgb_surface == NULL) {
			cerr << "SDL_CreateRGBSurface() failed: " << SDL_GetError() << endl;
			exit(1);
		}
		SDL_BlitSurface(component->surface_message, NULL, component->rgb_surface, NULL);

		//Avoid mipmap filtering
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//Copy the created image into OpenGL format
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, component->width, component->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, component->rgb_surface->pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
