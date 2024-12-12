// PluginProcessor.h
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

// Assigning the Audio Processor type to our own processor class
class MasteringCompressorAudioProcessor : public juce::AudioProcessor
{
public:
  MasteringCompressorAudioProcessor();
  ~MasteringCompressorAudioProcessor() override;

  const juce::String getName() const override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  juce::AudioProcessorEditor *createEditor() override;
  juce::AudioBuffer<float> wavBuffer;
  bool hasEditor() const override;

  // Functions
  double getTailLengthSeconds() const override;
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  void loadWavFile(const juce::AudioBuffer<float> &buffer);

private:
  // params
  juce::AudioParameterFloat *inputGain;
  juce::AudioParameterFloat *outputGain;
  juce::AudioParameterFloat *saturationAmount;
  juce::AudioParameterFloat *softClipAmount;
  juce::AudioParameterBool *saturationEnabled;
  juce::AudioParameterBool *softClipEnabled;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasteringCompressorAudioProcessor)
};