#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "sndfile.h"
#include "ofxFileDialogOSX.h"
#include "ofxSoundFileLoader.h"

//note the dependency on sndfile (libsndfile library needs to be accessible)
//also the file dialogue addon

//#include <vector>
//#include <cstdlib>


//main commands:
//O: open a new file
//see the key pressed function for other bits - e.g. can view spectral difference


//#define FRAMESIZE 512

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
		void loadSndfile();

 double getEnergyOfFrame();
	//	void putEnergyInFrame();

		void initialiseVariables();
	
	
	typedef std::vector<double> DoubleVector;
	typedef std::vector<DoubleVector> DoubleMatrix;

//	DoubleMatrix chromaMatrix;
//	DoubleMatrix* matrixPtr;
	

	
//	void drawDoubleMatrix(DoubleMatrix* dMatrix);
//	void drawSpectralDifference(DoubleMatrix* dMatrix);
	
//	DoubleVector firstEnergyVector;
	
//	void drawEnergyVectorFromPointer(DoubleVector* energyVec);
	
	//	void processAudioToDoubleMatrix(Chromagram* chromaG, DoubleMatrix* myDoubleMatrix, DoubleVector* energyVector);
	
		void loadNewAudio(string soundFileName);
		
		void openFileDialogBox();
		void loadLibSndFile(const char * filename);
		bool getFilenameFromDialogBox(string* fileNameToSave);
		void openNewAudioFileWithdialogBox();		
	
		double audioScale;
	
		string soundFileName;
	
		float screenWidth, screenHeight;
	
		float 	pan;
		int		sampleRate;
		bool 	bNoise;
		float 	volume;

		float 	* lAudio;
		float   * rAudio;

	//	bool moveOn;
		bool drawOnsetFunction;
		
	//	int frameIndex;
	//	float energy[ENERGY_LENGTH];
	
	//	float chromoGramVector[CHROMA_LENGTH][12];
	//	int rootChord[CHROMA_LENGTH];
		
	//	int energyIndex;
	
	//	int totalFrames;
		int screenToDraw;
		
		int scrollWidth;// 1600
	
		bool audioPlaying, audioPaused;
	

	
		//------------------- for the simple sine wave synthesis
/*
		float 	targetFrequency;
		float 	phase;
		float 	phaseAdder;
		float 	phaseAdderTarget;
*/		
		string sndfileInfoString, textString;
		int xIndex;
	
		ofxSoundFileLoader fileLoader;
	
		ofSoundPlayer  loadedAudio;
		float audioPosition;
		float width, height;
	//	int chromaIndex;	
		int totalNumberOfFrames;
	
		string chordString;
	
	//	Chromagram chromoGramm;
			
	//	ChordDetect chord;

//		SNDFILE *infile; // define input and output sound files
//		SF_INFO sfinfo ; // struct to hold info about sound file

		
};

#endif
