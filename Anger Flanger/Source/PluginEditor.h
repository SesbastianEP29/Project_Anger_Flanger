/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "filmStrip.h"

//==============================================================================
/**
*/
class ProyectoKnobAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ProyectoKnobAudioProcessorEditor (ProyectoKnobAudioProcessor&);
    ~ProyectoKnobAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Image imagenKnob;
    std::unique_ptr<FilmStripKnob> DepthKnob;
	std::unique_ptr<FilmStripKnob> RateKnob;
	std::unique_ptr<FilmStripKnob> FKnob;
	std::unique_ptr<FilmStripKnob> DaWKnob;
	juce::Slider StretchSlider;
	juce::ToggleButton chorusToggle,invFToggle;
	juce::Label DepthLabel, RateLabel, FormLabel, FeedBackLabel, DryLabel, WetLabel, invLabel, ChorusLabel,Firma;
    
    ProyectoKnobAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoKnobAudioProcessorEditor)
};
