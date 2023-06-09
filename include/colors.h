#pragma once


typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

#define DEFINE_COLOR(NAME, R, G, B, A) static constexpr Color NAME=Color{R, G, B, A}

class Colors{
public:
	DEFINE_COLOR(RED, 1.0f, 0.0f, 0.0f, 0.0f);
	DEFINE_COLOR(GREEN, 0.0f, 1.0f, 0.0f, 0.0f);
	DEFINE_COLOR(BLUE, 0.0f, 0.0f, 1.0f, 0.0f);
	DEFINE_COLOR(CYAN, 0.0f, 1.0f, 1.0f, 0.0f);
	DEFINE_COLOR(MAGENTA, 1.0f, 0.0f, 1.0f, 0.0f);
	DEFINE_COLOR(YELLOW, 1.0f, 1.0f, 0.0f, 0.0f);
	DEFINE_COLOR(BLACK, 0.0f, 0.0f, 0.0f, 0.0f);
	DEFINE_COLOR(WHITE, 1.0f, 1.0f, 1.0f, 0.0f);
	DEFINE_COLOR(GRAY, 0.5f, 0.5f, 0.5f, 0.0f);
	DEFINE_COLOR(LIGHT_GRAY, 0.75f, 0.75f, 0.75f, 0.0f);
	DEFINE_COLOR(DARK_GRAY, 0.25f, 0.25f, 0.25f, 0.0f);
	DEFINE_COLOR(BROWN, 0.6f, 0.4f, 0.2f, 0.0f);
	DEFINE_COLOR(ORANGE, 1.0f, 0.5f, 0.0f, 0.0f);
	DEFINE_COLOR(PINK, 1.0f, 0.75f, 0.8f, 0.0f);
	DEFINE_COLOR(PURPLE, 0.5f, 0.0f, 0.5f, 0.0f);
	DEFINE_COLOR(INDIGO, 0.3f, 0.0f, 0.5f, 0.0f);
	DEFINE_COLOR(TEAL, 0.0f, 0.5f, 0.5f, 0.0f);
	DEFINE_COLOR(LIME, 0.75f, 1.0f, 0.0f, 0.0f);
	DEFINE_COLOR(OLIVE, 0.5f, 0.5f, 0.0f, 0.0f);
	DEFINE_COLOR(MAROON, 0.5f, 0.0f, 0.0f, 0.0f);
	DEFINE_COLOR(A_RED, 1.0f, 0.0f, 0.0f, 1.0f);
	DEFINE_COLOR(A_GREEN, 0.0f, 1.0f, 0.0f, 1.0f);
	DEFINE_COLOR(A_BLUE, 0.0f, 0.0f, 1.0f, 1.0f);
	DEFINE_COLOR(A_CYAN, 0.0f, 1.0f, 1.0f, 1.0f);
	DEFINE_COLOR(A_MAGENTA, 1.0f, 0.0f, 1.0f, 1.0f);
	DEFINE_COLOR(A_YELLOW, 1.0f, 1.0f, 0.0f, 1.0f);
	DEFINE_COLOR(A_BLACK, 0.0f, 0.0f, 0.0f, 1.0f);
	DEFINE_COLOR(A_WHITE, 1.0f, 1.0f, 1.0f, 1.0f);
	DEFINE_COLOR(A_GRAY, 0.5f, 0.5f, 0.5f, 1.0f);
	DEFINE_COLOR(A_LIGHT_GRAY, 0.75f, 0.75f, 0.75f, 1.0f);
	DEFINE_COLOR(A_DARK_GRAY, 0.25f, 0.25f, 0.25f, 1.0f);
	DEFINE_COLOR(A_BROWN, 0.6f, 0.4f, 0.2f, 1.0f);
	DEFINE_COLOR(A_ORANGE, 1.0f, 0.5f, 0.0f, 1.0f);
	DEFINE_COLOR(A_PINK, 1.0f, 0.75f, 0.8f, 1.0f);
	DEFINE_COLOR(A_PURPLE, 0.5f, 0.0f, 0.5f, 1.0f);
	DEFINE_COLOR(A_INDIGO, 0.3f, 0.0f, 0.5f, 1.0f);
	DEFINE_COLOR(A_TEAL, 0.0f, 0.5f, 0.5f, 1.0f);
	DEFINE_COLOR(A_LIME, 0.75f, 1.0f, 0.0f, 1.0f);
	DEFINE_COLOR(A_OLIVE, 0.5f, 0.5f, 0.0f, 1.0f);
	DEFINE_COLOR(A_MAROON, 0.5f, 0.0f, 0.0f, 1.0f);

};
