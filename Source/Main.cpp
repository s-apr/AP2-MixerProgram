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

    // Read file1
        //buffer1
    juce::File inputFile1("E:\\JUCE\\JUCE Projects\\Tone.wav");
    FileInputStream* inputStream1 = new FileInputStream(inputFile1);
    AudioFormatReader* reader = format.createReaderFor(inputStream1, true);
    int numSamples1 = static_cast<int>(reader->lengthInSamples);
    AudioBuffer<float> buffer1(1, numSamples1);
    reader->read(&buffer1, 0, numSamples1, 0, true, false);
    std::cout << "done reading" << std::endl;
    delete reader;

    // Read file2
        //buffer2
    juce::File inputFile2("E:\\JUCE\\JUCE Projects\\Tone2.wav");
    FileInputStream* inputStream2 = new FileInputStream(inputFile2);
    AudioFormatReader* reader = format.createReaderFor(inputStream2, true);
    int numSamples2 = static_cast<int>(reader->lengthInSamples);
    AudioBuffer<float> buffer2(1, numSamples2);
    reader->read(&buffer2, 0, numSamples2, 0, true, false);
    std::cout << "done reading" << std::endl;
    delete reader;


    //apply gain
    buffer1.applyGain(0.5f);
    buffer2.applyGain(0.5f);

    //buffer for longest input
    int outputSamples = std::max(numSamples1, numSamples2);
    //output buffer for combined samples
    AudioBuffer<float> outputBuffer(1, outputSamples);

    // Write file
    juce::File output("E:\\JUCE\\JUCE Projects\\ToneMix.wav");
    FileOutputStream* outputStream = new FileOutputStream(output);
    outputStream->setPosition(0); // in case it exists
    outputStream->truncate();
    AudioFormatWriter* writer =
        format.createWriterFor(outputStream, 44100, 1, 16, {}, 0);
    writer->writeFromAudioSampleBuffer(outputBuffer, 0, outputSamples);
    std::cout << "done writing" << std::endl;
    delete writer;
    return 0;
}