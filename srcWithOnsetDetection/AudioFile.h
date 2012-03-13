/*
 *  audioFile.h
 *  audioFileLoader3
 *
 *  Created by Andrew on 31/07/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

//Holds the actual samples loaded in from the audio file
//in a double matrix, so multilpe channels used


#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include "ofMain.h"


class AudioFile
{
public:		
	AudioFile();											// constructor
//	~AudioFile();
	
	
	
	void drawAudioVectorMillis(double startTimeMillis, double endTimeMillis);
	void drawAudioVectorSamples(double startTimeSample, double endTimeSample);
	double getPosition(int index);
	
	typedef std::vector<double> DoubleVector;
	typedef std::vector<DoubleVector> DoubleMatrix;
	DoubleVector audioVector;
	DoubleMatrix audioMatrix;
	
	double screenHeight;
	int length;
	double audioScaleSamples;
	double playPosition;//in samples
	
};

#endif