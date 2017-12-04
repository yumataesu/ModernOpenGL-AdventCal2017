#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shader");
    
    
    // openGL
    GLfloat vertices[] = {
        // Positions
        0.5f, -0.5f, 0.0f,     // Bottom Right
        -0.5f, -0.5f, 0.0f,     // Bottom Left
        0.0f,  0.5f, 0.0f     // Top
    };
    
    GLfloat colors[] = {
        // Colors
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };
    
    
    {
        
        glGenBuffers(1, &vertex_vbo);
        glGenBuffers(1, &color_vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        
        
        
        glGenVertexArrays(1, &vao);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(vao);
        
        
        // Position attribute
        glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        
        // Color attribute
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    
    // oF
    std::array<ofVec3f, 3> of_vertex;
    of_vertex[0] = ofVec3f(0.5f,  0.5f, 0.0f);
    of_vertex[1] = ofVec3f(-0.5f, 0.5f, 0.0f);
    of_vertex[2] = ofVec3f(0.0f, -0.5f, 0.0f);
    
    std::array<ofFloatColor, 3> of_color;
    of_color[0] = ofFloatColor(1.0f, 0.0f, 1.0f, 1.0f);
    of_color[1] = ofFloatColor(1.0f, 1.0f, 0.0f, 1.0f);
    of_color[2] = ofFloatColor(0.0f, 1.0f, 1.0f, 1.0f);
    
    
    
    {
        of_vao.bind();
        of_vao.setVertexData(&of_vertex[0], 3 * sizeof(ofVec3f), GL_STATIC_DRAW);
        of_vao.setColorData(&of_color[0], 3 * sizeof(ofFloatColor), GL_STATIC_DRAW);
        of_vao.unbind();
    }
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    glClearColor(0.0, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    shader.begin();
    
    if(!is_ofApi)
    {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
    
    else
    {
        of_vao.draw(GL_TRIANGLES, 0, 3);
    }
    
    shader.end();
    
    if(!is_ofApi) ofDrawBitmapString("openGL Triangle", 20, 30);
    else ofDrawBitmapString("oF Triangle", 20, 30);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') is_ofApi = !is_ofApi;
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
