#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <conio.h>
#include <iostream>

using namespace std;

class Mandelbrot : public olc::PixelGameEngine {
	public:
	Mandelbrot() {
		sAppName = "Mandelbrot Set";
	}

	/* values that can be modified to generate other Julia Sets */
	double _real = -0.8;
	double _img = -0.156;

	double Map(double val, double curr_min, double curr_max, double new_min, double new_max) {
		return (val - curr_min) / (curr_max - curr_min)*(new_max - new_min) + new_min;
	}

	bool OnUserCreate() override {
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++) {

				double a = Map(x, 0, ScreenWidth(), -2, 2);
				double b = Map(y, 0, ScreenHeight(), -2, 2);
				int n = 0;
				while (n < 256) {
					double re1 = a*a;
					double re2 = b*b;
					double imgPart = 2 * a * b;
					a = re1 - re2 + _real;
					b = imgPart + _img;
					if (abs(a + b) > 16)
						break;
					n++;
				}
				int R = n % 256;
				int G = n % 100;
				int B = n % 50;
				Draw(x, y, olc::Pixel(R, G, B));
			}
		return true;
	}


	bool OnUserUpdate(float deltaTime) override{
		return true;
	}
};



int main()
{
	Mandelbrot demo;
	if (demo.Construct(1000, 1000, 1, 1))
		demo.Start();
	_getch();
}