cmake_minimum_required(VERSION 3.15)

# Set the project name
project(MasteringCompressor VERSION 1.0.0)

# Specify the location of JUCE and VST3 SDK
set(JUCE_DIR "C:/JUCE")
set(VST3_SDK_DIR "C:/vst3sdk")

# Include JUCE
add_subdirectory(${JUCE_DIR} JUCE)
add_subdirectory(${VST3_SDK_DIR} SDK)

# Define your target
juce_add_plugin(MasteringCompressor
    PLUGIN_MANUFACTURER_CODE MyMF
    PLUGIN_CODE MyCP
    FORMATS VST3
    PRODUCT_NAME "MC25a"
)

# Include the VST3 SDK (if needed by additional components)
target_include_directories(MasteringCompressor PRIVATE SDK)

# Add your source files
target_sources(MasteringCompressor PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# Specify link libraries (if required)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_analytics)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_animation)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_audio_basics)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_audio_devices)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_audio_formats)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_audio_plugin_client)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_audio_processors)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_audio_utils)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_core)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_data_structures)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_dsp)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_events)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_graphics)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_gui_basics)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_gui_extras)
target_link_libraries(MasteringCompressor PRIVATE juce::juce_osc)
