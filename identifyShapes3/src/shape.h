#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"


class shape : public ofBaseApp{
    
	public:
    
        void setup(int width, int height);
    
        ofxCvGrayscaleImage objectImage;
        ofxCvGrayscaleImage outlineImage;
        ofVec2f center;
        float angle;

};