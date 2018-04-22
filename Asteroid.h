#ifndef ASTEROID_H
#define ASTEROID_H

#include "LoadObjectFile.h"

class Asteroid
{
	private:	
		model md;
		double size[3];
		double sizetmp[3];

	public:

		bool notset;
	
		double posx;
		double posy;
		double posz;

		double rotx;

		double rate;
		double ratesize;

		Asteroid();
		~Asteroid();

		void Load(char*);
		void Set(double, double, double);
		void AsteroidDraw();

		double get_posx();
		double get_posy();
		double get_posz();
};


#endif