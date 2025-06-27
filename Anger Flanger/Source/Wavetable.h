/*
  ==============================================================================

    Wavetable.h
    Created: 8 Nov 2021 1:35:30am
    Author:  USUARIO

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Wavetable
{
public:
	Wavetable(float nFs, int tableLength)
		:mySampleRate(nFs), TableLength(tableLength)
	{
		N = 0;
		Ti = 0;
		tabla1 = new float[tableLength];
		tabla2 = new float[tableLength];
		for (int i = 0; i < TableLength; i++) {
			tabla1[i] = sin(pi2*i / TableLength);
			tabla2[i] = sin(pi2*i / TableLength);
		}
		

		
	}

	float getSample(float frequency)
	{
		if (CambioTabla) {
			if (TablaUsada) { auxtabla = tabla2; }
			else { auxtabla = tabla1; }
				if (Ti < (TableLength* StretchFactor)) {
					auxtabla[(int)Ti] = sin(pi2*Ti / (TableLength* StretchFactor));
				}
				else { auxtabla[(int)Ti] = 0;
			}
			Ti += 1;
			if (Ti == TableLength) {
				Ti = 0;
				CambioTabla=!CambioTabla;
				TablaUsada = !TablaUsada;
			}
		}
		int il, ih;
		il = (int)floor(N);
		ih = il + 1;
		float muestraTono;
		float epsilon = N - (float)il;
		if (ih >= TableLength) {
			if (TablaUsada) { muestraTono = (tabla1[0] - tabla1[il])*epsilon + tabla1[il]; }
			else { muestraTono = (tabla2[0] - tabla2[il])*epsilon + tabla2[il]; }
		}
		else {
			if (TablaUsada) { muestraTono = (tabla1[ih] - tabla1[il])*epsilon + tabla1[il]; }
			else { muestraTono = (tabla2[ih] - tabla2[il])*epsilon + tabla2[il]; }
		}
		if (N >= TableLength) { N = N + (frequency / mySampleRate) * TableLength - TableLength; }
		else { N = N + (frequency / mySampleRate) * TableLength; }
		if (N >= TableLength) { N = 0; }
		return muestraTono;

		
	}
	void ChangeForm(float stretch)
	{
		CambioTabla = true;
		StretchFactor = stretch;

	}

private:
	int TableLength;
	float mySampleRate, StretchFactor,N,Ti;
	bool CambioTabla, TablaUsada;
	float pi2 = juce::MathConstants<double>::twoPi;
	float*auxtabla;
	float*tabla1;
	float*tabla2;
};
