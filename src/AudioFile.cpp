/*
 *  audioFile.cpp
 *  audioFileLoader3
 *
 *  Created by Andrew on 31/07/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

#include "AudioFile.h"

const double samplingFrequency = 44100.0;

AudioFile::AudioFile(){
	audioScaleSamples = 44100.;
	playPosition = 0;
}

void AudioFile::drawAudioVectorMillis(double startTimeMillis, double endTimeMillis){
	
	double startTimeSamples = startTimeMillis * samplingFrequency / 1000.0;
	double endTimeSamples = endTimeMillis * samplingFrequency / 1000.0;
	double screenHeight = ofGetHeight() ;
	double screenWidth = ofGetWidth(); 
	
	ofSetColor(255,0,0);
	double numberOfSamples = endTimeSamples - startTimeSamples;
	double samplesPerPixel = numberOfSamples / screenWidth;
	string samplesString = "millis : sps ";
	samplesString += ofToString(samplesPerPixel, 2);
	samplesString += " , \n";
	
	int lastSampleIndex = (int) startTimeSamples;
	
	for (int i = 1;i < screenWidth;i++){// && startTimeSamples + samplesPerPixel * i < endTimeSamples;i += 1){
		int sampleIndex = (int) min((startTimeSamples + samplesPerPixel * i), (double) length-1);
			//if (sampleIndex < 0)
			//	sampleIndex = 0;
		ofLine(i-1, screenHeight - (1-audioVector[sampleIndex])*screenHeight/2.0 , i, screenHeight - (1-audioVector[lastSampleIndex])*screenHeight/2.0);
		samplesString += ofToString(audioVector[i])+"  , \n";
		lastSampleIndex = sampleIndex;
		
	}
	ofDrawBitmapString(samplesString, 20,20);	
	
}



void AudioFile::drawAudioVectorSamples(double startTimeSample, double endTimeSample){
	
	screenHeight = ofGetHeight() ;
	double screenWidth = ofGetWidth(); 
	
	ofSetColor(255,0,0);
	double numberOfSamples = endTimeSample - startTimeSample;
	double samplesPerPixel = numberOfSamples / screenWidth;
	
	double halfHeight = screenHeight/2;
	
	int lastSampleIndex = (int) startTimeSample;
	/*
	for (int i = 1;i < screenWidth;i++){// && startTimeSamples + samplesPerPixel * i < endTimeSamples;i += 1){
		int sampleIndex = (int) (startTimeSample + samplesPerPixel * i);
		ofLine(i-1, screenHeight - (1-audioVector[sampleIndex])*screenHeight/2.0 , i, screenHeight - (1-audioVector[lastSampleIndex])*screenHeight/2.0);
		lastSampleIndex = sampleIndex;
		
	}
	*/
	double firstXpos = halfHeight;
	double firstYpos = getPosition(startTimeSample);//screenHeight - ((1-audioVector[startTimeSample])*screenHeight/2.0);
	
	int stepSize = 1;//(int) samplesPerPixel); optimize !! XXX
	for (int sampleIndex = startTimeSample+1;sampleIndex < min(endTimeSample, (double) length);sampleIndex+= stepSize){

		double secondXpos = (sampleIndex - startTimeSample) * screenWidth/numberOfSamples;
		double secondYpos = getPosition(sampleIndex);//screenHeight - ((1-audioVector[sampleIndex])*screenHeight/2.0);
		ofLine(firstXpos, firstYpos, secondXpos, secondYpos);
		
			if (numberOfSamples < 100)
				ofCircle(secondXpos, secondYpos, 2);
		
		firstXpos = secondXpos;
		firstYpos = secondYpos;
		
		
	}

	string samplesString = "samples: sps " + ofToString(samplesPerPixel, 2);
	samplesString += ", number of smaplers " + ofToString(numberOfSamples, 2);
	samplesString += " , \n";
	
	
	//info string
	string textString;
	textString = ofToString(playPosition, 1);
	ofDrawBitmapString(textString, 20, 20);
	ofDrawBitmapString(samplesString, 20, 60);

	
	
	ofSetColor(0,0,255);
	ofLine(0, halfHeight, screenWidth, halfHeight);
	
}
/*
double testApp::getXposition(int index, int startTimeSampleIndex){
	if (index >= 0 && index < audioVector.size())
		return (index - startTimeSampleIndex) * screenWidth/numberOfSamples;
}
*/
double AudioFile::getPosition(int index){
	if (index >= 0 && index < audioVector.size())
		return screenHeight - ((1-audioVector[index])*screenHeight/2.0);
	else
		return screenHeight /2 ;
}	


/*
void AudioFile::drawAudioVectorSamples(double startTimeSample, double endTimeSample){
	
	double screenHeight = ofGetHeight() ;
	double screenWidth = ofGetWidth(); 
	
	ofSetColor(255,0,0);
	double numberOfSamples = endTimeSample - startTimeSample;
	double samplesPerPixel = numberOfSamples / screenWidth;
	
	double halfHeight = screenHeight/2;
	
	string samplesString = "samples: sps " + ofToString(samplesPerPixel, 2);
	samplesString += ", number of smaplers " + ofToString(numberOfSamples, 2);
	samplesString += " , \n";
	
	int lastSampleIndex = (int) startTimeSample;
	
	for (int i = 1;i < screenWidth;i++){// && startTimeSamples + samplesPerPixel * i < endTimeSamples;i += 1){
		int sampleIndex = (int) (startTimeSample + samplesPerPixel * i);
		ofLine(i-1, screenHeight - (1-audioVector[sampleIndex])*screenHeight/2.0 , i, screenHeight - (1-audioVector[lastSampleIndex])*screenHeight/2.0);
		lastSampleIndex = sampleIndex;
		
	}
	//info string
	string textString;
	textString = ofToString(playPosition, 1);
	ofDrawBitmapString(textString, 20, 20);
	ofDrawBitmapString(samplesString, 20, 60);
	
	
	
	ofSetColor(0,0,255);
	ofLine(0, halfHeight, screenWidth, halfHeight);
	
}
 */

