# THWAMP
## a Hip-Hop Bass Synth 

## PROJECT FINAL REPORT

### How to Run: 

1. Create a JUCE project with the name 'Thwamp'
2. make sure the JUCE project contains: 
  - the dsp module 
  - the 'is a synth' marked 'on'
  - the 'input midi' marked 'on'
3. replace the source code with the source code contained in this reposity. 
4. You can build as either a standalone plugin, or a vst/au, and use the plugin.

### PROJECT PROGRESS REPORT

## Overview
This project aims to develop a mono synthesizer plugin specifically designed for bass sounds - more specifcally, bass soudns heard in popular hip-hop music. The plugin will feature various controls such as saturation, distortion, and a unique "kick" parameter to enhance the user's ability to create diverse and dynamic bass tones.

## Team Members
Matthew Barker: Project lead, responsible for overall design, coding, and documentation.
Technologies
JUCE: The plugin will be developed using the JUCE framework.
C++: The primary programming language used for development.
JUCE GUI Library: The graphical user interface library used for designing the plugin interface.

## Features
Saturation Level: Controls the amount of saturation applied to the sound (0-100%).
Saturation Decay: Determines how the saturation fades over time (0-100%).
Distortion Level: Controls the level of distortion applied to the sound (0-100%).
Distortion Decay: Determines how the distortion fades over time (0-100%).
Kick Level: Controls the intensity of the "kick" effect added to the bass sound (0-100%).
Kick Time: Determines the position of the kick effect within the sample.
*Note: The implementation of individual envelopes for Saturation Decay and Distortion Decay will be considered during development.

## Visualization
The plugin will feature a waveform monitor to display the generated waveform in real-time. As the user plays a note or adjusts the plugin's parameters, the waveform will update accordingly.

## Milestones
### Worst-case scenario:
Complete the working prototype with basic controls.
no waveform monitor feature.
### Expected:
Optimize the plugin's performance and usability.
Add presets and additional features to enhance the plugin's capabilities.
### Stretch goals:
Implement individual envelopes for Saturation Decay and Distortion Decay, if feasible.
Implement a way of playing the bass synth 'in reverse'.

### Recources: 

https://www.youtube.com/@TheAudioProgrammer - This channel helped me massivly. 
https://www.youtube.com/@ValerioVelardoTheSoundofAI - This channel also helped me a lot.
https://www.youtube.com/watch?v=pbKJrks1ByE 
https://en.wikipedia.org/wiki/Triangle_wave
https://www.dataq.com/data-acquisition/general-education-tutorials/fft-fast-fourier-transform-waveform-analysis.html
https://www.loopcloud.com/cloud/blog/4849-Distorted-Reality-Your-guide-to-different-types-of-distortion
