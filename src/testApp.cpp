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

	ofBackground(255,255,255);
	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();
	
	drawOnsetFunction = false;

	sampleRate 			= 44100;

	ofSoundStreamSetup(2,0,this, sampleRate,256, 4);
//UNTIL HERE
	
	
	ofSetFrameRate(60);

	audioScale = 1000.0;

	//moveOn = true;

	//loading audio files

	const char	*infilename = "../../../data/sound/bach4_short1.wav";	
	loadNewAudio(infilename);
	
	audioPlaying = false;


	screenToDraw = 0;
	

}


void testApp::initialiseVariables(){
	
//	chromoGramm.initialise(FRAMESIZE,2048);//framesize 512 and hopsize 2048
}


//--------------------------------------------------------------
void testApp::update(){

	audioPosition = loadedAudio.getPosition() * fileLoader.totalNumberOfFrames;//frameIndex;//the position in number of frames
//	fileLoader.chromaAnalysis.currentPlayingFrame = audioPosition;
//	audioPosition = (int) audioPosition % fileLoader.chromaAnalysis.scrollWidth ;
//	audioPosition /= fileLoader.chromaAnalysis.scrollWidth;
	
	fileLoader.audioHolder.playPosition = loadedAudio.getPosition() * fileLoader.audioHolder.audioVector.size();
}

//--------------------------------------------------------------
void testApp::draw(){

	fileLoader.audioHolder.drawAudioVectorSamples(fileLoader.audioHolder.playPosition - fileLoader.audioHolder.audioScaleSamples*0.5, fileLoader.audioHolder.playPosition+fileLoader.audioHolder.audioScaleSamples*0.5);
	ofSetColor(100,100,100);
	ofLine(screenWidth/2, 0, screenWidth/2, screenHeight);
	ofDrawBitmapString(soundFileName,80,480);
	

	
		
}


void testApp::loadNewAudio(string soundFileName){
	
	loadedAudio.loadSound(soundFileName);
	
	//snd file method
	const char	*infilename = soundFileName.c_str() ;
	fileLoader.loadLibSndFile(infilename);
	
	audioPlaying = false;
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
		screenToDraw = 1 - screenToDraw;

	
	if (key == OF_KEY_RIGHT){
		loadedAudio.setPosition(min(1.0, loadedAudio.getPosition() + (fileLoader.audioHolder.audioScaleSamples/(4.0*fileLoader.audioHolder.audioVector.size()))) );
//	audioHolder.playPosition = loadedAudio.getPosition() * audioHolder.audioVector.size();
	}
	
	if (key == OF_KEY_LEFT){
		loadedAudio.setPosition(max(0.0, loadedAudio.getPosition() - (fileLoader.audioHolder.audioScaleSamples/(4.0*fileLoader.audioHolder.audioVector.size()))));
		//	audioHolder.playPosition = loadedAudio.getPosition() * audioHolder.audioVector.size();
	}

		
		if (key == ' '){
			if (!audioPlaying) {
				loadedAudio.play();
				loadedAudio.setPaused(false);
				audioPlaying = true;
				audioPaused = false;
			}
			else{
			audioPaused = !audioPaused;
			loadedAudio.setPaused(audioPaused);
			}
		
		}

	if (key == OF_KEY_RETURN){
			audioPlaying = false;
			loadedAudio.setPaused(true);
		loadedAudio.setPosition(0.0);
	}
	
	
	if (key == 'o'){
		openNewAudioFileWithdialogBox();
	}


	
	if (key == OF_KEY_UP){
		audioScale *= 2.;
		fileLoader.audioHolder.audioScaleSamples *= 2.;
	}
	
	if (key == OF_KEY_DOWN){
		audioScale /= 2.;	
		fileLoader.audioHolder.audioScaleSamples /= 2.;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

void testApp::openNewAudioFileWithdialogBox(){
	
	//open audio file
	string *filePtr;
	filePtr = &soundFileName;	
	
	if (getFilenameFromDialogBox(filePtr)){
		printf("Mainfile: Loaded name okay :\n'%s' \n", soundFileName.c_str());	
	}
	
	loadNewAudio(soundFileName);

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
width = w;
height = h;
	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();
	
}

//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
	//pan = 0.5f;
//	float leftScale = 1 - pan;
//	float rightScale = pan;

}


//--------------------------------------------------------------


bool testApp::getFilenameFromDialogBox(string* fileNameToSave){
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

void testApp::openFileDialogBox(){

	// first, create a string that will hold the URL
	string URL;
	
	// openFile(string& URL) returns 1 if a file was picked
	// returns 0 when something went wrong or the user pressed 'cancel'
	int response = ofxFileDialogOSX::openFile(URL);
	if(response){
		// now you can use the URL 
		soundFileName = URL;//"URL to open: \n "+URL;
	}else {
		soundFileName = "OPEN canceled. ";
	}
	
	

}





