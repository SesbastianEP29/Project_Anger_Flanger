/*
  ==============================================================================

    CircularBuffer.h
    Created: 28 Oct 2021 4:04:32pm
    Author:  Wateo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class CircularBuffer
{
public:
    CircularBuffer(float nFs, float tiempoMax, float nTdelay)
        :Fs(nFs), Tmax(tiempoMax), Tdelay(nTdelay)
    {
        createBuffer();
        int muestrasDelay = round(Tdelay * Fs);
        indxEscritura = 0;

        indxLectura = indxEscritura - muestrasDelay;
        if (indxLectura < 0)
            indxLectura += ((Fs * Tmax) + 1);
    }

    float getSample(float xn, float g, float mod)
    {
        float output;
		if (indxLectura >= circularBuffer.size())
		{
			indxLectura -= circularBuffer.size();
		}
        output = valueInterpolation(indxLectura);
		
        // Interpolar

        circularBuffer[indxEscritura] = xn + g * output ;

        indxEscritura++;
        if (indxEscritura >= circularBuffer.size())
        { indxEscritura = 0; }

        float muestrasDelay = Tdelay * Fs;
        indxLectura = (indxEscritura - (muestrasDelay * mod));
		
        if (indxLectura == indxEscritura)
        { indxLectura -= 1;}

        if (indxLectura < 0)
            indxLectura += ((Fs * Tmax) + 1);
		

        return output;
    }
    ~CircularBuffer()
    {}

    void updateSampleRate(float nFs)
    {
        Fs = nFs;
        createBuffer();
    }

    void updateDelayTime(float nDelayTime)
    {
        Tdelay = nDelayTime;

        int muestrasDelay = round(Tdelay * Fs);
        indxEscritura = 0;

        indxLectura = indxEscritura - muestrasDelay;
        if (indxLectura < 0)
            indxLectura += ((Fs * Tmax) + 1);
    }

    void createBuffer()
    {
        circularBuffer.resize(Fs * Tmax + 1, 0);
    }

    float valueInterpolation(float currentIndex)
    {
        float fracc = currentIndex - floor(currentIndex);
        int prev = (int)floor(currentIndex);
        int next = ((int)ceil(currentIndex));
		if (next >= circularBuffer.size())
		{
			next -= circularBuffer.size();
		}
        float y2 = circularBuffer[next];
        float y1 = circularBuffer[prev];
        float interpolated = (y2 * fracc) + ((1 - fracc) * y1);
        return interpolated;
    }

private:
    float Fs;
    float Tmax;
    float Tdelay;
    float indxLectura;
    int indxEscritura;
    std::vector<float> circularBuffer;
};