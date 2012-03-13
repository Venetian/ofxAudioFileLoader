/*
 *  ChordDetect.h
 *  ChordDetect
 *
 *  Created by Adam Stark on 28/04/2008.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CHORDDETECT_H
#define CHORDDETECT_H

#include "fftw3.h"

class ChordDetect
{
public:		
	ChordDetect();											// constructor
	~ChordDetect();											// destructor
	void C_Detect(float c[],float c_low[]);
	
	int root;
	int quality;
	int intervals;
	
private:
	void makeprofiles();
	void calculateweightings();
	void classifychromagram();
	
	float calcchordvalue(float c[],float T[],float biasval, float N);
	float max(float array[],int length);
	int minindex(float array[],int length);

	float chroma[12];
	float chroma_low[12];
	float weight_sus[12];
	float weight_aug[12];
	float profiles[108][12];
	float w_profile[12];
	
	float chord[108];
	
	float bias;
		

};

#endif
