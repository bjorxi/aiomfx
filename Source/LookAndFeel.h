

#pragma once


#include <JuceHeader.h>

namespace aiomfx {


const juce::Colour AIOMFX_RED{255, 109, 124};


class AiomFXLookAndFeel : public juce::LookAndFeel_V4  {

public:
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, const float rotaryStartAngle,
                           const float rotaryEndAngle, juce::Slider& slider);
  
    juce::Label* createSliderTextBox (juce::Slider& slider);
    
   void drawTickBox (juce::Graphics& g, juce::Component& component,
                                      float x, float y, float w, float h,
                                      const bool ticked,
                                      [[maybe_unused]] const bool isEnabled,
                                      [[maybe_unused]] const bool shouldDrawButtonAsHighlighted,
                     [[maybe_unused]] const bool shouldDrawButtonAsDown);
    

   
};

}
