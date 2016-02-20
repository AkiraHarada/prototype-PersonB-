#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup(HOST,PARTNER_PORT);
    receiver.setup(SELF_PORT);
    PARTNERButtonCondition = false;
    box2d.init();
    box2d.setFPS(60);
    box2d.setGravity(0, 10);
    box2d.registerGrabbing();
    PARTNERmouse = ofPoint(0, 0);
    ofBackground(255);
}


//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    box2d.createGround();
    while(receiver.hasWaitingMessages()){
        ofxOscMessage message;
        receiver.getNextMessage(&message);
        if(message.getAddress() == "/mouse/position"){
            PARTNERmouse = ofPoint(message.getArgAsInt32(0),message.getArgAsInt32(1));
            float radius = ofRandom(4,20);
            ofPtr <ofxBox2dCircle> _circle = ofPtr <ofxBox2dCircle> (new ofxBox2dCircle);
            _circle.get()->setPhysics(0.53, 0.3, 0.1);
            _circle.get()->setup(box2d.getWorld(), PARTNERmouse.x, PARTNERmouse.y, radius);
            CirclesOfPARTNER.push_back(_circle);
        }else if (message.getAddress() == "/mouse/button"){
            PARTNERButtonCondition = message.getArgAsInt32(0);
            if(PARTNERButtonCondition == true){
                float radius = ofRandom(4,20);
                ofPtr <ofxBox2dCircle> _circle = ofPtr <ofxBox2dCircle> (new ofxBox2dCircle);
                _circle.get()->setPhysics(0.53, 0.3, 0.1);
                _circle.get()->setup(box2d.getWorld(), PARTNERmouse.x, PARTNERmouse.y, radius);
                CirclesOfPARTNER.push_back(_circle);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < CirclesOfSELF.size(); i++){
        ofSetColor(0, 0, 255);
        CirclesOfSELF[i].get()->draw();
    }
    for(int i = 0; i < CirclesOfPARTNER.size(); i++){
        ofSetColor(255, 0, 0);
        CirclesOfPARTNER[i].get()->draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofxOscMessage message;
    message.setAddress("/mouse/button");
    message.addIntArg(1);
    sender.sendMessage(message);
    if(key=='c'){
        float radius = ofRandom(4, 20);
        ofPtr <ofxBox2dCircle> _circle =ofPtr <ofxBox2dCircle> (new ofxBox2dCircle);
        _circle.get()->setPhysics(0.53, 0.3, 0.1);
        _circle.get()->setup(box2d.getWorld(), mouseX, mouseY, radius);
        CirclesOfSELF.push_back(_circle);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    ofxOscMessage message;
    message.setAddress("/mouse/button");
    message.addIntArg(0);
    sender.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofxOscMessage message;
    message.setAddress("/mouse/position");
    message.addIntArg(x);
    message.addIntArg(y);
    sender.sendMessage(message);
    float radius = ofRandom(4, 20);
    ofPtr <ofxBox2dCircle> _circle = ofPtr <ofxBox2dCircle> (new ofxBox2dCircle);
    _circle.get()->setPhysics(0.53, 0.3, 0.1);
    _circle.get()->setup(box2d.getWorld(), mouseX, mouseY, radius);
    CirclesOfSELF.push_back(_circle);
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofxOscMessage message;
    message.setAddress("/mouse/button");
    message.addIntArg(1);
    sender.sendMessage(message);
    float radius = ofRandom(4,20);
    ofPtr <ofxBox2dCircle> _circle = ofPtr <ofxBox2dCircle> (new ofxBox2dCircle);
    _circle.get()->setPhysics(0.53, 0.3, 0.1);
    _circle.get()->setup(box2d.getWorld(), mouseX, mouseY, radius);
    CirclesOfSELF.push_back(_circle);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofxOscMessage message;
    message.setAddress("/mouse/button");
    message.addIntArg(0);
    sender.sendMessage(message);
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
