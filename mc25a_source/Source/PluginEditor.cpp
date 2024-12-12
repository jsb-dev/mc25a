#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"

// Instantiate the Master Compressor Audio Editor
MasteringCompressorAudioProcessorEditor::MasteringCompressorAudioProcessorEditor(MasteringCompressorAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
  setSize(800, 600); // Increased window size

  // Configure input gain dial
  inputGainDial.setSliderStyle(juce::Slider::Rotary);
  inputGainDial.setRange(-24.0, 24.0, 0.1);
  inputGainDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 40); // Larger UI elements
  inputGainDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF191a19));
  inputGainDial.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF2cd1a8));
  addAndMakeVisible(inputGainDial);
  inputGainLabel.setText("Input Gain", juce::dontSendNotification);
  inputGainLabel.setFont(juce::Font("Verdana", 18.0f, juce::Font::bold)); // Larger font
  inputGainLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFe6f0ed));
  inputGainLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(inputGainLabel);

  // Configure output gain dial
  outputGainDial.setSliderStyle(juce::Slider::Rotary);
  outputGainDial.setRange(-24.0, 24.0, 0.1);
  outputGainDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 40); // Larger UI elements
  outputGainDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF191a19));
  outputGainDial.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF2cd1a8));
  addAndMakeVisible(outputGainDial);
  outputGainLabel.setText("Output Gain", juce::dontSendNotification);
  outputGainLabel.setFont(juce::Font("Verdana", 18.0f, juce::Font::bold)); // Larger font
  outputGainLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFe6f0ed));
  outputGainLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(outputGainLabel);

  // Configure saturation amount dial
  saturationAmountDial.setSliderStyle(juce::Slider::Rotary);
  saturationAmountDial.setRange(0.0, 100.0, 0.1);
  saturationAmountDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 40); // Larger UI elements
  saturationAmountDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF191a19));
  saturationAmountDial.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF2cd1a8));
  addAndMakeVisible(saturationAmountDial);
  saturationAmountLabel.setText("Saturation", juce::dontSendNotification);
  saturationAmountLabel.setFont(juce::Font("Verdana", 18.0f, juce::Font::bold)); // Larger font
  saturationAmountLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFe6f0ed));
  saturationAmountLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(saturationAmountLabel);

  // Configure soft clip amount dial
  softClipAmountDial.setSliderStyle(juce::Slider::Rotary);
  softClipAmountDial.setRange(0.0, 100.0, 0.1);
  softClipAmountDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 40); // Larger UI elements
  softClipAmountDial.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF191a19));
  softClipAmountDial.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(0xFF2cd1a8));
  addAndMakeVisible(softClipAmountDial);
  softClipAmountLabel.setText("Soft Clip", juce::dontSendNotification);
  softClipAmountLabel.setFont(juce::Font("Verdana", 18.0f, juce::Font::bold)); // Larger font
  softClipAmountLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFe6f0ed));
  softClipAmountLabel.setJustificationType(juce::Justification::centred);
  addAndMakeVisible(softClipAmountLabel);

  // Add button to import WAV file
  importButton.setButtonText("Import WAV");
  importButton.onClick = [this]
  { importWavFile(); };
  addAndMakeVisible(importButton);
}

// Virtual override
MasteringCompressorAudioProcessorEditor::~MasteringCompressorAudioProcessorEditor() {}

// Provide the paint function
void MasteringCompressorAudioProcessorEditor::paint(juce::Graphics &g)
{
  g.fillAll(juce::Colour(0xFF2cd1a8));
  g.setColour(juce::Colour(0xFFe6f0ed));
  g.setFont(juce::Font("Verdana", 24.0f, juce::Font::bold)); // Larger font
  g.drawFittedText("MC24 Mastering Compressor", getLocalBounds(), juce::Justification::centredTop, 1);
}

// Provide the resize function
void MasteringCompressorAudioProcessorEditor::resized()
{
  auto area = getLocalBounds().reduced(10);
  auto dialAreaHeight = 120; // Increased height for larger UI elements

  inputGainLabel.setBounds(area.removeFromTop(30)); // Label above the dial
  inputGainDial.setBounds(area.removeFromTop(dialAreaHeight).reduced(5));

  outputGainLabel.setBounds(area.removeFromTop(30)); // Label above the dial
  outputGainDial.setBounds(area.removeFromTop(dialAreaHeight).reduced(5));

  saturationAmountLabel.setBounds(area.removeFromTop(30)); // Label above the dial
  saturationAmountDial.setBounds(area.removeFromTop(dialAreaHeight).reduced(5));

  softClipAmountLabel.setBounds(area.removeFromTop(30)); // Label above the dial
  softClipAmountDial.setBounds(area.removeFromTop(dialAreaHeight).reduced(5));

  importButton.setBounds(area.removeFromTop(30).reduced(5)); // Position the import button
}

// Function to import WAV file
void MasteringCompressorAudioProcessorEditor::importWavFile()
{
  juce::FileChooser chooser("Select a WAV file to import...", {}, "*.wav");
  chooser.launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                      [this](const juce::FileChooser &fc)
                      {
                        auto file = fc.getResult();
                        if (file.existsAsFile())
                        {
                          juce::AudioFormatManager formatManager;
                          formatManager.registerBasicFormats();
                          std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

                          if (reader != nullptr)
                          {
                            auto duration = reader->lengthInSamples / reader->sampleRate;
                            juce::AudioBuffer<float> buffer(reader->numChannels, reader->lengthInSamples);
                            reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);

                            // Feed the buffer into the input signal
                            audioProcessor.loadWavFile(buffer);
                          }
                        }
                      });
}
