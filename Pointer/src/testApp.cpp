#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    ofVec2f mouseLoc(mouseX, mouseY);
    ofVec2f objectLoc(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

    float objectSizeFactor = mouseLoc.distance(objectLoc) / (ofGetWidth() * 0.5);
    float objectSize = 150 - 100 * objectSizeFactor;
    
    // The angle between two points way:
    float angle = atan2(mouseY - objectLoc[1], mouseX - objectLoc[0]) * (180 / PI);

    // The vector angle way:
    float angle2 = atan2( mouseX * objectLoc[0] - mouseY * objectLoc[1], mouseX * objectLoc[1] + mouseY * objectLoc[1] ) * (180 / PI);

    ofBackground(0);
    ofSetColor(255 - (255 * objectSizeFactor));
    ofFill();
    
    

    ofPushMatrix();
    
    ofTranslate(objectLoc[0], objectLoc[1]);
    ofRotateZ(angle);
    
    ofRect(-1 * objectSize * 0.5, -1 * objectSize * 0.25, objectSize, objectSize * 0.5);
    
    
    ofPopMatrix();

    
    
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
