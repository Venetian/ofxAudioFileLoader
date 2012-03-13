#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "sndfile.h"
#include "ofxFileDialogOSX.h"
#include "LoadedAudioHolder.h"
//#include "ofxSoundFileLoader.h"
#include "LoadedAudioHolder.h"

//note the dependency on sndfile (libsndfile library needs to be accessible)
//also the file dialogue addon

//main commands:
//O: open a new file
//see the key pressed function for other bits - e.g. can view spectral difference

//TO DO
//Move all the soundfile stuff to the ofxSoundFileLoader
//can hold the player, the audio samples and the onset class there

//length in terms of frames (at 512 samples per frame - there are 90 per second) => 900: 10 seconds

class testApp : public ofBaseApp{

	public:


		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		void audioRequested 	(float * input, int bufferSize, int nChannels);

	bool getFilenameFromDialogBox(string* fileNameToSave);
	void openNewAudioFileWithdialogBox();		
	void loadNewAudio(string soundFileName);
	
	LoadedAudioHolder audioFilePlayer;
		

//live audio input	
		float 	pan;
		int		sampleRate;
		bool 	bNoise;
		float 	volume;
		float 	* lAudio;
		float   * rAudio;

		
};

#endif
