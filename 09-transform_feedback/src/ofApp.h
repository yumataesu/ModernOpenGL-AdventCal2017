#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void lateDrawUpdate();
    void drawGui();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofShader render_shader, feedback_shader;
    GLuint transform_feedback = 0;
    
    ofEasyCam camera;
    ofBufferObject TransformBuffer, FeedbackBuffer;
    std::array<ofVbo, 2> feedback_vao;
    
    
    static const int NUM = 1000000;
    struct Particle {
        ofVec3f position;
        ofVec3f accel;
        ofVec3f velocity;
        float lifetime;
        ofVec3f color;
    };
    
    Particle particle[NUM];
    
};
