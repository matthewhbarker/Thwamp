/*
  ==============================================================================

    AdsrData.cpp
    Created: 8 Apr 2023 2:00:37pm
    Author:  Matthew Barker

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.decay = release;
    
    setParameters(adsrParams);
}

