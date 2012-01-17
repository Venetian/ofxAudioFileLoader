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
	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	//nb THIS CODE WOULD BE USEFUL IF WE EVER WANTED REAL-TIME INPUT - VIA ofSoundSteam
	

//	ofSetDataPathRoot("../bin/data/");

//DONT NEED ANY OF THIS
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


	screenToDraw = 1;
	

}


void testApp::initialiseVariables(){
	
//	chromoGramm.initialise(FRAMESIZE,2048);//framesize 512 and hopsize 2048
}


//--------------------------------------------------------------
void testApp::update(){

	audioPosition = loadedAudio.getPosition() * fileLoader.totalNumberOfSamples;//frameIndex;//the position in number of frames
//	fileLoader.chromaAnalysis.currentPlayingFrame = audioPosition;
//	audioPosition = (int) audioPosition % fileLoader.chromaAnalysis.scrollWidth ;
//	audioPosition /= fileLoader.chromaAnalysis.scrollWidth;
	
	fileLoader.audioHolder.playPosition = loadedAudio.getPosition() * fileLoader.audioHolder.audioVector.size();
	fileLoader.onsetDetect->playPosition = loadedAudio.getPosition();
}

//--------------------------------------------------------------
void testApp::draw(){
	if (screenToDraw == 0){
	fileLoader.audioHolder.drawAudioVectorSamples(fileLoader.audioHolder.playPosition - fileLoader.audioHolder.audioScaleSamples*0.5, fileLoader.audioHolder.playPosition+fileLoader.audioHolder.audioScaleSamples*0.5);
	ofSetColor(100,100,100);
	ofLine(screenWidth/2, 0, screenWidth/2, screenHeight);
	ofDrawBitmapString(soundFileName,80,480);
	}else{
	fileLoader.onsetDetect->drawOnsetDetection();
	}
	
		
}


/*
void testApp::drawDoubleMatrix(DoubleMatrix* dMatrix){
	//used to draw the chromagram matrix
	int matrixSize = (*dMatrix).size();
	if (matrixSize > 0){
			
	float screenHeight = ofGetHeight() ;
	float screenWidth = ofGetWidth();
	float heightFactor = 8;
	int i, j, startingFrame;
	startingFrame = fileLoader.chromaAnalysis.currentPlayingFrame / fileLoader.chromaAnalysis.scrollWidth;//i.e. number of scroll widths in
	startingFrame *= fileLoader.chromaAnalysis.scrollWidth;//starting frame in terms of energy frames
	startingFrame /= CHROMA_CONVERSION_FACTOR; //in terms of chroma frames
	
	float chromoLength = fileLoader.chromaAnalysis.scrollWidth/CHROMA_CONVERSION_FACTOR;
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



/*
void testApp::loadLibSndFile(const char *infilename){
	
	if (!sf_close(infile)){
		printf("closed sndfile okay \n");
	}
	
	// Open Input File with lib snd file
    if (! (infile = sf_open (infilename, SFM_READ, &sfinfo)))
    {   // Open failed
        printf ("SF OPEN routine Not able to open input file %s.\n", infilename) ;
        // Print the error message from libsndfile. 
        puts (sf_strerror (NULL)) ;
		
	} else{
		printf("SF OPEN : file %s okay, ", infilename);
		printf("number of channels is %i\n", sfinfo.channels);
		sndfileInfoString = "Opened okay ";
		
	};
	
}
*/

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
/*	
	if (key == OF_KEY_DOWN){
		if (fileLoader.chromaAnalysis.scrollWidth > 600)
		fileLoader.chromaAnalysis.scrollWidth += 400;
		else
		fileLoader.chromaAnalysis.scrollWidth *= 2;
	}
 */
	
	if (key == OF_KEY_RIGHT){
		loadedAudio.setPosition(min(1.0, loadedAudio.getPosition() + (fileLoader.audioHolder.audioScaleSamples/(4.0*fileLoader.audioHolder.audioVector.size()))) );
//	audioHolder.playPosition = loadedAudio.getPosition() * audioHolder.audioVector.size();
	}
	
	if (key == OF_KEY_LEFT){
		loadedAudio.setPosition(max(0.0, loadedAudio.getPosition() - (fileLoader.audioHolder.audioScaleSamples/(4.0*fileLoader.audioHolder.audioVector.size()))));
		//	audioHolder.playPosition = loadedAudio.getPosition() * audioHolder.audioVector.size();
	}
	
	/*
	if (key == OF_KEY_UP){
		if (fileLoader.chromaAnalysis.scrollWidth > 600)
		fileLoader.chromaAnalysis.scrollWidth -= 400;
		else
		fileLoader.chromaAnalysis.scrollWidth /= 2;
	}
	 */
		
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
		if (screenToDraw == 0){
		audioScale *= 2.;
		fileLoader.audioHolder.audioScaleSamples *= 2.;}
		if (screenToDraw == 1){
			
			fileLoader.onsetDetect->amplitudeNumber *= 2;
		}
	}
	
	if (key == OF_KEY_DOWN){
		if (screenToDraw == 0){
		audioScale /= 2.;	
			fileLoader.audioHolder.audioScaleSamples /= 2.;
		}
		if (screenToDraw == 1 && 	fileLoader.onsetDetect->amplitudeNumber > 2){
			fileLoader.onsetDetect->amplitudeNumber /= 2;
		}
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

void testApp::openNewAudioFileWithdialogBox(){
	
	//open audio file
//	string *filePtr;
//	filePtr = &soundFileName;	
	
	if (getFilenameFromDialogBox(&soundFileName)){
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
	float leftScale = 1 - pan;
	float rightScale = pan;

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


void testApp::loadNewAudio(string soundFileName){

	loadedAudio.loadSound(soundFileName);
	
	//snd file method
	const char	*infilename = soundFileName.c_str() ;
	fileLoader.loadLibSndFile(infilename);

	audioPlaying = false;
}





/*
 
double testApp::getEnergyOfFrame(){
	
	float totalEnergyInFrame = 0;
	
	for (int i = 0;i<FRAMESIZE;i++){
		
		totalEnergyInFrame += (frame[i] * frame[i]);
		
	}
	totalEnergyInFrame = sqrt(totalEnergyInFrame);
	
	return totalEnergyInFrame;
}

*/


//JUNK METHODS BEFORE SWITCHING TO VECTORS TO HOLD ENERGY AND CHROMA
//THESE ARE BETTER AS THEY ARE DYNAMIC

/*
 void testApp::drawChromoGram(){
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
 ofSetColor(255*chromoGramVector[j][11-y],0,0);
 ofRect(i*screenWidth/chromoLength,y*screenHeight/12,screenWidth/chromoLength,screenHeight/12);
 }//end y
 }//end i
 
 }
 */



/*
 void testApp::drawChromaMatrix(){
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
 ofSetColor(0,255*chromaMatrix[j][11-y],0);
 ofRect(i*screenWidth/chromoLength,y*screenHeight/12,screenWidth/chromoLength,screenHeight/12);
 }//end y
 }//end i
 
 }
 */




/*
 
 
 int readcount = 1; // counts number of samples read from sound file
 printf("processing audio from doublematrix \n");
 
 while(readcount != 0 && moveOn == true)
 {
 
 // read FRAMESIZE samples from 'infile' and save in 'data'
 readcount = sf_read_float(infile, frame, FRAMESIZE);
 
 
 for (int i = 0;i < FRAMESIZE;i++)
 audioHolder.audioVector.push_back(frame[i]);
 
 printf("frame%f\n", frame[0]);
 //processing frame - downsampled to 11025Hz
 //8192 samples per chroma frame
 chromaG->processframe(frame);
 
 if (chromaG->chromaready)
 {
 DoubleVector d;
 
 for (int i = 0;i<12;i++){
 //chromoGramVector[chromaIndex][i] = chromoGramm.rawChroma[i] / chromoGramm.maximumChromaValue;
 d.push_back(chromaG->rawChroma[i]);// / chromaG->maximumChromaValue);	
 
 }	
 
 myDoubleMatrix->push_back(d);
 
 //There was a method to detect chord but deleted
 //	chord.C_Detect(chromoGramm.chroma,chromoGramm.chroma_low);
 //	rootChord[chromaIndex] = chord.root;
 
 
 }//end if chromagRamm ready
 
 //printf("calling drawSndFile %i", frameIndex);
 //	frameIndex++;
 
 //get energy of the current frame and wait
 double energyValue = getEnergyOfFrame();
 energyVector->push_back(energyValue);
 
 
 }//end while readcount
 
 
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
 */
 
