
#include "LookAndFeel.h"


namespace aiomfx {

void AiomFXLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, const float rotaryStartAngle,
                                          const float rotaryEndAngle, juce::Slider& slider) {
    auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
    //    auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);
    auto fill = AIOMFX_RED;
    
    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);
    
    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;
    
    juce::Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    
    g.setColour (outline); // non active background
    g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);
        
        g.setColour (fill);
        g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }
    
    juce::Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - 10) * std::cos (toAngle - juce::MathConstants<float>::halfPi),
                                   bounds.getCentreY() + (arcRadius - 10) * std::sin (toAngle - juce::MathConstants<float>::halfPi));
    
    g.setColour (AIOMFX_RED);
    g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(),
               thumbPoint.getX(), thumbPoint.getY(), 2.0f);
}


void AiomFXLookAndFeel::drawTickBox (juce::Graphics& g, juce::Component& component,
                                     float x, float y, float w, float h,
                                     const bool ticked,
                                     [[maybe_unused]] const bool isEnabled,
                                     [[maybe_unused]] const bool shouldDrawButtonAsHighlighted,
                                     [[maybe_unused]] const bool shouldDrawButtonAsDown) {
    juce::Rectangle<float> tickBounds {x, y, w, h};
    
    g.setColour(juce::Colours::black);
    g.drawRect(tickBounds);
    
    if (ticked)
    {
        g.setColour(AIOMFX_RED);
        g.fillRect(tickBounds);
    }
}


juce::Label* AiomFXLookAndFeel::createSliderTextBox (juce::Slider& slider) {
    auto* l = LookAndFeel_V2::createSliderTextBox (slider);
    juce::Font font16{20.0f};
    l->setFont(font16);
    
    
    return l;
}
}
