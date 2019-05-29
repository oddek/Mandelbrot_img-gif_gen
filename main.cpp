#include "Mandelbrot.h"

int main(int argc, char**argv)
{
	Mandelbrot* m = new Mandelbrot();
	//m->create_png();
	m->create_gif();
}
