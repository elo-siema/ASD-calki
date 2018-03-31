#include <stdlib.h>
#include <stdio.h>
#define lp 1000;
double c_od, c_do;

void setRange(double from, double to)
{
	c_od = from;
	c_do = to;
}

double prostokaty(double(*f)(double))
{
	double krok, p, suma = 0;
	krok = (c_do - c_od) / lp;
	for (p = c_od; p<c_do; p += krok)
		suma += (*f)(p)*krok;
	return suma;
}

double trapezy(double(*f)(double))
{
	double krok, p, suma = 0;
	krok = (c_do - c_od) / lp;
	for (p = c_od; p<c_do; p += krok)
		suma += 0.5*((*f)(p) + (*f)(p + krok))*krok;
	return suma;
}

double mc(double(*f)(double))
{
	const int kroczek = 1000;
	const int lstrzalow = 1000000;
	int   i, trafione = 0;
	double cal, ff, x = c_od, zakresx, zakresy, y, ymax, ymin;
	zakresx = c_do - c_od;
	//printf("zakres x=%lf\n", zakresx);
	ymax = ymin = (*f)(c_od);
	for (; x <= c_do; x += zakresx / kroczek)
	{
		y = (*f)(x);
		if (y<ymin) ymin = y;
		else if (y>ymax) ymax = y;
	};
	if (ymax*ymin>0)
	{
		if (ymax>0)
			ymin = 0;
		else
			ymax = 0;
	}
	//printf("ymin = %lf   ymax = %lf\n", ymin, ymax);
	for (i = 0; i<lstrzalow; i++)
	{
		x = rand();
		x = x / RAND_MAX * zakresx + c_od;
		y = rand();
		y = y / RAND_MAX * (ymax - ymin) + ymin;
		ff = (*f)(x);
		if (ff>y && y>0) trafione++;
		else if (ff<y && y<0) trafione--;
	}
	cal = trafione * zakresx*(ymax - ymin) / lstrzalow;
	//printf("trafionych %d\n", trafione);
	return cal;
}


