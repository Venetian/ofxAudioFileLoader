/*
 *  LoadedAudioHolder.h
 *  fileLoaderAndOnsetDetection
 *
 *  Created by Andrew Robertson on 28/01/2012.
 *  Copyright 2012 QMUL. All rights reserved.
 *
 */

//Holds the player ofSoundplayer
//and the analysis - ofxSoundFileLoader
//latter consists of the audio samples - in AudioFile.h
//and the onset detection, chroma and pitch analysis - in ofxAubioOnsetDetection


#ifndef LOADED_AUDIO_HOLDER_H
#define LOADED_AUDIO_HOLDER_H


#include "ofMain.h"
#include "ofxSoundFileLoader.h"

class LoadedAudioHolder{
	
	public:

	LoadedAudioHolder();

	void updateToPlayPosition();
	void updateToMillisPosition(const double& millis);
	
	void draw();
	void windowResized(const int& w, const int& h);
	
	void loadAudioFile(string soundFileName);

	void togglePlay();//pauses if playing and vice-versa
	void stop();
	void switchScreens();
	
	void printEvents();
	
	//Samples to show or iterate through
	ofxSoundFileLoader fileLoader;
	ofSoundPlayer  loadedAudio;
	std::string loadedFileName;
	
	int trackType;
	void setTrackType(const int& type);
	
	typedef vector<double> DoubleVector;
	DoubleVector onsetTimesMillis;
	void copyOnsetTimes();
	
private:
	
	//Audio To PLay
	bool audioPlaying, audioPaused;
		

	
};
#endif
