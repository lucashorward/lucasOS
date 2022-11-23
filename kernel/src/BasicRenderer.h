#pragma once
#include "Math.h"
#include "SimpleFonts.h"
#include "Framebuffer.h"

class BasicRenderer
{
public:
    BasicRenderer(Framebuffer *targetFramebuffer, PSF1_FONT *psf1_Font);
    Point CursorPosition;
    Framebuffer *TargetFramebuffer;
    PSF1_FONT *PSF1_Font;
    unsigned int Colour;
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void Print(const char *str);
};
