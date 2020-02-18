#include <iostream>
#include <cassert>
#include "simulation.h"
using namespace std;
using namespace simulationspace;

//AVERAGER CLASS
averageTime::averageTime(double t, int c)
{
	total = t;
	counter = c;
}

void averageTime::addNumber(int num)
{
	total += num;
	counter++;
}

double averageTime::average() const
{
	assert(numberCount() > 0);
	return ((double)total / counter);
}

int averageTime::numberCount() const
{
	return counter;
}

//BOOLSOURCE CLASS
boolSource::boolSource(double p)
{
	assert(p >= 0); 
	assert(p <= 1);
	probability = p;
}

bool boolSource::queryCall() const
{
	return (rand() < (probability * 32767));
}

//RUNWAY CLASS
Runway::Runway(unsigned int s)
{
	activitySeconds = s;
	activityTimeLeft = 0;
}

void Runway::oneMinute()
{
	if (isBusy()) activityTimeLeft--;
}

void Runway::startActivity()
{
	assert(!isBusy()); 
	activityTimeLeft = activitySeconds;

}

bool Runway::isBusy() const
{
	return (activityTimeLeft > 0);
}
