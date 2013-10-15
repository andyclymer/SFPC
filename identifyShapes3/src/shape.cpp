
#include "shape.h"


void shape::setup(int width, int height){
    
    // Allocate memory for the images
    objectImage.allocate(width, height);
    outlineImage.allocate(width, height);
    
    // Clear the memory
    memset(objectImage.getPixels(), 0, width * height);
    memset(outlineImage.getPixels(), 0, width * height);
    
    objectImage.flagImageChanged();
    outlineImage.flagImageChanged();
    
    
}