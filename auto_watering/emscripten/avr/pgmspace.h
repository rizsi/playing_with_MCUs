// Dummy header for Arduino compatibility to compile Arduino library rizsi_DRAW

/// Progmem is omitted when compiled for emscripten
#define PROGMEM
#define pgm_read_byte_near(X) *(X)

