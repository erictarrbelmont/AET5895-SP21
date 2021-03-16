#ifndef SMALLKNOB_H_INCLUDED
#define SMALLKNOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SmallKnob : public LookAndFeel_V3
{
public:
    Image sprite = ImageCache::getFromMemory(BinaryData::knob_small_png, BinaryData::knob_small_pngSize);
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);
};

#endif /* SMALLKNOB_H_INCLUDED */
