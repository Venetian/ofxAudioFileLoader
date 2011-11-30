/*
 *  SoundFileLoader.h
 *  audioFileLoaderSVN1
 *
 *  Created by Andrew on 04/09/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

#ifndef SOUND_FILE_LOADER_H
#define SOUND_FILE_LOADER_H


#include "ofMain.h"
#include "sndfile.h"
#include "AudioFile.h"

#define FRAMESIZE 512


//this does a chromagram analysis and aubio onset analysis
//held in double matrix and doubleVector respectively
//these are dynamic vectors, so size set by what's needed for the file

class SoundFileLoader{
	
public:
	SoundFileLoader();
	float frame[FRAMESIZE]; 
	
	void loadLibSndFile(const char *infilename);

	typedef std::vector<double> DoubleVector;
		typedef std::vector<DoubleVector> DoubleMatrix;

	//DoubleVector leftAudioSamples;
	//DoubleMatrix multichannelAudioSamples;
	AudioFile audioHolder;
	
	int totalNumberOfFrames;
	
	void readAudio();
	
	SNDFILE *infile; // define input and output sound files
	SF_INFO sfinfo ; // struct to hold info about sound file

};
#endif
