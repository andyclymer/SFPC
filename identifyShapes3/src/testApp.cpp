#include "testApp.h"
#include "shape.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //ofSetFrameRate(1);
    
    sourceImage.loadImage("shapeImage2.jpg");
    thresholdImage.allocate(sourceImage.width, sourceImage.height);
    resultImage.allocate(sourceImage.width, sourceImage.height);

}

//--------------------------------------------------------------
void testApp::update(){
    
    ofSetWindowTitle( ofToString(ofGetFrameRate()) );
    
    shapes.clear();
    
    unsigned char * pixelsSource = sourceImage.getPixels();
    
    ofxCvColorImage tempImage;
    tempImage.setFromPixels(pixelsSource, sourceImage.width, sourceImage.height);

    thresholdImage = tempImage;
    thresholdImage.threshold(128);
    unsigned char * pixelsThresh = thresholdImage.getPixels();
    
    
    // Look through each pixel in the thresholdImage
    // Identify the first "on" pixel that it hits
    // Collect all neighboring "on" pixels into a new shape object image
    // Turn this pixel to gray so that it won't be found again
    // Continue until there are no more pixels remaining in the shape
    // Continue to the next pixel in thresholdImage looking for another shape
    
    for (int pxIdx = 0; pxIdx < thresholdImage.width * thresholdImage.height; pxIdx++){
        
        if (pixelsThresh[pxIdx] == onValue) {
            
            // Found an "on" pixel in the thresholdImage
            
            // Collect all "on" pixels which touch this one, and add them to the shape's image. Create a new shape object and populate the object's images for the filled in area and the outline
            shape newShape;
            // Allocate the image before pushing it to the vector
            newShape.setup(thresholdImage.width, thresholdImage.height);
            shapes.push_back(newShape);
            
            unsigned char * pixelsObject = shapes.back().objectImage.getPixels();
            unsigned char * pixelsOutline = shapes.back().outlineImage.getPixels();
            findNeighborPixels(pxIdx, pixelsThresh, pixelsObject, pixelsOutline);
            
        }
    }
    
    // Compose a "Result Image"
    
    // Copy the sourceImage to the resultImage
    resultImage.setFromPixels(pixelsSource, sourceImage.width, sourceImage.height);
    
    // Draw outlineImages in red into the resultImage
    for (int i=0; i < shapes.size(); i++){
        for (int pxIdx=0; pxIdx < sourceImage.width * sourceImage.height; pxIdx++) {
            if (shapes[i].outlineImage.getPixels()[pxIdx] == offValue){
                resultImage.getPixels()[pxIdx*3] = 255;
                resultImage.getPixels()[pxIdx*3+1] = 0;
                resultImage.getPixels()[pxIdx*3+2] = 0;
            }
        }
    }
}




//--------------------------------------------------------------
void testApp::findNeighborPixels(int pxIdx, unsigned char * sourcePixels, unsigned char * destPixels, unsigned char * destOutline){
    
    // Find the neighboring pixels in the lastShape,
    // if any of them are white, look for their neighbors to
    
    int neighborIndices [8] = {
        pxIdx - thresholdImage.width - 1,
        pxIdx - thresholdImage.width,
        pxIdx - thresholdImage.width + 1,
        pxIdx - 1,
        pxIdx + 1,
        pxIdx + thresholdImage.width - 1,
        pxIdx + thresholdImage.width,
        pxIdx + thresholdImage.width + 1
        };
    
    vector<int>foundPixels;
    bool foundEdge = false;
    
    // Look at the 8 pixels around this one and turn black ones gray,
    // holding aside their indices for further neighbor checking
    for (int i = 0; i < 8; i++ ) {
        int testIdx = neighborIndices[i];
        if (testIdx >=0) {
            if (testIdx <= thresholdImage.width * thresholdImage.height) {
                if (sourcePixels[testIdx] == onValue) {
                    foundPixels.push_back(testIdx);
                    sourcePixels[testIdx] = 128;
                    destPixels[testIdx] = 255;
                }
                // If any of the neighboring pixels are black, the pxIdx pixel is on an edge
                if (sourcePixels[testIdx] == offValue) {
                    foundEdge = true;
                }
            }
        }
    }
    
    // If any of the neighboring pixels were black, toggle this pixel as being part of an outline. @@@ Should it only check the neighboring 4 and not 8?
    if (foundEdge) {
        destOutline[pxIdx] = 255;
    }

    // Then, look at the neighbors for their own neighbor pixels
    for (int i = 0; i < foundPixels.size(); i++) {
        int testIdx = foundPixels[i];
        findNeighborPixels(testIdx, sourcePixels, destPixels, destOutline);
    }
}


//--------------------------------------------------------------
void testApp::draw(){
    
    sourceImage.draw(0, 0, sourceImage.width, sourceImage.height);
    thresholdImage.draw(sourceImage.width, 0, thresholdImage.width, thresholdImage.height);
    
    prevShape += 1;
    if (prevShape > shapes.size()-1) {
        prevShape = 0;
    }
    shapes[prevShape].objectImage.draw(0, sourceImage.height, sourceImage.width, sourceImage.height);
    
    resultImage.draw(sourceImage.width, sourceImage.height, resultImage.width, resultImage.height);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
