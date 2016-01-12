#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>


struct ComponentCoordinateInfo
{
	int x;
	int y;
	int width;
	int height;
};


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void readInputFiles();

	void playPressed();

	void setupTheVideo();

	ofxPanel gui;

	ofxButton play;
	ofxButton stop;
	ofxFloatSlider volume;
	ofxFloatSlider speed;
	ofxIntSlider background;
	ofxIntSlider instruments;
	ofVideoPlayer video;

	int counter = 0;

	ofVideoGrabber myVidGrabber;
	int frameCounter = 0;

	unsigned char* finalVideo;

	ofTexture finalTexture;
	ofImage backgroundImg;

	int start = 0;

	std::vector<int> showInstrumentsVect;
	std::vector<ofImage> backgroundVect;
	int stopValue = 0;

	int totalFrames;
	int instrumentsArr[12] = { 1,1,1,1,1,1,1,1,1,1,1,1 };

	int playing = 0;
	std::vector<std::string> backgroundImagesVect = { "Beach1.jpg", "Beach2.jpg", "Berlin.jpg", "Church.jpg", "CoronadoBridge.jpg", "Rome.jpg", "Vatican.jpg", "Venice.jpg", "Versailles.jpg" };
	std::string videoFile = "Pinoccgreenkey180909new3.mov";
	std::string imgsDirectory = "C:/Users/efe/VSOData/Images/";
	std::string videosDirectory = "C:/Users/efe/VSOData/Video/";
	std::string soundsDirectory = "C:/Users/efe/VSOData/Sounds/";
	std::vector<ComponentCoordinateInfo> componentCoordinateInfoVect;

};

