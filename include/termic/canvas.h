#pragma once

#include "color.h"
#include "size.h"

namespace termic
{

struct Screen;

namespace color
{
struct Sampler;
}

struct Rectangle
{
	Pos top_left;
	Size size;
};


struct Canvas
{
	inline Canvas(Screen &scr) : _scr(scr) {};

	void clear();
	Size size() const;

	void fill(Color c);
	void fill(const color::Sampler *s, float sampler_angle=0);
	void fill(Rectangle rect, Color c);
	void fill(Rectangle rect, const color::Sampler *s, float sampler_angle=0);


private:
	Screen &_scr;
};

} // NS: termic
