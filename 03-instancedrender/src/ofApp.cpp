#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    of_shader.load("shader/of_shader");
    shader.load("shader/shader");
    
    ofVec3f vertices[4];
    vertices[0] = ofVec3f(-0.7f, -0.7f, 0.0f);
    vertices[1] = ofVec3f(0.7f,-0.7f, 0.0f);
    vertices[2] = ofVec3f(0.7f, 0.7f, 0.0f);
    vertices[3] = ofVec3f(-0.7f,0.7f, 0.0f);
    
    ofIndexType indices[] = {0, 1, 2, 0, 3, 2};
    
    float R = 200;
    for(auto&& p : positions) {
        p = ofVec3f(ofRandom(-R, R), ofRandom(-R, R), ofRandom(-R, R));
    }
    
    for(auto&& c : colors) {
        c = ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0);
    }
    
    
    
    {
        
        // Raw OpenGL
        glGenBuffers(1, &vert_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(ofVec3f), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glGenBuffers(1, &pos_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
        glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(ofVec3f), &positions, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glGenBuffers(1, &col_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, col_vbo);
        glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(ofFloatColor), &colors, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vert_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, col_vbo);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        // Element Array Buffer
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        
        glBindVertexArray(0);
    }
    
    //        enum defaultAttributes{
    //            POSITION_ATTRIBUTE=0,  // tig: was =1, and BOY, what a performance hog this was!!! see: http://www.chromium.org/nativeclient/how-tos/3d-tips-and-best-practices
    //            COLOR_ATTRIBUTE,
    //            NORMAL_ATTRIBUTE,
    //            TEXCOORD_ATTRIBUTE,
    //            INDEX_ATTRIBUTE  // usually not used except for compute shades
    //        };
    
    
    // oF
    {
        of_pos_vbo.allocate();
        of_pos_vbo.bind(GL_ARRAY_BUFFER);
        of_pos_vbo.setData(sizeof(ofVec3f) * 10000, &positions, GL_STATIC_DRAW);
        of_pos_vbo.unbind(GL_ARRAY_BUFFER);
        
        
        of_vao.bind();
        of_vao.setVertexData(vertices, 4, GL_STATIC_DRAW);
        of_vao.setColorData(&colors[0], 10000, GL_STATIC_DRAW);
        of_vao.setAttributeBuffer(4, of_pos_vbo, 3, 0, 0);
        
        of_vao.setIndexData(indices, 6, GL_STATIC_DRAW);
        
        of_vao.setAttributeDivisor(0, 0);
        of_vao.setAttributeDivisor(1, 1);
        of_vao.setAttributeDivisor(4, 1);
        of_vao.unbind();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    
    ofEnableDepthTest();
    
    cam.begin();
    
    if(!is_of) {
        shader.begin();
        glBindVertexArray(vao);
        glDrawElementsInstanced(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, NULL, 10000);
        glBindVertexArray(0);
        shader.end();
    } else {
        of_shader.begin();
        of_vao.drawElementsInstanced(GL_TRIANGLE_STRIP, 6, 10000);
        of_shader.end();
        
    }
    cam.end();
    
    
    ofDrawBitmapString("Press space-key", 10, 10);
    if(!is_of) ofDrawBitmapString("with Raw OpenGL", 10, 30);
    else ofDrawBitmapString("with oF", 10, 50);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == ' ') is_of = !is_of;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
