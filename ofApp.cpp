#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	this->box2d.init();
	this->box2d.setGravity(0, 50);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {

	vector<ofColor> base_color_list;
	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		base_color_list.push_back(color);
	}

	for (int i = this->circle_list.size() - 1; i > -1; i--) {

		this->life_list[i] -= 1;

		if (this->life_list[i] < 0) {

			this->circle_list.erase(this->circle_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	if (ofGetFrameNum() % 240 < 120) {

		for (int i = 0; i < 5; i++) {

			auto radius = ofRandom(2, 5);

			auto circle = make_shared<ofxBox2dCircle>();
			circle->setPhysics(0.5, 0.03, 0.1);
			circle->setup(this->box2d.getWorld(), ofRandom(ofGetWidth() * 0.35 - radius, ofGetWidth() * 0.35 + radius), 100 + radius, radius);
			circle->setRotation(ofRandom(360));
			this->circle_list.push_back(circle);
			this->radius_list.push_back(radius);
			this->life_list.push_back(250);

			this->color_list.push_back(base_color_list[ofRandom(base_color_list.size())]);
		}

	} else {

		for (int i = 0; i < 3; i++) {

			auto radius = ofRandom(5, 10);

			auto circle = make_shared<ofxBox2dCircle>();
			circle->setPhysics(0.5, 0.03, 0.1);
			circle->setup(this->box2d.getWorld(), ofRandom(ofGetWidth() * 0.65 - radius, ofGetWidth() * 0.65 + radius), 100 + radius, radius);
			circle->setRotation(ofRandom(360));
			this->circle_list.push_back(circle);
			this->radius_list.push_back(radius);
			this->life_list.push_back(250);

			this->color_list.push_back(base_color_list[ofRandom(base_color_list.size())]);
		}
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofTranslate(ofGetWidth() * -0.5, ofGetHeight() * -0.5);

	ofSetLineWidth(1);
	for (int i = 0; i < this->circle_list.size(); i++) {

		ofFill();
		ofSetColor(this->color_list[i]);
		ofDrawCircle(glm::vec2(this->circle_list[i]->getPosition()), this->radius_list[i]);

		ofNoFill();
		ofSetColor(39);
		ofDrawCircle(glm::vec2(this->circle_list[i]->getPosition()), this->radius_list[i]);

	}

	ofSetLineWidth(3);
	ofSetColor(39);
	ofDrawRectangle(0, 0, 720, 720);

	this->cam.end();
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}