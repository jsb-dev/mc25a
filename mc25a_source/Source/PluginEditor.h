// PluginEditor.h
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class MasteringCompressorAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
  explicit MasteringCompressorAudioProcessorEditor(MasteringCompressorAudioProcessor &);
  ~MasteringCompressorAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  MasteringCompressorAudioProcessor &audioProcessor;

  juce::Slider inputGainSlider;
  juce::Slider outputGainSlider;
  juce::Slider saturationAmountSlider;
  juce::Slider softClipAmountSlider;
  juce::ToggleButton saturationToggle;
  juce::ToggleButton softClipToggle;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasteringCompressorAudioProcessorEditor)
};