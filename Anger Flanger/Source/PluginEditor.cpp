/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProyectoKnobAudioProcessorEditor::ProyectoKnobAudioProcessorEditor (ProyectoKnobAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    imagenKnob = juce::ImageFileFormat::loadFrom(BinaryData::knob101st111si_png, BinaryData::knob101st111si_pngSize);

    DepthKnob.reset(new FilmStripKnob(imagenKnob, 101, true));
    DepthKnob->setRange(0.1, 0.9);
    DepthKnob->setSliderStyle(juce::Slider::Rotary);
    addAndMakeVisible(DepthKnob.get());

    
	DepthKnob->onValueChange = [this]
	{
		audioProcessor.depth = DepthKnob->getValue();
	};
	DepthKnob->setBounds(29, 30, 111, 111);

	RateKnob.reset(new FilmStripKnob(imagenKnob, 101, true));
	RateKnob->setRange(0.5, 10);
	RateKnob->setSliderStyle(juce::Slider::Rotary);
	addAndMakeVisible(RateKnob.get());
	RateKnob->onValueChange = [this]
	{
		audioProcessor.rate = RateKnob->getValue();
	};
	RateKnob->setBounds(199, 30, 111, 111);
	FKnob.reset(new FilmStripKnob(imagenKnob, 101, true));
	FKnob->setRange(0, 0.9);
	FKnob->setSliderStyle(juce::Slider::Rotary);
	addAndMakeVisible(FKnob.get());
	FKnob->onValueChange = [this]
	{
		audioProcessor.FeedBack = FKnob->getValue();
	};
	FKnob->setBounds(369, 30, 111, 111);

	DaWKnob.reset(new FilmStripKnob(imagenKnob, 101, true));
	DaWKnob->setRange(0, 1);
	DaWKnob->setSliderStyle(juce::Slider::Rotary);
	addAndMakeVisible(DaWKnob.get());
	DaWKnob->setValue(0.5f);
	DaWKnob->onValueChange = [this]
	{
		audioProcessor.Mix = DaWKnob->getValue();
	};

	DaWKnob->setBounds(326, 180, 111, 111);


	addAndMakeVisible(chorusToggle);
	chorusToggle.onClick = [this]
	{
		audioProcessor.isChorus = chorusToggle.getToggleState();
		if (chorusToggle.getToggleState()) {
			audioProcessor.bufferL->updateDelayTime(30e-3);
			audioProcessor.bufferR->updateDelayTime(30e-3);	
			DaWKnob->setValue(0.25f);
			FKnob->setValue(0.0f);
		}
		else {
			audioProcessor.bufferL->updateDelayTime(9e-3);
			audioProcessor.bufferR->updateDelayTime(9e-3);
		}
	};
	chorusToggle.setBounds(10, 141, 30, 30);

	addAndMakeVisible(invFToggle);
	invFToggle.onClick = [this]
	{
		if (invFToggle.getToggleState()) { audioProcessor.Inv = -1; }
		else { audioProcessor.Inv = 1; }
	};
	invFToggle.setBounds(369, 141, 30, 30);

	StretchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
	StretchSlider.setRange(0.3f, 1.0f, 0.05f);
	StretchSlider.setValue(1.0f);
	addAndMakeVisible(StretchSlider);

	StretchSlider.onValueChange = [this]
	{
		//audioProcessor.Moduladora->ChangeForm(StretchSlider.getValue());
		audioProcessor.StretchFactor = StretchSlider.getValue();
	};
	StretchSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::darkblue);
	StretchSlider.setBounds(95, 190, 170, 80);

	DepthLabel.setText("Depth", juce::dontSendNotification);
	DepthLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(DepthLabel);
	DepthLabel.setBounds(60, 10, 50, 18);

	RateLabel.setText("Rate", juce::dontSendNotification);
	RateLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(RateLabel);
	RateLabel.setBounds(230, 10, 50, 18);

	FeedBackLabel.setText("FeedBack", juce::dontSendNotification);
	FeedBackLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(FeedBackLabel);
	FeedBackLabel.setBounds(392, 10, 70, 18);

	ChorusLabel.setText("Chorus", juce::dontSendNotification);
	ChorusLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(ChorusLabel);
	ChorusLabel.setBounds(33, 148, 50, 18);

	invLabel.setText("Inv", juce::dontSendNotification);
	invLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(invLabel);
	invLabel.setBounds(392, 148, 50, 18);

	FormLabel.setText("PulseWidth", juce::dontSendNotification);
	FormLabel.setFont(juce::Font("Impact", 28, juce::Font::italic));
	addAndMakeVisible(FormLabel);
	FormLabel.setBounds(130, 160, 100, 28);

	DryLabel.setText("Dry", juce::dontSendNotification);
	DryLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(DryLabel);
	DryLabel.setBounds(286, 220, 40, 18);

	WetLabel.setText("Wet", juce::dontSendNotification);
	WetLabel.setFont(juce::Font("Impact", 22, juce::Font::italic));
	addAndMakeVisible(WetLabel);
	WetLabel.setBounds(445, 220, 40, 18);

	Firma.setText("By Sebastián Escobar P1", juce::dontSendNotification);
	Firma.setFont(juce::Font("Segoe Print", 25, juce::Font::italic));
	addAndMakeVisible(Firma);
	Firma.setBounds(10, 178, 65, 100);

	setSize(512, 288);
}

ProyectoKnobAudioProcessorEditor::~ProyectoKnobAudioProcessorEditor()
{
}

//==============================================================================
void ProyectoKnobAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	juce::Image ImagenDeFondo = juce::ImageFileFormat::loadFrom(BinaryData::Fondondo_jpg, BinaryData::Fondondo_jpgSize);
	g.drawImage(ImagenDeFondo, getBounds().toFloat());

}

void ProyectoKnobAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
