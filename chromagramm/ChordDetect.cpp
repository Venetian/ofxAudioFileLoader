/*
 *  ChordDetect.cpp
 *  ChordDetect
 *
 *  Created by Adam Stark on 28/04/2008.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "ChordDetect.h"
#include <iostream>
#include <math.h>
using namespace std;

ChordDetect :: ChordDetect()
{
	
	bias = 1.06;
	
	makeprofiles();
		
}

//--------------------------------------------------------------------------------------
// destructor
ChordDetect :: ~ChordDetect()
{
										
}


//--------------------------------------------------------------------------------------
// main function to be called with 8192 sample frame at 11025 Hz
void ChordDetect :: C_Detect(float c[],float c_low[])
{
	for (int i = 0;i < 12;i++)
	{
		chroma[i] = c[i];
		chroma_low[i] = c_low[i];
	}
	
	calculateweightings();
	
	classifychromagram();
		
	//cout << root << " " << quality << " " << intervals << endl;
}

//--------------------------------------------------------------------------------------
// analyse the chromagram and assign it a root note, chord type and any features
void ChordDetect :: classifychromagram()
{
	int i;
	int j;
	int fifth;
	int chordindex;
	
	// remove some of the 5th note energy from chromagram
	for (i = 0;i < 12;i++)
	{
		fifth = (i+7) % 12;
		chroma[fifth] = chroma[fifth] - (0.1*chroma[i]);
		
		if (chroma[fifth] < 0)
		{
			chroma[fifth] = 0;
		}
		
	}
	
	
	// major chords
	for (j=0;j < 12;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],bias,3);
	}
	
	// minor chords
	for (j=12;j < 24;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],bias,3);
	}
	
	// diminished 5th chords
	for (j=24;j < 36;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],bias,3);
	}
	
	// augmented 5th chords
	for (j=36;j < 48;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],bias,3);
		
		chord[j] = chord[j] / weight_aug[j-36];
	}
	
	// sus2 chords
	for (j=48;j < 60;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],1,3);
		
		chord[j] = chord[j] / weight_sus[j-48];
	}
	
	// sus4 chords
	for (j=60;j < 72;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],1,3);
		
		chord[j] = chord[j] / weight_sus[j-60];
	}
	
	// major 7th chords
	for (j=72;j < 84;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],1,4);
	}
	
	// minor 7th chords
	for (j=84;j < 96;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],bias,4);
	}

	// dominant 7th chords
	for (j=96;j < 108;j++)
	{
		chord[j] = calcchordvalue(chroma,profiles[j],bias,4);
	}
	
	chordindex = minindex(chord,108);
	
	// major
	if (chordindex < 12)
	{
		root = chordindex;
		quality = 1;
		intervals = 0;
	}
	
	// minor
	if ((chordindex >= 12) && (chordindex < 24))
	{
		root = chordindex-12;
		quality = 0;
		intervals = 0;
	}
	
	// diminished 5th
	if ((chordindex >= 24) && (chordindex < 36))
	{
		root = chordindex-24;
		quality = 4;
		intervals = 0;
	}
	
	// augmented 5th
	if ((chordindex >= 36) && (chordindex < 48))
	{
		root = chordindex-36;
		quality = 6;
		intervals = 0;
	}
	
	// sus2
	if ((chordindex >= 48) && (chordindex < 60))
	{
		root = chordindex-48;
		quality = 2;
		intervals = 2;
	}
	
	// sus4
	if ((chordindex >= 60) && (chordindex < 72))
	{
		root = chordindex-60;
		quality = 2;
		intervals = 4;
	}
	
	// major 7th
	if ((chordindex >= 72) && (chordindex < 84))
	{
		root = chordindex-72;
		quality = 1;
		intervals = 7;
	}
	
	// minor 7th
	if ((chordindex >= 84) && (chordindex < 96))
	{
		root = chordindex-84;
		quality = 0;
		intervals = 7;
	}
	
	// dominant 7th
	if ((chordindex >= 96) && (chordindex < 108))
	{
		root = chordindex-96;
		quality = 2;
		intervals = 7;
	}
}

//--------------------------------------------------------------------------------------
// calculate weightings to help distinguish between sus2/sus4 and aug chords
void ChordDetect :: calculateweightings()
{
	int i;
	float maxval = 0;
	int fifth;
	int augfifth;
	
	maxval = max(chroma_low,12); 
		
	// normalise chroma low
	for (i = 0;i < 12;i++)
	{
		chroma_low[i] = chroma_low[i] / maxval;
	}
	
	// make weight for sus chords
	for (i = 0;i < 12;i++)
	{
		fifth = i+7;
		augfifth = i+8;
		
		if (fifth >= 12)
		{
			fifth = fifth-12;
		}
		
		if (augfifth >= 12)
		{
			augfifth = augfifth-12;
		}
		
		weight_sus[i] = chroma_low[i] + (chroma_low[fifth]/2);
		weight_aug[i] = chroma_low[i] + (chroma_low[augfifth]/2);
	}
	
	maxval = max(weight_sus,12);
	// normalise weight_sus
	for (i = 0;i < 12;i++)
	{
		weight_sus[i] = weight_sus[i] / maxval;
	}
	
	maxval = max(weight_aug,12);
	// normalise weight_aug
	for (i = 0;i < 12;i++)
	{
		weight_aug[i] = weight_aug[i] / maxval;
	}
	
	
}


//--------------------------------------------------------------------------------------
// return delta value indicating how similar the chroma is to the chord template - lower value = more similar
float ChordDetect :: calcchordvalue(float c[],float T[],float biasval, float N)
{
	float sum = 0;
	float delta;

	for (int i=0;i < 12;i++)
	{
		sum = sum + ((1-T[i])*(pow(c[i],2)));
	}

	delta = sqrt(sum) / ((12 - N)*biasval);
	
	return delta;
}


//--------------------------------------------------------------------------------------
// returns max value of an array
float ChordDetect :: max(float array[],int length)
{
	float max = 0;
	
	for (int i=0;i < length;i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}
	
	return max;
}

//--------------------------------------------------------------------------------------
// returns index of minimum value of array
int ChordDetect :: minindex(float array[],int length)
{
	float min = 10000;
	int minindex = 0;
	int i;
	
	for (i = 0;i < length;i++)
	{
		if (array[i] < min)
		{
			min = array[i];
			minindex = i;
		}
	}
	
	return minindex;
}

//--------------------------------------------------------------------------------------
// calculates bit mask chord profiles
void ChordDetect :: makeprofiles()
{
	int i;
	int t;
	int j = 0;
	int root;
	int third;
	int fifth;
	int seventh;
	
	float v1 = 1;
	float v2 = 1;
	float v3 = 1;
	
	// set profiles matrix to all zeros
	for (j = 0;j < 108;j++)
	{
		for (t = 0;t < 12;t++)
		{
			profiles[j][t] = 0;
		}
	}
	
	// reset j to zero to begin creating profiles
	j = 0;
	
	// major chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		
		j++;				
	}

	// minor chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+7) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		
		j++;				
	}

	// diminished chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+6) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		
		j++;				
	}	
	
	// augmented chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+8) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		
		j++;				
	}	
	
	// sus2 chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+2) % 12;
		fifth = (i+7) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		
		j++;				
	}
	
	// sus4 chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+5) % 12;
		fifth = (i+7) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		
		j++;				
	}		
	
	// major 7th chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		seventh = (i+11) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		profiles[j][seventh] = v3;
		
		j++;				
	}	
	
	// minor 7th chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+7) % 12;
		seventh = (i+10) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		profiles[j][seventh] = v3;
		
		j++;				
	}
	
	// dominant 7th chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		seventh = (i+10) % 12;
		
		profiles[j][root] = v1;
		profiles[j][third] = v2;
		profiles[j][fifth] = v3;
		profiles[j][seventh] = v3;
		
		j++;				
	}
}