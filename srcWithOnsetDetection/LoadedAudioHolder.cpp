/*
 *  LoadedAudioHolder.cpp
 *  fileLoaderAndOnsetDetection
 *
 *  Created by Andrew on 28/01/2012.
 *  Copyright 2012 QMUL. All rights reserved.
 *
 */

#include "LoadedAudioHolder.h"

LoadedAudioHolder::LoadedAudioHolder(){
	audioPaused = true;
	audioPlaying = false;
	trackType = 0;
}

void LoadedAudioHolder::updateToPlayPosition(){
	fileLoader.updateToAudioPosition(loadedAudio.getPosition());
}

void LoadedAudioHolder::updateToMillisPosition(const double& millis){	
	fileLoader.updateToMillisPosition(millis);
}

void LoadedAudioHolder::draw(){
	fileLoader.drawFile();
}

void LoadedAudioHolder::loadAudioFile(string soundFileName){
	loadedAudio.loadSound(soundFileName);
	fileLoader.loadNewAudio(soundFileName);
	audioPlaying = false;
	loadedFileName = soundFileName;
	copyOnsetTimes();
}

void LoadedAudioHolder::copyOnsetTimes(){

	onsetTimesMillis.clear();
	
	for (int i = 0;i < fileLoader.onsetDetect.chromaOnsets.size();i++)
		onsetTimesMillis.push_back(fileLoader.onsetDetect.chromaOnsets[i].millisTime);
}

void LoadedAudioHolder::setTrackType(const int& i){
	fileLoader.onsetDetect.trackType = i;
	trackType = i;
}

void LoadedAudioHolder::togglePlay(){
	if (!audioPlaying) {
		loadedAudio.play();
		loadedAudio.setPaused(false);
		audioPlaying = true;
		audioPaused = false;
		printf("playing %s\n", loadedFileName.c_str());
	}
	else{
		audioPaused = !audioPaused;
		loadedAudio.setPaused(audioPaused);
	}
}

void LoadedAudioHolder::stop(){
	audioPlaying = false;
	loadedAudio.setPaused(true);
	loadedAudio.setPosition(0.0);
}

void LoadedAudioHolder::switchScreens(){
	fileLoader.screenToDraw = 1 - fileLoader.screenToDraw;
}

void LoadedAudioHolder::windowResized(const int& w, const int& h){
	fileLoader.onsetDetect.windowResized(w, h);
}


void LoadedAudioHolder::printEvents(){
	for (int i = 0;i < fileLoader.onsetDetect.chromaOnsets.size();i++){
		printf("Event time %f millis %i frames pitch %f\n", fileLoader.onsetDetect.chromaOnsets[i].millisTime, 
			   fileLoader.onsetDetect.chromaOnsets[i].frameTime, fileLoader.onsetDetect.chromaOnsets[i].aubioPitch);
	}
}
