// Teodor-Adrian Mirea (2017)
// Univerity Project - Photo Editor - C

#include<stdio.h>
#include<math.h>

void rgb_hsv(float, char);
float max(float, float, float);
float min(float, float, float);
float hue(float, float, float, float, float);
float saturation(float, float);

int main() {
	int N, M, i; //N - number of lines, M - number of columns
	float x; // x - value of modified parameter
	char c; // c - parameter to be modified (hue, saturation or value)

	scanf("%d %d %c %f", &N, &M, &c, &x);

	// processing every pixel of the photo
	for (i = 1; i <= N*M; i++)
		rgb_hsv(x, c);

	return 0;
}

// rgb_hsv(x, c) will transform the initial (R, G, B) triplet into the final
// (H, S, V) triplet
void rgb_hsv(float x, char c) {
	int R, G, B;
	float Rf, Gf, Bf, Cmax, Cmin, delta, H, S, V;

	scanf("%d %d %d", &R, &G, &B);

	// scaling the R, G, B values and finding the Cmax, Cmin and delta values
	Rf = R / 255.;
	Gf = G / 255.;
	Bf = B / 255.;
	Cmax = max(Rf, Gf, Bf);
	Cmin = min(Rf, Gf, Bf);
	delta = Cmax - Cmin;

	// finding the H, S and V values
	H = hue(Rf, Gf, Bf, Cmax, delta);
	S = saturation(Cmax, delta);
	V = Cmax;

	// modify the (H, S, V) triplet depending of the value of c
	switch (c) {
		case 'h':
			H = H + x;
			break;

		case 's':
			S = S * x;
			break;

		case 'v':
			V = V * x;
			break;
	}

	// the H, S and V values are normed for being between 0 and 1
	if (H < 0)
		H = 0;
	if (H > 1)
		H = 1;
	if (S < 0)
		S = 0;
	if (S > 1)
		S = 1;
	if (V < 0)
		V = 0;
	if (V > 1)
		V = 1;

	// the final (H, S, V) triplet is printed with an accuracy of 5 decimals
	printf("%.5f %.5f %.5f\n", H, S, V);
}

// calculation of the maximum between the 3 values (used to identify Cmax)
float max(float x, float y, float z) {
	if (x > y) {
		if (x > z)
			return x;
		return z;
	}
	else {
		if (y > z)
			return y;
		return z;
	}
}

// calculation of the minimum between the 3 values (used to identify Cmin)
float min(float x, float y, float z) {
	if (x < y) {
		if (x < z)
			return x;
		return z;
	}
	else {
		if (y < z)
			return y;
		return z;
	}
}

// calculation of H (hue) value using the proper formulas
float hue(float R1, float G1, float B1, float Cmax, float delta) {
	float H;

	if (delta == 0)
		H = 0;
	else if (Cmax == R1)
		H = 60 * fmod((float)((G1 - B1) / delta), 6);
	else if (Cmax == G1)
		H = 60 * ((float)((B1 - R1) / delta) + 2);
	else if (Cmax == B1)
		H = 60 * ((float)((R1 - G1) / delta) + 4);

	// if the value is negative, make it positive
	if (H < 0)
		H = H + 360;

	// norm the H value for being between 0 and 1
	H = H / 360.;

	return H;
}

// calculation of S (saturation) value using the proper formulas
float saturation(float Cmax, float delta) {
	if (Cmax == 0)
		return 0;
	return (float)(delta / Cmax);
}
