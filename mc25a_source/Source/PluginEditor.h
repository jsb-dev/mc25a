#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class MasteringCompressorAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
  MasteringCompressorAudioProcessorEditor(MasteringCompressorAudioProcessor &);
  ~MasteringCompressorAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  MasteringCompressorAudioProcessor &audioProcessor;

  juce::Slider inputGainDial;
  juce::Label inputGainLabel;

  juce::Slider outputGainDial;
  juce::Label outputGainLabel;

  juce::Slider saturationAmountDial;
  juce::Label saturationAmountLabel;

  juce::Slider softClipAmountDial;
  juce::Label softClipAmountLabel;

  juce::TextButton importButton;

  void importWavFile();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasteringCompressorAudioProcessorEditor)
};
