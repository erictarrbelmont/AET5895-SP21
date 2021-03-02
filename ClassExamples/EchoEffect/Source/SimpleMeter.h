//
//  SimpleMeter.h
//
//
//  Copyright © 2019 Eric Tarr. All rights reserved.
//  Code may not be distributed without permission
//
//  Based on Inter-App Audio Plugin (https://docs.juce.com/master/tutorial_plugin_examples.html )
//
//  This class creates a meter component which draws a value between 0 and 1

#ifndef SimpleMeter_h
#define SimpleMeter_h

// Class definition
class SimpleMeter  : public Component,
                    private Timer
{
public:
    SimpleMeter()
    {
        startTimerHz (30);
    }
    
    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (Colours::transparentBlack);
        
        auto area = g.getClipBounds();
        
        
        auto unfilledHeight = area.getHeight() * (1.0 - level);
        auto unfilledWidth = area.getWidth() * (1.0 - level);
        
        switch (configuration) {
            case VERTICAL:
                g.setColour (getLookAndFeel().findColour (Slider::thumbColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                g.reduceClipRegion (area.getX(), area.getY(),
                                    area.getWidth(), (int) unfilledHeight);
                g.setColour (getLookAndFeel().findColour (Slider::trackColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                break;
            
            case HORIZONTAL:
                g.setColour (getLookAndFeel().findColour (Slider::trackColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                g.reduceClipRegion (area.getX(), area.getY(),
                                    area.getWidth() - (int) unfilledWidth,area.getHeight());
                g.setColour (getLookAndFeel().findColour (Slider::thumbColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                break;
            
            case GAINREDUCTION:
                g.setColour (getLookAndFeel().findColour (Slider::thumbColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                g.reduceClipRegion (area.getX(), area.getY(),
                                    area.getWidth() - (int) unfilledWidth,area.getHeight());
                g.setColour (getLookAndFeel().findColour (Slider::trackColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                break;
                
            default: // Vertical
                g.setColour (getLookAndFeel().findColour (Slider::thumbColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                g.reduceClipRegion (area.getX(), area.getY(),
                                    area.getWidth(), (int) unfilledHeight);
                g.setColour (getLookAndFeel().findColour (Slider::trackColourId));
                g.fillRoundedRectangle (area.toFloat(), 6.0);
                
                break;
        }
        
        
    }
    
    void resized() override {}
    
    //==============================================================================
    // Called from the audio thread.
    void update (float newLevel)
    {
        // make sure it doesn't go above the maximum possible level of 1
        maxLevel = jmin (newLevel,1.0f);
        
    }
    
    enum Configuration {HORIZONTAL,VERTICAL,GAINREDUCTION};
    Configuration configuration = VERTICAL;
    
private:
    //==============================================================================
    void timerCallback() override
    {
        auto callbackLevel = maxLevel.load();//exchange(1.0);
        
        if (callbackLevel > 0.000001)
            level = callbackLevel;
        else
            level = 0; // Round down to zero, if the value is very small
        
        repaint();
    }
    
    std::atomic<float> maxLevel { 0.0f };
    float level = 0.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMeter)
};


#endif 
