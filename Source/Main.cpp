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
    AudioFormatReader* reader1 = format.createReaderFor(inputStream1, true);
    int numSamples1 = static_cast<int>(reader1->lengthInSamples);
    AudioBuffer<float> buffer1(1, numSamples1);
    reader1->read(&buffer1, 0, numSamples1, 0, true, false);
    std::cout << "done reading" << std::endl;
    delete reader1;

    // Read file2
        //buffer2
    juce::File inputFile2("E:\\JUCE\\JUCE Projects\\Tone2.wav");
    FileInputStream* inputStream2 = new FileInputStream(inputFile2);
    AudioFormatReader* reader2 = format.createReaderFor(inputStream2, true);
    int numSamples2 = static_cast<int>(reader2->lengthInSamples);
    AudioBuffer<float> buffer2(1, numSamples2);
    reader2->read(&buffer2, 0, numSamples2, 0, true, false);
    std::cout << "done reading" << std::endl;
    delete reader2;


    //apply gain
    buffer1.applyGain(0.5f);
    buffer2.applyGain(0.2f);

    //buffer for longest input
        //output buffer for combined samples
    int outputSamples = std::max(numSamples1, numSamples2);
    AudioBuffer<float> outputBuffer(1, outputSamples);

    //read buffers
    const float* readPtr1 = buffer1.getReadPointer(0);
    const float* readPtr2 = buffer2.getReadPointer(0);
    float* writePtr = outputBuffer.getWritePointer(0);

    //mix buffers
        //loop for length of longest sample (outputSamples)
    for (int i = 0; i < outputSamples; i++) {
        
        float sample1, sample2;

        if (i < numSamples1) {
            sample1 = readPtr1[i];
        }
        else {
            sample1 = 0.0f;
        }

        if (i < numSamples2) {
            sample2 = readPtr2[i];
        }
        else {
            sample2 = 0.0f;
        }

        writePtr[i] = sample1 + sample2;

    }

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