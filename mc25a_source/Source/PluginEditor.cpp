// PluginEditor.cpp
#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"

MasteringCompressorAudioProcessorEditor::MasteringCompressorAudioProcessorEditor(MasteringCompressorAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
  setSize(400, 300);

  inputGainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
  inputGainSlider.setRange(-24.0, 24.0, 0.1);
  inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
  addAndMakeVisible(inputGainSlider);

  outputGainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
  outputGainSlider.setRange(-24.0, 24.0, 0.1);
  outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
  addAndMakeVisible(outputGainSlider);

  saturationAmountSlider.setSliderStyle(juce::Slider::LinearHorizontal);
  saturationAmountSlider.setRange(0.0, 100.0, 0.1);
  saturationAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
  addAndMakeVisible(saturationAmountSlider);

  softClipAmountSlider.setSliderStyle(juce::Slider::LinearHorizontal);
  softClipAmountSlider.setRange(0.0, 100.0, 0.1);
  softClipAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
  addAndMakeVisible(softClipAmountSlider);

  saturationToggle.setButtonText("Saturation");
  addAndMakeVisible(saturationToggle);

  softClipToggle.setButtonText("Soft Clipping");
  addAndMakeVisible(softClipToggle);
}

MasteringCompressorAudioProcessorEditor::~MasteringCompressorAudioProcessorEditor() {}

void MasteringCompressorAudioProcessorEditor::paint(juce::Graphics &g)
{
  g.fillAll(juce::Colours::black);
  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("MC24 Mastering Compressor", getLocalBounds(), juce::Justification::centredTop, 1);
}

void MasteringCompressorAudioProcessorEditor::resized()
{
  auto area = getLocalBounds().reduced(10);
  auto sliderHeight = 50;

  inputGainSlider.setBounds(area.removeFromTop(sliderHeight));
  outputGainSlider.setBounds(area.removeFromTop(sliderHeight));
  saturationAmountSlider.setBounds(area.removeFromTop(sliderHeight));
  softClipAmountSlider.setBounds(area.removeFromTop(sliderHeight));

  saturationToggle.setBounds(area.removeFromTop(30));
  softClipToggle.setBounds(area.removeFromTop(30));
}
