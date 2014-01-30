/*
 * Code for hill climbing
 */

#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <sstream>
#include <fstream>

// Modify initial temperature and decrement value for fast convergence!
#define INITTEMP 30
#define DECREMENT 1
using namespace std;

class __HILL_CLIMB{
private:
	float curr_temperature;
	float initTemperature;
	vector<double> curr_coordinates, init_coordinates, bestCoord;
	vector<double> curr_stepSize, init_stepSize;
	int dimensions;
	float max,bestScore;
	std::map<double, vector<double> > registeredScores;
	std::vector<bool> prevStep;	// true is positive and false is negative
protected:
	std::string stringcoordinates(){
		stringstream ss;
	   ss <<	curr_coordinates[0] << ", " <<curr_coordinates[1];
		return ss.str();
	}
	void changeStepSize(){
		for(int n=0;n<dimensions;n++){
			curr_stepSize[n] = init_stepSize[n] * (curr_temperature/initTemperature);
		}
	}
	void decreaseTemperature(){
		curr_temperature -= DECREMENT; 
	}
	void nextMonoStep(int n){
		if(prevStep[n]==true){
			curr_coordinates[n] += curr_stepSize[n];
		}
		else{
			curr_coordinates[n] -= curr_stepSize[n];
		}
		return;
	}
	void nextSwapStep(int n){
		if(prevStep[n]==true){
			curr_coordinates[n] -= 2*curr_stepSize[n];
			prevStep[n]=false;
		}
		else{
			curr_coordinates[n] += 2*curr_stepSize[n];
			prevStep[n]=true;
		}
		return;
	}
	void registerScore(double score, vector<double> coord){
		if(score > bestScore){
			bestScore=score;
			bestCoord=coord;
		}
	}

public:


	__HILL_CLIMB(float initTemp, string filename) :
		initTemperature(initTemp),curr_temperature(initTemp){
		max=-9999999.0;
		bestScore=-9999999.0;

//		read initial coordinates and step sizes
		ifstream file;
		file.open(filename.c_str(), ios_base::in);
		file >> dimensions;
		for(int n=0;n<dimensions;n++){
			double coord;
			file >> coord;
			init_coordinates.push_back(coord);
		}
		curr_coordinates = init_coordinates;
		for(int n=0;n<dimensions;n++){
			double step;
			file >> step;
			init_stepSize.push_back(step);
		}
		curr_stepSize=init_stepSize;
		prevStep.resize(dimensions);
		for(int n=0;n<dimensions;n++){
			prevStep[n]=true;
		}
	}
	void Optimize(){
//		start with the current coordinates, change one dimensioned coordinate at one time and then evaluate the function
		for(int i=0;i<30;i++){
			double score=getScore();
			for(int n=0;n<dimensions;n++){
				if(score>max){
					nextMonoStep(n);
					max=score;
				}
				else{
					nextSwapStep(n);
				}
				score=getScore();
				registerScore(score,curr_coordinates);
			}
			decreaseTemperature();
			if(curr_temperature<0) {return;}
			changeStepSize();
		}
		return;
	}
	vector<double> retrieveBestCoordinates(){
		cerr<<"Best Score : "<<bestScore<<endl;
		return bestCoord;
	}
/*This is a simple function, change it according to your needs*/
	double getScore(){
/*		for(int i=0;i<dimensions;i++){
			cout<<curr_coordinates[i]<<" ";
		}
		double score;
		cin>>score;
		return score;
*/
// default function to test univariate function
//		return -1 * pow((curr_coordinates[0]-1),2);
	
// default function to test bi-variate function
		return -1 * (pow(curr_coordinates[0],2) + pow(curr_coordinates[1],2));
	}
};

int main(int argc, char *argv[])
{
	string filename(argv[1]);
	__HILL_CLIMB hc(INITTEMP, filename);
	hc.Optimize();
	vector<double> x=hc.retrieveBestCoordinates();
	cerr<<"Best Coordinates : ";
	for(int i=0;i<x.size();i++){
		cerr<<x[i]<<" ";
	}
	cerr<<endl;
}
