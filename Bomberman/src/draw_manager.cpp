// HEADERS
// -----------------------------------------------------------------------------------
#include "../lib/draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------
Draw::Draw() {
}


Draw& Draw::get_instance() {
	static Draw instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Main objects' drawing methods
// -----------------------------------------------------------------------------------

void Draw::DrawHUD(HUDComponent top_left, HUDComponent top_right, HUDComponent top_center) {
	glPushMatrix();
	
	// TOP
	int height = max(top_left.height, top_right.height);
	DrawHUDComponent(top_left);
	DrawHUDComponent(top_right);
	DrawHUDComponent(top_center);

	// Draw the rest of the overlay
	glBegin(GL_QUADS); {
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, height + 6.f, 0.f);
		glVertex3f(WINDOW_WIDTH, height + 6.f, 0.f);
		glVertex3f(WINDOW_WIDTH, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
	} glEnd();
	glPopMatrix();

	// BOTTOM

	// Draw the rest of the overlay
	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, keybinds_texture);
	glBegin(GL_QUADS); {
		glColor3f(1.f, 1.f, 1.f);
		glTexCoord2d(0.f, 1.f); glVertex3f(0.f, SCR_HEIGHT - 62.f, 1.f);
		glTexCoord2d(1.f, 1.f); glVertex3f(WINDOW_WIDTH, SCR_HEIGHT - 62.f, 1.f);
		glTexCoord2d(1.f, 0.f); glVertex3f(WINDOW_WIDTH, SCR_HEIGHT, 1.f);
		glTexCoord2d(0.f, 0.f); glVertex3f(0.f, SCR_HEIGHT, 1.f);
	} glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();*/
}

void Draw::DrawHUDComponent(HUDComponent component) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, component.texture_id);
	glColor3f(component.message_color.r, component.message_color.g, component.message_color.b);
	switch (component.position) {
	case HUDComponentIs::top_left:
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f(30.f, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f(30.f + component.surface_message->w, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f(30.f + component.surface_message->w, 3.f, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f(30.f, 3.f, 0.f);
		} glEnd();
		break;
	case HUDComponentIs::top_right:
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f(WINDOW_WIDTH - 30.f - component.surface_message->w, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f(WINDOW_WIDTH - 30.f, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f(WINDOW_WIDTH - 30.f, 3.f, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f(WINDOW_WIDTH - 30.f - component.surface_message->w, 3.f, 0.f);
		} glEnd();
		break;
	case HUDComponentIs::top_center:
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f(WINDOW_WIDTH / 2.f - component.surface_message->w / 2, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f(WINDOW_WIDTH / 2.f + component.surface_message->w / 2, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f(WINDOW_WIDTH / 2.f + component.surface_message->w / 2, 3.f, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f(WINDOW_WIDTH / 2.f - component.surface_message->w / 2, 3.f, 0.f);
		} glEnd();
		break;
	}
	glDisable(GL_TEXTURE_2D);
}
