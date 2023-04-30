#pragma once


struct Color {
	unsigned int r, g, b;
	Color() { this->r = 0; this->g = 0; this->b = 0; };
	Color(int r, int g, int b) :r(r), g(g), b(b) {};
	Color applyIntensity(float intensity) {
		Color c;
		c.r = this->r * intensity;
		c.g = this->g * intensity;
		c.b = this->b * intensity;		
		return c;
	}
};



