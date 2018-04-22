#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship
{
	private:
	public:

		double x;
		double y;
		double z;

		double angleX;
		double angleY;
		double angleZ;

		float angle;

		Spaceship();
		~Spaceship();

		void Set();
		void SpaceshipDraw();
		void starship();

};



#endif