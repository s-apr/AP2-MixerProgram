/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include <iostream>

//==============================================================================
int main (int argc, char* argv[])
{
    using namespace juce;

    WavAudioFormat format;
    AudioFormatManager manager;
    manager.registerBasicFormats();

    // Read file
    juce::File inputFile("path/to/wav/file");
    FileInputStream* inputStream = new FileInputStream(inputFile);
    AudioFormatReader* reader = format.createReaderFor(inputStream, true);
    int numSamples = static_cast<int>(reader->lengthInSamples);
    AudioBuffer<float> buffer(1, numSamples);
    reader->read(&buffer, 0, numSamples, 0, true, false);
    std::cout << "done reading" << std::endl;
    delete reader;

    // Write file
    juce::File output("path/to/wav/file");
    FileOutputStream* outputStream = new FileOutputStream(output);
    outputStream->setPosition(0); // in case it exists
    outputStream->truncate();
    AudioFormatWriter* writer =
        format.createWriterFor(outputStream, 44100, 1, 16, {}, 0);
    writer->writeFromAudioSampleBuffer(buffer, 0, numSamples);
    std::cout << "done writing" << std::endl;
    delete writer;
    return 0;
}