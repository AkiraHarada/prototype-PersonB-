#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxBox2d.h"
#define HOST "127.0.0.1"
#define PARTNER_PORT 8889
#define SELF_PORT 8888

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    bool PARTNERButtonCondition;
    ofxBox2d box2d;
    ofPoint PARTNERmouse;
    vector <ofPtr<ofxBox2dCircle> > CirclesOfSELF,CirclesOfPARTNER;
    
    
    
};

