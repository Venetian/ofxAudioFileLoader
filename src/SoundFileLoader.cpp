/*
 *  SoundFileLoader.cpp
 *  audioFileLoaderSVN1
 *
 *  Created by Andrew on 04/09/2011.
 *  Copyright 2011 QMUL. All rights reserved.
 *
 */

#include "SoundFileLoader.h"


SoundFileLoader::SoundFileLoader(){
	sfinfo.format = 0;
	
	//chromaG = &chromoGramm;
	
}

void SoundFileLoader::loadLibSndFile(const char *infilename){
	
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
		//sndfileInfoString = "Opened okay ";
		
	};
	
	readAudio();
	
}




void SoundFileLoader::readAudio(){
	
	
		// HERE IS THE CLASSIC LOADING FILE CODE
	//DEALS WITH MORE THAN MONO
	int channels = sfinfo.channels;
	int blocksize = FRAMESIZE;
	
	float buf [channels * blocksize] ;
	int k, m, readcount ;
	
	DoubleVector d;
	while ((readcount = sf_readf_float (infile, buf, blocksize)) > 0){
		for (k = 0 ; k < readcount ; k++){	
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
		
		//could call this here
	//	someAudioProcess->processframe(frame);

		
	}//end readcount
	
	//printf("audio vector size is %i\n", (int) audioHolder.audioVector.size());
	audioHolder.length = (int) audioHolder.audioVector.size();
	totalNumberOfFrames = audioHolder.length;
}

