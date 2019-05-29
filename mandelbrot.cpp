#include "Mandelbrot.h"


Mandelbrot::Mandelbrot()
{
	img = new IMG(output_file, width, height);
	gifw = new GifWriter();
	GifBegin(gifw, outputgif, width, height, mspf);
}

Mandelbrot::~Mandelbrot()
{
	delete img;
	delete gifw;
}



void Mandelbrot::create_img()
{
	calc();
	img->encodeOneStep();
}

void Mandelbrot::update_min_max(char axis)
{
	if(axis == 'x')
	{
		double inc_fact = (zoom_inc/abs(x_max-x_min));
		x_min += inc_fact * abs(x_center-x_min);
		x_max -= inc_fact * abs(x_center-x_max);

		x_inc = abs(x_max - x_min)/(double)width;
	}
	else if(axis == 'y')
	{
		double inc_fact = (zoom_inc/abs(y_max-y_min));
		y_min += inc_fact * abs(y_center-y_min);
		y_max -= inc_fact * abs(y_center-y_max);

		y_inc = abs(y_max - y_min)/(double)height;
	}
}

vector<unsigned char> Mandelbrot::get_buffer()
{
	calc();
	cout << "Done calc()" << endl;
	return img->buffer;
}

void Mandelbrot::create_gif()
{
	auto start = chrono::high_resolution_clock::now();
	int n = 0;
	while(n < frames)
	{
		SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
		if(x_min >= x_max || y_min >= y_max) break;
		calc();
		static_assert(std::is_same<unsigned char, uint8_t>::value, "uint8_t is not unsigned char");
		
		uint8_t* data = img->buffer.data();
		GifWriteFrame(gifw, data, width, height, mspf);
		update_min_max('x');
		update_min_max('y');
		zoom_inc = min(abs(y_center-y_min), min(abs(y_center-y_max),
	 		min(abs(x_center-x_max), abs(x_center-x_min))));
		cout << "zoom_inc: " << zoom_inc << endl;
		printf("x_min: %.16G x_max: %.16G\ny_min: %.16Gy_max: %.16G\n", x_min, x_max, y_min, y_max);
		cout << "N: " << n << endl;
		n++;
	}
	SetThreadExecutionState(ES_CONTINUOUS);
	GifEnd(gifw);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end - start;
	cout << "Ferdig!" << endl;
	cout << "Gif tok: " << diff.count() << " sekunder" <<endl;
}

void Mandelbrot::calc()
{
	for(double y = y_max; y >= y_min; y -= y_inc)
	{
		for(double x = x_min; x <= x_max; x += x_inc)
		{
			iterate(x, y);
		}
	}
}

void Mandelbrot::iterate(double x, double y)
{
	//complex<double> c(x, y);
	//complex<double> z(0, 0);
	double z_real = 0;
	double z_imag = 0;
	int no_of_iterations = 0;
	for(no_of_iterations; no_of_iterations <= iterations; no_of_iterations++)
	{
		double old_z_real = z_real;
		z_real = pow(z_real, 2) - pow(z_imag, 2) + x;
		z_imag = 2*old_z_real*z_imag + y;
		if(pow(z_real,2)+pow(z_imag,2) > magic_number) break;
	}

	long index = 4*(map_onto(y, y_max, y_min, 0, height)*width
		+ map_onto(x, x_min, x_max, 0, width));
	//Skjønner ikke helt hvorfor denne er nødvendig, men får for stor index i blant. 
	//Antakelig noe tull når det blir mange desimaler
	if(index >= img->buffer.size())
	{
		return;
	}

	if(no_of_iterations > iterations*0.84)
	{
		img->buffer.at(index) = 0;
		img->buffer.at(index+1) = 0;
		img->buffer.at(index+2) = 0;
		img->buffer.at(index+3) = 255;
	}
	else
	{
		img->buffer.at(index) = get_color(no_of_iterations, 1,0);
		img->buffer.at(index+1) =  get_color(no_of_iterations, 1, 120);
		img->buffer.at(index+2) =  get_color(no_of_iterations, 1,240);
		img->buffer.at(index+3) = 255;
	}
}

long Mandelbrot::map_onto(double x, double a, double b, double c, double d)
{
	long i = abs(((x-a)*((d-c)/(b-a))+c));
	//if(i > 49) return 49;
	return i;
}

int Mandelbrot::get_color(int x,int f,int p)
{
	return 255*pow((cos(sqrt(x)*f + p)), 2);
}