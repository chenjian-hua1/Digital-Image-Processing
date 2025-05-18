#include <iostream>
using namespace std;

void LinearInterpolation(const int *f, int *g, int fw, int fh, int gw, int gh);
void NearestInterpolation(const int *f, int *g, int fw, int fh, int gw, int gh);

int* scaling(const int *f, const int w, const int h, double scale, bool linear, int &gw, int &gh) {
    gh = h * scale;
    gw = w * scale;
    int *g = new int[gh*gw];

	if (linear)
		LinearInterpolation(f, g, w, h, gw, gh);
	else 
		NearestInterpolation(f, g, w, h, gw, gh);

	return g;
}

void LinearInterpolation(const int *f, int *g, int fw, int fh, int gw, int gh) {
	double new_x, new_y, alpha, beta, a, b, c;
    for(int y=1; y<=gh; y++) {
		// new_y = (y-1.0) * ((y-1.0)/(nh-1.0)) + 1;
		new_y = (y-1.0) * (fh-1)/(gh-1);
		int y_floor = (int)new_y;
		int y_ceil = (int)ceil(new_y);

		beta = new_y - y_floor;
	 	for(int x=1; x<=gw; x++) {
			new_x = (x-1.0) * (fw-1)/(gw-1);
			int x_floor = (int)new_x;
			int x_ceil = (int)ceil(new_x);

			alpha = new_x - x_floor;
	 		a = (1-alpha)*f[y_floor*fw + x_floor] + alpha*f[y_floor*fw + x_ceil];
	 		b = (1-alpha)*f[y_ceil*fw + x_floor] + alpha*f[y_ceil*fw + x_ceil];
	 		c = beta*b + (1-beta)*a;

			g[(y-1)*gw + (x-1)] = (int)(c+0.5);
		}
	}
}

void NearestInterpolation(const int *f, int *g, int fw, int fh, int gw, int gh) {
    for(int y=1; y<=gh; y++) {
		int new_y = round((y-1.0) * (fh-1)/(gh-1));

	 	for(int x=1; x<=gw; x++) {
			int new_x = round((x-1.0) * (fw-1)/(gw-1));
			g[(y-1)*gw + (x-1)] = f[new_y*fw + new_x];
		}
	}
}