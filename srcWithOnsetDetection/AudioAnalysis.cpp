/*
 *  AudioAnalysis.cpp
 *  audioFileLoader4
 *
 *  Created by Andrew on 14/08/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

#include "AudioAnalysis.h"


AudioAnalysis::AudioAnalysis(){
//	chromoGramm.initialise(FRAMESIZE,2048);

	scrollWidth = 1600;
	
}



void AudioAnalysis::drawEnergyVectorFromPointer(){
	DoubleVector* energyVec;
	energyVec = &energyVector;
	//xxx above
	
	ofSetColor(0xFF0066);
	float screenHeight = ofGetHeight() ;
	float screenWidth = ofGetWidth();  
	float heightFactor = 8;
	int i, j, startingFrame;
	startingFrame = currentPlayingFrame / scrollWidth;//i.e. number of scroll widths in
	startingFrame *= scrollWidth;
	
	for (i = 0; i < scrollWidth - 1; i++){
		j = i + startingFrame;
		if (j < (*energyVec).size())
			ofLine(i*screenWidth/scrollWidth, screenHeight - ((*energyVec)[j]*screenHeight/heightFactor),
				   screenWidth*(i+1)/scrollWidth, screenHeight - ((*energyVec)[j+1]*screenHeight/heightFactor));
		
	}
}

void AudioAnalysis::drawSpectralDifference(){
	DoubleMatrix* dMatrix;
	dMatrix = &chromaMatrix;
	//get rid of these!
	
	int matrixSize = (*dMatrix).size();
	if (matrixSize > 0){
		
		float screenHeight = ofGetHeight() ;
		float screenWidth = ofGetWidth();
		float heightFactor = 8;
		double difference;
		int i, j, startingFrame;
		startingFrame = currentPlayingFrame / scrollWidth;//i.e. number of scroll widths in
		startingFrame *= scrollWidth;//starting frame in terms of energy frames
		startingFrame /= CHROMA_CONVERSION_FACTOR; //in terms of chroma frames
		
		float chromoLength = scrollWidth/CHROMA_CONVERSION_FACTOR;
		for (i = 1; i < chromoLength; i++){//changed to add 1
			j = i + startingFrame;
			for (int y = 0;y < 12;y++){			
				
				if (j < matrixSize)
					difference = (*dMatrix)[j][11-y] - (*dMatrix)[j-1][11-y];
				else 
					difference = 0;
				
				if (difference < 0)
					difference = 0;//half wave rectify
				
				ofSetColor(0,0,255 * difference);//, 0;
				ofRect(i*screenWidth/chromoLength,y*screenHeight/12,screenWidth/chromoLength,screenHeight/12);
			}//end y
		}//end i
		
	}///end if matrix has content
	else{
		printf("Error - please load audio first");
	}
	
}


/*
void testApp::initialiseVariables(){
	
	energyIndex = 0;
	//	frameIndex = 0;
	chromaIndex = 0;
	chromoGramm.initialise(FRAMESIZE,2048);//framesize 512 and hopsize 2048
}


//--------------------------------------------------------------
void testApp::draw(){
	switch (screenToDraw){
		case 0:
			if (drawSpectralDifferenceFunction)
				drawSpectralDifference(&chromaMatrix);
			else
				drawDoubleMatrix(&chromaMatrix);
			
			drawEnergyVectorFromPointer(&firstEnergyVector);
			break;
		case 1:
			//	audioHolder.drawAudioVectorMillis(1000, 1000+audioScale);
			audioHolder.drawAudioVectorSamples(audioHolder.playPosition, audioHolder.playPosition+audioHolder.audioScaleSamples);
			break;
	}
	
	
	
	//ofSetColor(255,0,0);
	//drawEnergyVectorFromPointer(&audioVector);
	
	ofSetColor(0xFFFFFF);
	ofLine(audioPosition*width, 0, audioPosition*width, height);
	
	ofDrawBitmapString(soundFileName,80,480);
	
}


void testApp::drawEnergyVectorFromPointer(DoubleVector* energyVec){
	
	ofSetColor(0xFF0066);
	float screenHeight = ofGetHeight() ;
	float screenWidth = ofGetWidth();  
	float heightFactor = 8;
	int i, j, startingFrame;
	startingFrame = currentPlayingFrame / scrollWidth;//i.e. number of scroll widths in
	startingFrame *= scrollWidth;
	
	for (i = 0; i < scrollWidth - 1; i++){
		j = i + startingFrame;
		if (j < (*energyVec).size())
			ofLine(i*screenWidth/scrollWidth, screenHeight - ((*energyVec)[j]*screenHeight/heightFactor),
				   screenWidth*(i+1)/scrollWidth, screenHeight - ((*energyVec)[j+1]*screenHeight/heightFactor));
		
	}
}

void testApp::drawSpectralDifference(DoubleMatrix* dMatrix){
	int matrixSize = (*dMatrix).size();
	if (matrixSize > 0){
		
		float screenHeight = ofGetHeight() ;
		float screenWidth = ofGetWidth();
		float heightFactor = 8;
		double difference;
		int i, j, startingFrame;
		startingFrame = currentPlayingFrame / scrollWidth;//i.e. number of scroll widths in
		startingFrame *= scrollWidth;//starting frame in terms of energy frames
		startingFrame /= CHROMA_CONVERSION_FACTOR; //in terms of chroma frames
		
		float chromoLength = scrollWidth/CHROMA_CONVERSION_FACTOR;
		for (i = 1; i < chromoLength; i++){//changed to add 1
			j = i + startingFrame;
			for (int y = 0;y < 12;y++){			
				
				if (j < matrixSize)
					difference = (*dMatrix)[j][11-y] - (*dMatrix)[j-1][11-y];
				else 
					difference = 0;
				
				if (difference < 0)
					difference = 0;//half wave rectify
				
				ofSetColor(0,0,255 * difference);//, 0;
				ofRect(i*screenWidth/chromoLength,y*screenHeight/12,screenWidth/chromoLength,screenHeight/12);
			}//end y
		}//end i
		
	}///end if matrix has content
	else{
		printf("Error - please load audio first");
	}
	
}


void testApp::drawDoubleMatrix(DoubleMatrix* dMatrix){
	//used to draw the chromagram matrix
	int matrixSize = (*dMatrix).size();
	if (matrixSize > 0){
		
		float screenHeight = ofGetHeight() ;
		float screenWidth = ofGetWidth();
		float heightFactor = 8;
		int i, j, startingFrame;
		startingFrame = currentPlayingFrame / scrollWidth;//i.e. number of scroll widths in
		startingFrame *= scrollWidth;//starting frame in terms of energy frames
		startingFrame /= CHROMA_CONVERSION_FACTOR; //in terms of chroma frames
		
		float chromoLength = scrollWidth/CHROMA_CONVERSION_FACTOR;
		for (i = 0; i < chromoLength; i++){
			j = i + startingFrame;
			for (int y = 0;y < 12;y++){
				
				if (j < matrixSize)
					ofSetColor(0,0,255 * (*dMatrix)[j][11-y]);
				else 
					ofSetColor(0,0,0);
				
				ofRect(i*screenWidth/chromoLength,y*screenHeight/12,screenWidth/chromoLength,screenHeight/12);
			}//end y
		}//end i
		
	}///end if matrix has content
	else{
		printf("Error - please load audio first");
	}
	
	
}





*/


