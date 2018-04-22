#ifndef STAR_H
#define STAR_H

#include "Asteroid.h"

class Star
{
	private:
		double radius_inner;
		double radius_outer;
		double radius_tmp;

		double radius_change;
		
		float x;
		float y;
		
	public:
		
		Star();
		~Star();

		void Set(double, double, float, float);
		void StarDraw(double, double, int, int);
		void SunDraw(double, double, int, int);
		void Print();

};

class Sky
{
	private:
		class Star *stars;
		class Star Sun;
		int num_of_stars;
		unsigned int time;

	public:

		class Asteroid asteroid;

		int height;
		int width;

		double xmove;
		double ymove;

		Sky();
		~Sky();

		void Set();
		void SkyDraw();
	
		unsigned int getTime();
		bool AsteroidNotSet();
};

#endif