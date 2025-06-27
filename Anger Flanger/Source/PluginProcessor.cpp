/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProyectoKnobAudioProcessor::ProyectoKnobAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    bufferL.reset(new CircularBuffer(44100, 3, 9e-3));
    bufferR.reset(new CircularBuffer(44100, 3, 9e-3));
	TiAnterior = 1000;
    counter = 0;
    mysampleRate = 44.1e3;
    rate = 0.5;
    depth = 0.1;
	Inv = 1;
	FeedBack = 0;
	isChorus = false;
	Mix = 0.5;
	StretchFactor = 1;
}

ProyectoKnobAudioProcessor::~ProyectoKnobAudioProcessor()
{
}

//==============================================================================
const juce::String ProyectoKnobAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProyectoKnobAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoKnobAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoKnobAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProyectoKnobAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProyectoKnobAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ProyectoKnobAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProyectoKnobAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ProyectoKnobAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProyectoKnobAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ProyectoKnobAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mysampleRate = sampleRate;
	bufferL->updateSampleRate(sampleRate);
	bufferL->updateSampleRate(sampleRate);
	Tperiod = sampleRate;
    counter = 0;
}

void ProyectoKnobAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProyectoKnobAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ProyectoKnobAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
		float lfo;
		Tperiod = mysampleRate / (rate);
		int auxval = (int)counter % (int)round(Tperiod);
		float Ti = (float)auxval;
		if (TiAnterior == Ti) { 
			bool ay = false; }
		if (Ti < (Tperiod* StretchFactor)) {
			lfo = sin(pi2*Ti / (Tperiod* StretchFactor))*0.9;
		}
		else {
			lfo = 0;
		}
		TiAnterior = Ti;

		//float lfo = Moduladora->getSample(rate)*0.9;
		//float lfo;

		if (isChorus){
		//	lfo = sin(juce::MathConstants<float>::twoPi * rate * (counter / mysampleRate))*depth*0.95;
			lfo = (lfo*depth + 1) / 2;
		}
		else
		{
	//		lfo = sin(juce::MathConstants<float>::twoPi * rate * (counter / mysampleRate))*0.9;
			lfo = ((lfo-1/10 + 1)/ 2)*depth+1/20;
		}
        if (auxval==0)
        {
            counter=0;
        }
        counter++;
        
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            float* channelN = buffer.getWritePointer(channel);
			

            if (channel == 0)
            {
				channelN[sample] = 
					channelN[sample]*(1-Mix)+(bufferL->getSample(channelN[sample], FeedBack*Inv, lfo))*Mix;
            }
            else if (channel == 1)
            {
				channelN[sample] = 
					channelN[sample] * (1 - Mix) + (bufferR->getSample(channelN[sample], FeedBack*Inv, lfo))*Mix;
            }
            else
            {
                buffer.clear();
            }
        }
    }
}

//==============================================================================
bool ProyectoKnobAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ProyectoKnobAudioProcessor::createEditor()
{
    return new ProyectoKnobAudioProcessorEditor (*this);
}

//==============================================================================
void ProyectoKnobAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ProyectoKnobAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProyectoKnobAudioProcessor();
}
