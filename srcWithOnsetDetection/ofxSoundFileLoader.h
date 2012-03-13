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
	
	void updateToAudioPosition(const float& audioPosition);
	void updateToMillisPosition(const double& millis);
	void drawFile();
	void zoomOut();
	void zoomIn();
	
	void loadLibSndFile(const char *infilename);

//	void openNewFileWithDialogBox();
	void loadNewAudio(std::string filename);
	
	typedef std::vector<double> DoubleVector;
//	typedef std::vector<DoubleVector> DoubleMatrix;

	//0 draws audio vector samples
	//1 draws the onset fn, pitch and chroma data
	int screenToDraw;
	
	AudioFile audioHolder;
	
	ofxAubioOnsetDetection onsetDetect;
	
	int totalNumberOfSamples;
	
	void readAudio();
	
	string soundFileName;
	SNDFILE *infile; // define input and output sound files
	SF_INFO sfinfo ; // struct to hold info about sound file
	
	

};
#endif
