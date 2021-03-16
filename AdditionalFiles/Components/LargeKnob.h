#ifndef LARGEKNOB_H_INCLUDED
#define LARGEKNOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class LargeKnob : public LookAndFeel_V3
{
public:
    Image sprite = ImageCache::getFromMemory(BinaryData::knob_large_png, BinaryData::knob_large_pngSize);
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);
};

#endif /* LARGEKNOB_H_INCLUDED */
