# THWAMP
## Bass Synth 

##Overview
This project aims to develop a mono synthesizer plugin specifically designed for bass sounds. The plugin will feature various controls such as saturation, distortion, and a unique "kick" parameter to enhance the user's ability to create diverse and dynamic bass tones.

##Team Members
Matthew Barker: Project lead, responsible for overall design, coding, and documentation.
Technologies
JUCE: The plugin will be developed using the JUCE framework.
C++: The primary programming language used for development.
JUCE GUI Library: The graphical user interface library used for designing the plugin interface.

##Features
Saturation Level: Controls the amount of saturation applied to the sound (0-100%).
Saturation Decay: Determines how the saturation fades over time (0-100%).
Distortion Level: Controls the level of distortion applied to the sound (0-100%).
Distortion Decay: Determines how the distortion fades over time (0-100%).
Kick Level: Controls the intensity of the "kick" effect added to the bass sound (0-100%).
Kick Time: Determines the position of the kick effect within the sample.
*Note: The implementation of individual envelopes for Saturation Decay and Distortion Decay will be considered during development.

##Visualization
The plugin will feature a waveform monitor to display the generated waveform in real-time. As the user plays a note or adjusts the plugin's parameters, the waveform will update accordingly.

##Milestones
###Worst-case scenario:
Complete the working prototype with basic controls.
no waveform monitor feature.
###Expected:
Optimize the plugin's performance and usability.
Add presets and additional features to enhance the plugin's capabilities.
###Stretch goals:
Implement individual envelopes for Saturation Decay and Distortion Decay, if feasible.
Implement a way of playing the bass synth 'in reverse'.

