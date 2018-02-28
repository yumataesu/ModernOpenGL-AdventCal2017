#pragma once

#include "ofMain.h"

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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    ofShader of_shader, shader;
    ofEasyCam cam;
    
    GLuint vert_vbo, pos_vbo, col_vbo;
    GLuint vao, vbo, ebo;
    
    std::array<ofVec3f, 10000> positions;
    std::array<ofFloatColor, 10000> colors;
    
    bool is_of;
    
    ofVbo of_vao;
    ofBufferObject of_pos_vbo;
    
};
