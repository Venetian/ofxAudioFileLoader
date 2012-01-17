/*
 *  ofxSoundFileLoader.h
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
#include "ofxAubioOnsetDetection.h"

#define FRAMESIZE 512



class ofxSoundFileLoader{
	
public:
	ofxSoundFileLoader();
	~ofxSoundFileLoader();
	float frame[FRAMESIZE]; 
	
	void loadLibSndFile(const char *infilename);

	typedef std::vector<double> DoubleVector;
//	typedef std::vector<DoubleVector> DoubleMatrix;


	AudioFile audioHolder;
	
	ofxAubioOnsetDetection* onsetDetect;
	
	int totalNumberOfSamples;
	
	void readAudio();
	
	SNDFILE *infile; // define input and output sound files
	SF_INFO sfinfo ; // struct to hold info about sound file

};
#endif
