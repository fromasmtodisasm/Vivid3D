#pragma once
class Utils
{
public:
	static int rand(int low, int high);
	static int rand(int high);
	static double rand();
	static double rand(double low, double high);
	static double rand(double high);
	static void randSeed(unsigned int seed);
	static void randSeedTicks();
private:



};

