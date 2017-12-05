#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shader");
    
    GLfloat vertices[] = {
        -0.7f, -0.7f, 0.0f,
        0.7f,-0.7f, 0.0f,
        0.7f, 0.7f, 0.0f,
        -0.7f,0.7f, 0.0f
    };
    
    GLfloat colors[] = {
        1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };
    
    int indices[] = {0, 1, 2, 0, 3, 2};
    
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertex_vbo);
    glGenBuffers(1, &color_vbo);
    glGenBuffers(1, &ebo);
    
    
    glBindVertexArray(vao);
    
    
    // Position attribute
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    
    // Color attribute
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    
    // Element Array Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    // oF
    
    // Position Attribute
    std::array<ofVec3f, 4> of_vertices;
    of_vertices[0] = ofVec3f(-0.7f, -0.7f, 0.0f);
    of_vertices[1] = ofVec3f(0.7f,-0.7f, 0.0f);
    of_vertices[2] = ofVec3f(0.7f, 0.7f, 0.0f);
    of_vertices[3] = ofVec3f(-0.7f,0.7f, 0.0f);
    
    // Color Attribute
    std::array<ofFloatColor, 4> of_colors;
    of_colors[0] = ofFloatColor(1.0f, 0.0f, 0.0f, 1.0f);
    of_colors[1] = ofFloatColor(0.0f, 1.0f, 0.0f, 1.0f);
    of_colors[2] = ofFloatColor(0.0f, 0.0f, 1.0f, 1.0f);
    of_colors[3] = ofFloatColor(0.0f, 1.0f, 1.0f, 1.0f);
    
    // Index Attribute
    std::array<ofIndexType, 6> of_indices = {0, 1, 2, 0, 3, 2};
    {
        of_vao.bind();
        of_vao.setVertexData(&of_vertices[0], 4 * sizeof(ofVec3f), GL_STATIC_DRAW);
        of_vao.setColorData(&of_colors[0],   4 * sizeof(ofFloatColor), GL_STATIC_DRAW);
        of_vao.setIndexData(&of_indices[0],    6 * sizeof(ofIndexType), GL_STATIC_DRAW);
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
        glBindVertexArray( vao );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );
    }
    
    else
    {
        of_vao.drawElements(GL_TRIANGLES, 6);
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
