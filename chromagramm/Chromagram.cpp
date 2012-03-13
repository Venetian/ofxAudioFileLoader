

#include "Chromagram.h"
#include <iostream>
#include <math.h>
using namespace std;

Chromagram :: Chromagram()
{
	pi = 3.14159265;
	bsize = 8192;
		
	// array init
	buffer = new float[8192]; // make audio buffer
	wbuffer = new float[8192]; // to hold windowed audio buffer
	win = new float[8192];
	d_frame = new float[128];
	hop = new float[1024];
	mag = new float[(bsize/2)+1];
	
	maximumChromaValue = 1.0;
	
	float base = 130.81278265;
	
	for (int i = 0;i < 12;i++)
	{
		note[i] = base*pow(2,(((float) i)/12));
	}
	
	harmonics = 2;
	octaves = 2;
	search = 2;  // p is number of bins either side of target to search for other peaks
		
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * bsize);		// complex array to hold fft
	p = fftwf_plan_dft_r2c_1d(bsize,wbuffer,out,FFTW_FORWARD*-1);	// plan for executing fft of wbuffer
	
	chromaready = 0;
}

//--------------------------------------------------------------------------------------
// destructor
Chromagram :: ~Chromagram()
{
	// destroy fft plan
   // fftwf_destroy_plan(p); - causes problem - why? (Andrew R)
	
	// deallocate memory
	win = NULL;	
	delete [] win;	
	buffer = NULL;	
	delete [] buffer;										
	wbuffer = NULL;	
	delete [] wbuffer;
	
	printf("delete chromogram\n");
}

//--------------------------------------------------------------------------------------
// Initialises all framesize dependent variables. Should be called to properly initialise variables and anytime the frame size changes.
void Chromagram :: initialise(int framesize,int hsize)
{
	fsize = framesize;
	hopsize = hsize;
	
	d_frame = new float[fsize/4];
	hop = new float[hopsize];


	calcrate = (hopsize*4)/fsize;

	count = 0;
	
	//fsize = framesize; // set frame size
		
	ratio = ((float) 11025) / ((float) 8192);	
	hamming(bsize);		// define a hanning window offline	
}

//--------------------------------------------------------------------------------------
// Processes a single frame
void Chromagram :: processframe(float frame[])
{
	int i;
	int j;
	int c;

	chromaready = 0; // default case that chroma isn't ready

	// downsample frame
	downsampleframe(frame);
		
	if (count < calcrate)
	{
        c = count*(fsize/4);
		
		j = 0;
		for (i = c;i < c+(fsize/4);i++)
		{
			hop[i] = d_frame[j];//d_frame is downsampled
			j++;
		}
		count++;// = count + 1;
	}
	    
    if (count == calcrate)
	{
		for (i=0;i < 8192-hopsize;i++)
		{
			buffer[i] = buffer[i+hopsize];
		}
		
		j = 0;
		for (i=8192-hopsize;i < bsize;i++)
		{
			buffer[i] = hop[j];
			j++;
		}
		        
		chromacalc(buffer);
		
        count = 0;
    }

}
/*
// Processes a single frame
void Chromagram :: processFrame(float* frame, int length){
	if (length == 8192){
	
	int i;
	int j;
	int c;
	
	chromaready = 0; // default case that chroma isn't ready
	
	// downsample frame
	downsampleframe(frame);
	
	if (count < calcrate)
	{
        c = count*(fsize/4);
		
		j = 0;
		for (i = c;i < c+(fsize/4);i++)
		{
			hop[i] = d_frame[j];
			j++;
		}
		count = count + 1;
	}
	
    if (count == calcrate)
	{
		for (i=0;i < 8192-hopsize;i++)
		{
			buffer[i] = buffer[i+hopsize];
		}
		
		j = 0;
		for (i=8192-hopsize;i < bsize;i++)
		{
			buffer[i] = hop[j];
			j++;
		}
		
		chromacalc(buffer);
		
        count = 0;
    }
	}
	
}
*/


//--------------------------------------------------------------------------------------
// Processes a single frame
void Chromagram :: downsampleframe(float frame[])
{
	float filt_frame[fsize];
	
	float b0,b1,b2,a1,a2;
	float x_1,x_2,y_1,y_2;
	
	b0 = 0.2929;
	b1 = 0.5858;
	b2 = 0.2929;   
	a1 = -0.0000;
	a2 = 0.1716;

	x_1 = 0;
	x_2 = 0;
	y_1 = 0;
	y_2 = 0;

	for (int i=0;i < fsize;i++)
	{
		filt_frame[i] = frame[i]*b0 + x_1*b1 + x_2*b2 - y_1*a1 - y_2*a2;
    
		x_2 = x_1;
		x_1 = frame[i];
		y_2 = y_1;
		y_1 = filt_frame[i];
	}
	
	for (int i=0;i < (fsize/4);i++)
	{
		d_frame[i] = filt_frame[i*4];
	}

}

//--------------------------------------------------------------------------------------
// main function to be called with 8192 sample frame at 11025 Hz
void Chromagram :: chromacalc(float frame[])
{
	int i;
		
	// apply hanning window to buffer
	for (i = 0; i < bsize;i++)
	{
		wbuffer[i] = frame[i] * win[i];
	}
	
	getmagspectrum();
	
	generatechromagram();
		
	chromaready = 1;	
		
//	for (i = 0;i < 12;i++)
//	{
//		cout << chroma[i] << " ";
//	}	
//	
//	cout << endl;
		
	//cout << "root: " << root << "  type: " << type << "  features: " << features << endl;
	
	//cout << root << " " << quality << " " << intervals << endl;
}

//--------------------------------------------------------------------------------------
// creates a chromagram from the magnitude spectrum of the input signal
void Chromagram :: generatechromagram()
{
	int i;
	float sum;
	float notesum = 0;
	float noteval;
	int index;
	float maxval = 0;
	int searchlength;
	
	for (i = 0;i < 12;i++)
	{
		sum = 0;
		
		for (int oct = 1;oct <= octaves;oct++)
		{
			noteval = (note[i]/ratio)*((float) oct);
			notesum = 0;
			
			for (int h = 1;h <= harmonics;h++)
			{
				index = round(noteval*((float) h));
				
				searchlength = search*h;
				
				maxval = 0;
				for (int n = (index-searchlength);n <= index+searchlength;n++)
				{
					if (mag[n] > maxval)
					{
						maxval = mag[n];
					}
				}
				
				notesum = notesum+(maxval*(1/((float) h)));
			}
			sum = sum + notesum;
			
			if (oct == 1)
			{
				chroma_low[i] = notesum;
			}
		}
		
		chroma[i] = sum;
		rawChroma[i] = sum;
		
		if (sum > maximumChromaValue)
		maximumChromaValue = sum;
		
	}
	
	
	// normalise chromagram
	maxval = max(chroma,12);
	
	for (i = 0;i < 12;i++)
	{
		chroma[i] = chroma[i] / maxval;
	}
	
}


//--------------------------------------------------------------------------------------
// main function to be called with 8192 sample frame at 11025 Hz
void Chromagram :: hamming(int N)
{
	int n;
		
	// apply hanning window to buffer
	for (n = 0; n < N;n++)
	{
		win[n] = 0.54 - 0.46*cos(2*pi*(((float) n)/((float) N)));
	}
}

//--------------------------------------------------------------------------------------
// finds mag spectrum of input
void Chromagram :: getmagspectrum()
{
	int i = 0;	

	// execute fft plan, i.e. compute fft of buffer
    fftwf_execute(p);

	// compute first (N/2)+1 mag values
	for (i = 0;i < (bsize/2)+1;i++)
	{
		mag[i] = sqrt(pow(out[i][0],2) + pow(out[i][1],2));
		mag[i] = sqrt(mag[i]);
	}
}

//--------------------------------------------------------------------------------------
// returns max value of an array
float Chromagram :: max(float array[],int length)
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
int Chromagram :: minindex(float array[],int length)
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