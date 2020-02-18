#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

namespace simulationspace {
	//AVERAGER: RETURN AVERAGE TIME
	class averageTime {
	private:
		double total;
		int counter;

	public:
		averageTime(double t = 0, int c = 0);
		void addNumber(int num);
		double average() const;
		int numberCount() const;
	};

	//BOOLSOURCE: RUNWAY HELPER
	class boolSource {
	private:
		double probability;

	public:
		boolSource(double p = 0.5);
		bool queryCall() const;
	};

	//RUNWAY
	class Runway {
	private: 
		unsigned int activitySeconds;
		unsigned int activityTimeLeft;

	public:
		Runway(unsigned int s = 60);
		void oneMinute( ); 
		void startActivity( );
		bool isBusy() const;
	};
}

#endif