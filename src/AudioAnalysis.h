/*
 *  AudioAnalysis.h
 *  audioFileLoader4
 *
 *  Created by Andrew on 14/08/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

#ifndef AUDIO_ANALYSIS_H
#define AUDIO_ANALYSIS_H


//#include "fftw3.h"
#include "ofMain.h"
//#include "chromaGram.h"
//#include "ChordDetect.h"
#include "sndfile.h"
#include "ofxFileDialogOSX.h"
#include "AudioFile.h"

#define FRAMESIZE 512
#define ENERGY_LENGTH 80000
#define CHROMA_LENGTH 12000
#define CHROMA_CONVERSION_FACTOR 16 //16 times as many frames in energy as in chroma


//this does a chromagram analysis and aubio onset analysis
//held in double matrix and doubleVector respectively
//these are dynamic vectors, so size set by what's needed for the file

class AudioAnalysis{

public:
	
	AudioAnalysis();
	
	typedef std::vector<double> DoubleVector;
	typedef std::vector<DoubleVector> DoubleMatrix;
	
	DoubleMatrix chromaMatrix;
//	DoubleMatrix* matrixPtr;
	DoubleVector energyVector;
	
	AudioFile* audioHolder;
	void loadNewAudio(string soundFileName);//??
	
//	Chromagram chromoGramm;
	int currentPlayingFrame;
	
//	ChordDetect chord;
	
	double getEnergyOfFrame();
	int scrollWidth;
	//int totalFrames;
	void drawEnergyVectorFromPointer();
	void drawSpectralDifference();
	
	/*
	 double getEnergyOfFrame();
	
	 
	 void initialiseVariables();
	 
	 	 
	 void initialiseVariables();
	 
	 
		 AudioFile audioHolder;
	 
	 void drawDoubleMatrix(DoubleMatrix* dMatrix);//DoubleMatrix* dMatrix); WOULD BE NICE TO USE POINTER BUT NOT WORKING YET
	
	 
	 DoubleVector firstEnergyVector;
	 
	 void drawEnergyVectorFromPointer(DoubleVector* energyVec);
	 
	 void processAudioToDoubleMatrix(Chromagram* chromaG, DoubleMatrix* myDoubleMatrix, DoubleVector* energyVector);
	 
	 void loadNewAudio(string soundFileName);
	 
	 
	 
	 */
	
	
};
#endif



