#include "pch.h"
#include "Utils.h"

int Utils::rand(int low, int high) {

	//std::experimental::randInt()
	return std::rand() % (high - low - 1) + low + 1;

};

int Utils::rand(int high) {

	return std::rand() % high;

};

double Utils::rand()
{
	double f = (double)std::rand() / (double)RAND_MAX;
	return f;
}

double Utils::rand(double low, double high) {

	double v = Utils::rand();
	return low + v * (high - low);

}

double Utils::rand(double high) {

	return Utils::rand() * high;

}

void Utils::randSeed(unsigned int seed) {

	std::srand(seed);

};

void Utils::randSeedTicks() {

	std::srand(std::time(nullptr));

};