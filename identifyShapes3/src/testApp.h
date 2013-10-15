#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "shape.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
    
        void findNeighborPixels(int pxIdx, unsigned char * sourcePixels, unsigned char * destPixels, unsigned char * destOutline);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        unsigned char onValue = 0;
        unsigned char offValue = 255;
        
        ofImage sourceImage;
        ofxCvGrayscaleImage thresholdImage;
        ofxCvColorImage resultImage;
        
        vector<shape>shapes;
        int prevShape;
    
        ofVideoGrabber cam;  
    
		
};
