#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    
    ofShader raymarch_shader;
    ofMesh quad;
    
    float previous_time, current_time, delta_time;
    
    const int WIDTH = ofGetWidth();
    const int HEIGHT = ofGetHeight();
    
    ofFbo g_buffer;
    
    ofEasyCam camera;
    
    ofBoxPrimitive box;
    float radius = 0.5;
    float boxSize = 5.0;
    ofxImGui imgui;
    
    ofMatrix4x4 projection_matrix;
    ofShader geo_shader;
    ofShader phong_shader;
    
    ofVec3f lightPos = ofVec3f(1.0, 1.0, 3.0);
    bool bgui = true;
    
    float angle, speed;
    
};
