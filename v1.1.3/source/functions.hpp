#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

bool init();
b2Vec2 BoxToSDL(b2Vec2 in);
int BoxToSDL(float in);
void titlescreen();
void alphaText(std::string message, std::string fontFile, int fontSize, int x, int y, int a);
void renderText(std::string message, std::string fontFile, int fontSize, int x, int y);

#endif
