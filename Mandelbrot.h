#include "IMG.h"
#include <iostream>
#include <vector>
#include <complex>
#include <chrono>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cmath>
#include <Windows.h>

class Mandelbrot
{
public:

	Mandelbrot();
	~Mandelbrot();
	void create_img();
	void create_gif();
	vector<unsigned char> get_buffer();
	void update_min_max(char axis);

	const char* output_file = "output.png";
	const char* outputgif = "outgif.gif";
	const int iterations = 5000;
	const unsigned width = 200;
	const unsigned height = 200;
	const int frames = 400;
	const int mspf = 4;
	const double x_center = -1.7499564580472739564705477776562276034030013003223408296905558858044682390324136554899487670145791483057924534176890341996502913934286483023421550995322215230920028391110922147773310060433028445101080723665476709250383640281390786950832930195073649094100;
	const double y_center = -0.0000000028889364622952216110631124592015176048023146806110138866271195328775766372317069847663371213563257344270341244777002427747254513137862024448737402834148390346058278262950918110733516833061003987539156235147103962630048751561606774033170058308043;
	double zoom_inc = 0.001;
	double x_min = -2;
	double x_max = 2;
	double y_min = -2;
	double y_max = 2;
	double x_inc = (x_max - x_min)/(double)width;
	double y_inc = (y_max - y_min)/(double)height;
	int magic_number = 4;
	mutex vector_lock;
	mutex function_lock;

private:
	void calc();
	void iterate(double x, double y);
	long map_onto(double x, double a, double b, double c, double d);
	int get_color(int x,int f,int p);

	GifWriter* gifw;
	IMG* img;
};