#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Power.h"

class Drawable
{
private:
	SDL_Color color;
	bool drawing;

	int ID;
	static int COUNT;
protected:
	virtual void Draw(SDL_Renderer* rend) = 0;
public:
	Drawable() { 
		drawing = true; 
		setDrawColor(0, 255, 0, 0); 
		Game::rendManager->addDrawable(this);
		ID = COUNT++;
	}
	~Drawable() {
		Game::rendManager->removeDrawable(ID);
	}

	void DrawItem(SDL_Renderer* rend) {
		if (drawing) {
			SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
			Draw(rend);
		}
	}
	void setDrawColor(int r, int g, int b, int a) { color.r = r; color.g = g; color.b = b; color.a = a; }
	int getID() { return ID; }

	void setDrawing(bool drawng) { drawing = drawng; }
	bool getDrawing(bool drawng) { return drawing; }
};

#endif