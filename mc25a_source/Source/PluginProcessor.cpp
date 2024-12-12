// PluginProcessor.cpp
#include "PluginProcessor.h"
#include "PluginEditor.h"

MasteringCompressorAudioProcessor::MasteringCompressorAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    // Initialize audio parameters
    addParameter(inputGain = new juce::AudioParameterFloat("inputGain", "Input Gain", -24.0f, 24.0f, 0.0f));
    addParameter(outputGain = new juce::AudioParameterFloat("outputGain", "Output Gain", -24.0f, 24.0f, 0.0f));
    addParameter(saturationAmount = new juce::AudioParameterFloat("saturationAmount", "Saturation Amount", 0.0f, 100.0f, 0.0f));
    addParameter(softClipAmount = new juce::AudioParameterFloat("softClipAmount", "Soft Clip Amount", 0.0f, 100.0f, 0.0f));
    addParameter(saturationEnabled = new juce::AudioParameterBool("saturationEnabled", "Saturation Enabled", false));
    addParameter(softClipEnabled = new juce::AudioParameterBool("softClipEnabled", "Soft Clip Enabled", false));
}

void MasteringCompressorAudioProcessor::loadWavFile(const juce::AudioBuffer<float> &buffer)
{
    // Store the buffer in a member variable
    wavBuffer = buffer;
}

// Process block
void MasteringCompressorAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int channel = totalNumInputChannels; channel < totalNumOutputChannels; ++channel)
        buffer.clear(channel, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto *channelData = buffer.getWritePointer(channel);

        // If a WAV file is loaded, mix it with the input signal
        if (wavBuffer.getNumSamples() > 0)
        {
            auto *wavData = wavBuffer.getReadPointer(channel % wavBuffer.getNumChannels());
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                channelData[sample] += wavData[sample % wavBuffer.getNumSamples()];
            }
        }
    }

    // Apply gain, saturation, and soft clipping here
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto *channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Apply input gain
            channelData[sample] *= inputGain->get();

            // Apply saturation if enabled
            if (saturationEnabled->get())
            {
                channelData[sample] = std::tanh(channelData[sample] * saturationAmount->get() / 100.0f);
            }

            // Apply soft clipping if enabled
            if (softClipEnabled->get())
            {
                if (channelData[sample] > 1.0f)
                    channelData[sample] = 1.0f;
                else if (channelData[sample] < -1.0f)
                    channelData[sample] = -1.0f;
            }

            // Apply output gain
            channelData[sample] *= outputGain->get();
        }
    }
}

// Destructor
MasteringCompressorAudioProcessor::~MasteringCompressorAudioProcessor() = default;

// Returns the plugin name
const juce::String MasteringCompressorAudioProcessor::getName() const
{
    return "Mastering Compressor";
}

// Prepares the plugin for playback
void MasteringCompressorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Reset the WAV buffer to avoid issues
    wavBuffer.setSize(getTotalNumInputChannels(), samplesPerBlock);
}

// Releases any resources when the plugin is stopped
void MasteringCompressorAudioProcessor::releaseResources()
{
    // Clean up or reset any state here
}

// Determines if the plugin supports a given bus layout
bool MasteringCompressorAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    // Stereo input/output is supported
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo() &&
           layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

// Creates the plugin editor
juce::AudioProcessorEditor *MasteringCompressorAudioProcessor::createEditor()
{
    return new MasteringCompressorAudioProcessorEditor(*this);
}

// Indicates whether the plugin has an editor
bool MasteringCompressorAudioProcessor::hasEditor() const
{
    return true;
}

// Returns the plugin's tail length in seconds
double MasteringCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

// Indicates if the plugin accepts MIDI input
bool MasteringCompressorAudioProcessor::acceptsMidi() const
{
    return false;
}

// Indicates if the plugin produces MIDI output
bool MasteringCompressorAudioProcessor::producesMidi() const
{
    return false;
}

// Indicates if the plugin is a MIDI effect
bool MasteringCompressorAudioProcessor::isMidiEffect() const
{
    return false;
}

// Returns the number of programs (presets)
int MasteringCompressorAudioProcessor::getNumPrograms()
{
    return 1; // Single program
}

// Gets the current program index
int MasteringCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

// Sets the current program index
void MasteringCompressorAudioProcessor::setCurrentProgram(int index)
{
    // No implementation needed for single program
}

// Returns the name of a program
const juce::String MasteringCompressorAudioProcessor::getProgramName(int index)
{
    return {};
}

// Changes the name of a program
void MasteringCompressorAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
    // No implementation needed
}

// Saves the plugin's state
void MasteringCompressorAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    // Serialize parameters here
    juce::MemoryOutputStream stream(destData, true);
    stream.writeFloat(*inputGain);
    stream.writeFloat(*outputGain);
    stream.writeFloat(*saturationAmount);
    stream.writeFloat(*softClipAmount);
    stream.writeBool(*saturationEnabled);
    stream.writeBool(*softClipEnabled);
}

// Restores the plugin's state
void MasteringCompressorAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    // Deserialize parameters here
    juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
    inputGain->setValueNotifyingHost(stream.readFloat());
    outputGain->setValueNotifyingHost(stream.readFloat());
    saturationAmount->setValueNotifyingHost(stream.readFloat());
    softClipAmount->setValueNotifyingHost(stream.readFloat());
    saturationEnabled->setValueNotifyingHost(stream.readBool());
    softClipEnabled->setValueNotifyingHost(stream.readBool());
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new MasteringCompressorAudioProcessor();
}
