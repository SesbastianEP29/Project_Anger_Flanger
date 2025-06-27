/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Wavetable.h"

//==============================================================================
/**
*/
class ProyectoKnobAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ProyectoKnobAudioProcessor();
    ~ProyectoKnobAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	std::atomic<float> rate,depth;
	std::atomic<bool> isChorus;
	std::unique_ptr<CircularBuffer> bufferL, bufferR;
	std::atomic<float> FeedBack;
	std::atomic<float> Mix;
	std::atomic<float> Inv;
	std::atomic<float> StretchFactor;


private:
    float counter;
    float mysampleRate;
	float pi2 = juce::MathConstants<float>::twoPi;
	float Tperiod;
	float TiAnterior;
	
    

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoKnobAudioProcessor)
};
