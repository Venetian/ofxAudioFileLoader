/*
 *  ofxSoundFileLoader.cpp
 *  audioFileLoaderSVN1
 *
 *  Created by Andrew on 04/09/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

#include "ofxSoundFileLoader.h"


ofxSoundFileLoader::ofxSoundFileLoader(){
	sfinfo.format = 0;
//	onsetDetect = new ofxAubioOnsetDetection();
	//onsetDetect->reset();
	
	soundFileName = "";
	screenToDraw = 1;
}

ofxSoundFileLoader::~ofxSoundFileLoader(){
//	delete onsetDetect ;
//	printf("file loader delete onset detect\n");
	
}

void ofxSoundFileLoader::updateToAudioPosition(const float& audioPosition){
	
	audioHolder.playPosition = audioPosition * audioHolder.audioVector.size();
	onsetDetect.playPosition = audioPosition;
}

void ofxSoundFileLoader::updateToMillisPosition(const double& millis){
	
//	audioHolder.playPosition = audioPosition * audioHolder.audioVector.size();
	onsetDetect.playPosition = millis * 44.1 / (double)totalNumberOfSamples;
}

void ofxSoundFileLoader::drawFile(){
	if (screenToDraw == 0){
		audioHolder.drawAudioVectorSamples(audioHolder.playPosition - audioHolder.audioScaleSamples*0.5, 
													  audioHolder.playPosition + audioHolder.audioScaleSamples*0.5);
	}else{
		onsetDetect.drawOnsetDetectionScrolling();
	}

}


void ofxSoundFileLoader::loadNewAudio(std::string filename){
	loadLibSndFile(filename.c_str());
}

void ofxSoundFileLoader::loadLibSndFile(const char *infilename){
	
//	if (!sf_close(infile)){
//		printf("closed sndfile okay \n");
//	}
	
	// Open Input File with lib snd file
    if (! (infile = sf_open (infilename, SFM_READ, &sfinfo)))
    {   // Open failed
        printf ("SF OPEN routine Not able to open input file %s.\n", infilename) ;
        // Print the error message from libsndfile. 
        puts (sf_strerror (NULL)) ;
		
	} else{
		printf("SF OPEN : file %s okay, ", infilename);
		printf("number of channels is %i\n", sfinfo.channels);
		soundFileName = infilename;
		//sndfileInfoString = "Opened okay ";
		
	};
	
	readAudio();
	onsetDetect.printOnsetList();
	printf("max val of onset det is %f\n", onsetDetect.onsetDetector.maximumDetectionValue);
}

void ofxSoundFileLoader::readAudio(){
	
	onsetDetect.reset();
	//could add this in - check the stored github
	
	// HERE IS THE CLASSIC LOADING FILE CODE
	//DEALS WITH MORE THAN MONO
	int channels = sfinfo.channels;
	int blocksize = FRAMESIZE;
	
	float buf [channels * blocksize] ;
	int k, m, readcount ;
	
	DoubleVector d;
	while ((readcount = sf_readf_float (infile, buf, blocksize)) > 0){
		for (k = 0 ; k < readcount ; k++){	
			//readcount is a chunk - eg 512 samples - of audio that is processed
			d.clear();
			for (m = 0 ; m < channels ; m++){
				d.push_back(buf [k * channels + m]);
				//		 fprintf (outfile, " % 12.10f", buf [k * channels + m]) ;
				//		 fprintf (outfile, "\n") ;
				if (m == 0){
					//makes the vector hold the mono file - the left channel
					audioHolder.audioVector.push_back(buf[k * channels + 0]);
					frame[k] = buf[k*channels + 0];
				}
				
			} 
		audioHolder.audioMatrix.push_back(d);
			//storing the full soundfile in multiple channels in the audioMatrix
		}
		//printf("processing at readcount %i\n", readcount);
		//could call this here
		onsetDetect.processFrame(&frame[0], blocksize);

		
	}//end readcount
	
	//printf("audio vector size is %i\n", (int) audioHolder.audioVector.size());
	audioHolder.length = (int) audioHolder.audioVector.size();
	totalNumberOfSamples = audioHolder.length;
	
	printf("Total number of samples %i onset frames %i\n", totalNumberOfSamples, onsetDetect.frameCountIndex);
	
}


void ofxSoundFileLoader::zoomOut(){
	if (screenToDraw == 0){
		audioHolder.audioScaleSamples *= 2.;
	}
	if (screenToDraw == 1){
		onsetDetect.amplitudeNumber *= 2;
	}
}

void ofxSoundFileLoader::zoomIn(){
	if (screenToDraw == 0){
		audioHolder.audioScaleSamples /= 2.;
	}
	if (screenToDraw == 1 && onsetDetect.amplitudeNumber > 2){
		onsetDetect.amplitudeNumber /= 2;
	}
}

