#include "testApp.h"
#include "stdio.h"
//#include "aubio.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib> 


const double samplingFrequency = 44100.0;
	
//--------------------------------------------------------------
void testApp::setup(){

	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	//nb THIS CODE WOULD BE USEFUL IF WE EVER WANTED REAL-TIME INPUT - VIA ofSoundSteam
	

	
	sampleRate 			= 44100;
	ofSoundStreamSetup(2,0,this, sampleRate,256, 4);

	ofSetFrameRate(30);

	//loading audio files
	const char	*infilename = "../../../data/sound/bach4_short1.wav";	
	loadNewAudio(infilename);


}



//--------------------------------------------------------------
void testApp::update(){

	audioFilePlayer.updateToPlayPosition();
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	audioFilePlayer.draw();

}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (key == '-'){
		volume -= 0.05;
		volume = MAX(volume, 0);
	} else if (key == '+'){
		volume += 0.05;
		volume = MIN(volume, 1);
	}

	if (key == 'q')
		audioFilePlayer.switchScreens();

	
	if (key == OF_KEY_RIGHT){
		audioFilePlayer.loadedAudio.setPosition(min(1.0, audioFilePlayer.loadedAudio.getPosition() + (audioFilePlayer.fileLoader.audioHolder.audioScaleSamples/(4.0*audioFilePlayer.fileLoader.audioHolder.audioVector.size()))) );

	}
	
	if (key == OF_KEY_LEFT){
		audioFilePlayer.loadedAudio.setPosition(max(0.0, audioFilePlayer.loadedAudio.getPosition() - (audioFilePlayer.fileLoader.audioHolder.audioScaleSamples/(4.0*audioFilePlayer.fileLoader.audioHolder.audioVector.size()))));
		
	}
	
	
		if (key == ' '){
		audioFilePlayer.togglePlay();
	}

	if (key == OF_KEY_RETURN){
		audioFilePlayer.stop();
	}
	
	
	if (key == 'o'){
		openNewAudioFileWithdialogBox();

	}


	
	if (key == OF_KEY_UP){
		audioFilePlayer.fileLoader.zoomOut();
	}
	
	if (key == OF_KEY_DOWN){
		audioFilePlayer.fileLoader.zoomIn();

	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){


}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

	audioFilePlayer.windowResized(w, h);
	
	
}
//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
	//pan = 0.5f;
	float leftScale = 1 - pan;
	float rightScale = pan;

}



//--------------------------------------------------------------
void testApp::openNewAudioFileWithdialogBox(){
	std::string filename;
	getFilenameFromDialogBox(&filename);
	loadNewAudio(filename);
	
}


void testApp::loadNewAudio(string soundFileName){
	audioFilePlayer.loadAudioFile(soundFileName);
	/*
	loadedAudio.loadSound(soundFileName);
	fileLoader.loadNewAudio(soundFileName);
	audioPlaying = false;
	 */
}


bool testApp::getFilenameFromDialogBox(std::string* fileNameToSave){
	//this uses a pointer structure within the loader and returns true if the dialogue box was used successfully
	// first, create a string that will hold the URL
	string URL;
	
	// openFile(string& URL) returns 1 if a file was picked
	// returns 0 when something went wrong or the user pressed 'cancel'
	int response = ofxFileDialogOSX::openFile(URL);
	if(response){
		// now you can use the URL 
		*fileNameToSave = URL;
		//printf("\n filename is %s \n", soundFileName.c_str());
		return true;
	}
	else {
	//	soundFileName = "OPEN canceled. ";
		printf("\n open file cancelled \n");
		return false;
	}
	
}
 




