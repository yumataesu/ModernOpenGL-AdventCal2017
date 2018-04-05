#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    imgui.setup();
    raymarch_shader.load("shader/raymarch_shader");
    geo_shader.load("shader/geo_shader");
    phong_shader.load("shader/phong_shader");
    
    
    box.set(4);
    
    camera.setNearClip(0.1);
    camera.setFarClip(500);
    camera.setFov(70);
    camera.setDistance(5.0);
    projection_matrix = camera.getProjectionMatrix();
    
    
    
    //allocate G-Buffer---------------------------------------
    ofDisableArbTex();
    vector<GLint> formats = { GL_RGBA16F, GL_RGBA16F, GL_RGBA16F };
    ofFbo::Settings settings;
    settings.width = WIDTH;
    settings.height = HEIGHT;
    settings.textureTarget = GL_TEXTURE_2D;
    settings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
    settings.wrapModeVertical = GL_CLAMP_TO_EDGE;
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;
    settings.numColorbuffers = 3;
    settings.colorFormats = formats;
    settings.numSamples = 4;
    settings.useDepth = true;
    settings.useStencil = true;
    g_buffer.allocate(settings);
    g_buffer.checkStatus();
    ofEnableArbTex();
    
    
    quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    quad.addVertex(ofVec3f(1.0, 1.0, 0.0)); // top-right
    quad.addTexCoord(ofVec2f(1.0f, 1.0f));
    quad.addVertex(ofVec3f(1.0, -1.0, 0.0)); //bottom-right
    quad.addTexCoord(ofVec2f(1.0f, 0.0f));
    quad.addVertex(ofVec3f(-1.0, -1.0, 0.0)); //bottom-left
    quad.addTexCoord(ofVec2f(0.0f, 0.0f));
    quad.addVertex(ofVec3f(-1.0, 1.0, 0.0)); //top-left
    quad.addTexCoord(ofVec2f(0.0f, 1.0f));
    
}

//--------------------------------------------------------------
void ofApp::update() {
    current_time = ofGetElapsedTimef();
    delta_time = current_time - previous_time;
    previous_time = current_time;
    
    angle += (delta_time * speed);
    
    box.set(boxSize);
    box.rotate(angle, 0.1, 1.0, -0.3);

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    glEnable(GL_DEPTH_TEST);
    
    
    //1. render geometry to G-Buffer-------------------------------
    g_buffer.begin();
    g_buffer.activateAllDrawBuffers();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.begin();
    ofMatrix4x4 viewMatrix = ofGetCurrentViewMatrix();
    geo_shader.begin();
    geo_shader.setUniformMatrix4f("view", viewMatrix);
    geo_shader.setUniformMatrix4f("projection", projection_matrix);
    geo_shader.setUniformMatrix4f("model", box.getGlobalTransformMatrix());
    geo_shader.setUniform1i("u_isLight", 0);
    box.draw();
    geo_shader.setUniform1i("u_isLight", 1);
    ofSpherePrimitive s;
    s.set(0.3, 5);
    s.setPosition(lightPos);
    s.draw();
    geo_shader.end();
    camera.end();
    g_buffer.end();
    
    
    // 2. render raymarching---------------------------------------
    g_buffer.begin();
    g_buffer.activateAllDrawBuffers();
    camera.begin();
    raymarch_shader.begin();
    raymarch_shader.setUniform1f("u_time" , ofGetElapsedTimef());
    raymarch_shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    raymarch_shader.setUniform3f("u_camPos", camera.getGlobalPosition() );
    raymarch_shader.setUniform3f("u_camUp", camera.getUpDir());
    raymarch_shader.setUniform1f("u_fov", camera.getFov());
    raymarch_shader.setUniform1f("u_far", camera.getFarClip());
    raymarch_shader.setUniform1f("u_near", camera.getNearClip());
    raymarch_shader.setUniformMatrix4f("view", viewMatrix);
    raymarch_shader.setUniformMatrix4f("projection", projection_matrix);
    raymarch_shader.setUniform1f("u_radius", radius);
    quad.draw();
    raymarch_shader.end();
    camera.end();
    g_buffer.end();
    
    
    
    // 3. lighting Pass--------------------------------------------
    glDisable(GL_DEPTH_TEST);
    phong_shader.begin();
    phong_shader.setUniformTexture("gPosition", g_buffer.getTexture(0), 0);
    phong_shader.setUniformTexture("gNormal", g_buffer.getTexture(1), 1);
    phong_shader.setUniformTexture("gAlbedo", g_buffer.getTexture(2), 2);
    phong_shader.setUniform3f("u_lightPos", lightPos * viewMatrix);
    phong_shader.setUniform3f("viewPos", camera.getPosition());
    quad.draw();
    phong_shader.end();
    
    if(bgui) this->drawGui();
    
}

void ofApp::drawGui() {
    imgui.begin();
    ImGui::Begin("Position");
    ImGui::ImageButton((ImTextureID)(uintptr_t) g_buffer.getTexture(0).getTextureData().textureID, ImVec2(128, 72));
    
    ImGui::Text("Normal");
    ImGui::ImageButton((ImTextureID)(uintptr_t) g_buffer.getTexture(1).getTextureData().textureID, ImVec2(128, 72));
    
    ImGui::Text("Albedo");
    ImGui::ImageButton((ImTextureID)(uintptr_t) g_buffer.getTexture(2).getTextureData().textureID, ImVec2(128, 72));
    
    ImGui::End();
    
    ImGui::Text("Objects");
    ImGui::SliderFloat("Sphere Size", &radius, 0.1, 1.0);
    ImGui::SliderFloat("Box Size", &boxSize, 0.1, 10.0);
    ImGui::SliderFloat("Speed", &speed, 0.1, 3.0);
    
    ImGui::Text("Light");
    ImGui::SliderFloat("X", &lightPos.x, -10.0, 10.0);
    ImGui::SliderFloat("Y", &lightPos.y, -10.0, 10.0);
    ImGui::SliderFloat("Z", &lightPos.z, -10.0, 10.0);
    
    imgui.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g') bgui = !bgui;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

