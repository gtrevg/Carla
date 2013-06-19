/*
 * DISTRHO PingPongPan Plugin, based on PingPongPan by Michael Gruhn
 * Copyright (C) 2012-2013 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * For a full copy of the license see the LGPL.txt file
 */

#include "DistrhoUIPingPongPan.hpp"

#include "dgl/ImageAboutWindow.hpp"

START_NAMESPACE_DISTRHO

// -------------------------------------------------

DistrhoUIPingPongPan::DistrhoUIPingPongPan()
    : OpenGLUI(),
      fAboutWindow(this)
{
    // background
    fImgBackground = Image(DistrhoArtworkPingPongPan::backgroundData, DistrhoArtworkPingPongPan::backgroundWidth, DistrhoArtworkPingPongPan::backgroundHeight, GL_BGR);

    Image imageAbout(DistrhoArtworkPingPongPan::aboutData, DistrhoArtworkPingPongPan::aboutWidth, DistrhoArtworkPingPongPan::aboutHeight, GL_BGR);
    fAboutWindow.setImage(imageAbout);

    // knobs
    Image knobImage(DistrhoArtworkPingPongPan::knobData, DistrhoArtworkPingPongPan::knobWidth, DistrhoArtworkPingPongPan::knobHeight);

    // knob Low-Mid
    fKnobFreq = new ImageKnob(this, knobImage);
    fKnobFreq->setPos(61, 59);
    fKnobFreq->setRange(0.0f, 100.0f);
    fKnobFreq->setValue(50.0f);
    fKnobFreq->setCallback(this);

    // knob Mid-High
    fKnobWidth = new ImageKnob(this, knobImage);
    fKnobWidth->setPos(183, 59);
    fKnobWidth->setRange(0.0f, 100.0f);
    fKnobWidth->setValue(75.0f);
    fKnobWidth->setCallback(this);

    // about button
    Image aboutImageNormal(DistrhoArtworkPingPongPan::aboutButtonNormalData, DistrhoArtworkPingPongPan::aboutButtonNormalWidth, DistrhoArtworkPingPongPan::aboutButtonNormalHeight);
    Image aboutImageHover(DistrhoArtworkPingPongPan::aboutButtonHoverData, DistrhoArtworkPingPongPan::aboutButtonHoverWidth, DistrhoArtworkPingPongPan::aboutButtonHoverHeight);
    fButtonAbout = new ImageButton(this, aboutImageNormal, aboutImageHover, aboutImageHover);
    fButtonAbout->setPos(183, 8);
    fButtonAbout->setCallback(this);
}

DistrhoUIPingPongPan::~DistrhoUIPingPongPan()
{
    delete fKnobFreq;
    delete fKnobWidth;
    delete fButtonAbout;
}

// -------------------------------------------------
// DSP Callbacks

void DistrhoUIPingPongPan::d_parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistrhoPluginPingPongPan::paramFreq:
        fKnobFreq->setValue(value);
        break;
    case DistrhoPluginPingPongPan::paramWidth:
        fKnobWidth->setValue(value);
        break;
    }
}

void DistrhoUIPingPongPan::d_programChanged(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fKnobFreq->setValue(50.0f);
    fKnobWidth->setValue(75.0f);
}

// -------------------------------------------------
// Widget Callbacks

void DistrhoUIPingPongPan::imageButtonClicked(ImageButton* button, int)
{
    if (button != fButtonAbout)
        return;

    fAboutWindow.exec();
}

void DistrhoUIPingPongPan::imageKnobDragStarted(ImageKnob* knob)
{
    if (knob == fKnobFreq)
        d_editParameter(DistrhoPluginPingPongPan::paramFreq, true);
    else if (knob == fKnobWidth)
        d_editParameter(DistrhoPluginPingPongPan::paramWidth, true);
}

void DistrhoUIPingPongPan::imageKnobDragFinished(ImageKnob* knob)
{
    if (knob == fKnobFreq)
        d_editParameter(DistrhoPluginPingPongPan::paramFreq, false);
    else if (knob == fKnobWidth)
        d_editParameter(DistrhoPluginPingPongPan::paramWidth, false);
}


void DistrhoUIPingPongPan::imageKnobValueChanged(ImageKnob* knob, float value)
{
    if (knob == fKnobFreq)
        d_setParameterValue(DistrhoPluginPingPongPan::paramFreq, value);
    else if (knob == fKnobWidth)
        d_setParameterValue(DistrhoPluginPingPongPan::paramWidth, value);
}

void DistrhoUIPingPongPan::onDisplay()
{
    fImgBackground.draw();
}

// -------------------------------------------------

UI* createUI()
{
    return new DistrhoUIPingPongPan();
}

// -------------------------------------------------

END_NAMESPACE_DISTRHO
