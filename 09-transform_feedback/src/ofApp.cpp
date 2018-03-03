#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    render_shader.load("shaders/render.vert", "shaders/render.frag");
    
    feedback_shader.setupShaderFromFile(GL_VERTEX_SHADER, "shaders/feedback.vert");
    feedback_shader.setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, "shaders/feedback.geom");
    const GLchar* feedbackVaryings[] = { "o_position", "o_accel", "o_velocity", "o_lifetime", "o_color" };
    glTransformFeedbackVaryings(feedback_shader.getProgram(), 5, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
    feedback_shader.linkProgram();
    
    
    for(int i = 0; i < NUM; i++) {
        particle[i].position = ofVec3f(ofRandom(-50, 50), ofRandom(-50, 50), ofRandom(-50, 50));
        particle[i].accel = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
        particle[i].velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
        particle[i].lifetime = ofRandom(0, 100);
        particle[i].color = ofVec3f(0.1, ofRandom(0.0, 0.4), ofRandom(0.0, 0.7));
    }
    
    
    // Create and init ping pong vbo
    TransformBuffer.allocate();
    TransformBuffer.bind(GL_ARRAY_BUFFER);
    TransformBuffer.setData(sizeof(Particle) * NUM, particle, GL_STREAM_COPY);
    TransformBuffer.unbind(GL_ARRAY_BUFFER);
    
    // Create and init ping pong vbo
    FeedbackBuffer.allocate();
    FeedbackBuffer.bind(GL_ARRAY_BUFFER);
    FeedbackBuffer.setData(sizeof(Particle) * NUM, nullptr, GL_STREAM_COPY);
    FeedbackBuffer.unbind(GL_ARRAY_BUFFER);
    
    
    // Create and init ping pong vao
    for(auto&& vao : feedback_vao) {
        vao.bind();
        vao.setAttributeBuffer(0, TransformBuffer, 3, sizeof(Particle), 0);
        vao.setAttributeBuffer(1, TransformBuffer, 3, sizeof(Particle), 12);
        vao.setAttributeBuffer(2, TransformBuffer, 3, sizeof(Particle), 24);
        vao.setAttributeBuffer(3, TransformBuffer, 1, sizeof(Particle), 36);
        vao.setAttributeBuffer(4, TransformBuffer, 3, sizeof(Particle), 40);
        vao.unbind();
    }
    
    // Create and init TF
    glGenTransformFeedbacks(1, &transform_feedback);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transform_feedback);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, FeedbackBuffer.getId());
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

}

//--------------------------------------------------------------
void ofApp::update()
{
    
    glEnable(GL_RASTERIZER_DISCARD);
    
    feedback_shader.begin();
    feedback_shader.setUniform1f("u_time", ofGetElapsedTimef());
    feedback_shader.setUniform1f("u_rand", ofRandom(1.0));
    
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transform_feedback);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, FeedbackBuffer.getId());
        glBeginTransformFeedback(GL_POINTS);
        feedback_vao[0].drawInstanced(GL_POINTS, 0, NUM, 1);
        glEndTransformFeedback();
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
    feedback_shader.end();
    
    glDisable(GL_RASTERIZER_DISCARD);
}

//--------------------------------------------------------------
void ofApp::draw() {

    ofBackground(0);

    camera.begin();
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    render_shader.begin();
    render_shader.setUniform1f("u_time", ofGetElapsedTimef());
    feedback_vao[1].bind();
    feedback_vao[1].drawInstanced(GL_POINTS, 0, NUM, 1);
    feedback_vao[1].unbind();
    render_shader.end();
    camera.end();
    

    std::swap(TransformBuffer, FeedbackBuffer);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
