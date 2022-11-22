typedef unsigned long long size_t;

typedef struct
{
    void *BaseAddress;
    size_t BufferSize;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanline;
} Framebuffer;

typedef struct
{
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
} PSF1_HEADER;

typedef struct
{
    PSF1_HEADER *psf1_Header;
    void *glyphBuffer;
} PSF1_FONT;

typedef struct {
    unsigned int X;
    unsigned int Y;
} Point;

void putChar(Framebuffer *frameBuffer, PSF1_FONT *psf1_font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int *pixPtr = (unsigned int *)frameBuffer->BaseAddress;
    char *fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * frameBuffer->PixelsPerScanline)) = colour;
            }
        }
        fontPtr++;
    }
}

Point CursorPosition;
void Print(Framebuffer *frameBuffer, PSF1_FONT *psf1_font, unsigned int colour, char* str) {
    char* chr = str;
    while (*chr != 0) {
        putChar(frameBuffer, psf1_font, colour, *chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X += 8;
        if (CursorPosition.X + 8 > frameBuffer->Width) {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}

void _start(Framebuffer *framebuffer, PSF1_FONT *psf1_font)
{
    CursorPosition.X = 50;
    CursorPosition.Y = 120;
    for (int i = 0; i < 50; i+=1) {
        Print(framebuffer, psf1_font, 0xffffffff, "Hello kernel");
    }
    return;
}
