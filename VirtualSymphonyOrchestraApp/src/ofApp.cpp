#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	ofSetEscapeQuitsApp(false);

	play.addListener(this, &ofApp::playPressed);
	learnPlay.addListener(this, &ofApp::playPressed);
	conductModeButton.addListener(this, &ofApp::conductModeSelected);
	learnModeButton.addListener(this, &ofApp::learnModeSelected);
	back.addListener(this, &ofApp::backPressed);
	learnBack.addListener(this, &ofApp::backPressed);

	// Main screen gui
	guiModeSelection.setup("", "settings.xml", screenWidth/2, screenHeight/2);
	//guiModeSelection.add(conductModeButton.setup("conduct", 50.0F, 50.0F));
	//guiModeSelection.add(learnModeButton.setup("learn", 50.0F, 50.0F));
	conductModeButton.setup("Conduct", 30.0F, 30.0F);
	conductModeButton.setPosition(ofPoint(screenWidth/2-15, screenHeight/2-15));
	learnModeButton.setup("Learn", 30.0F, 30.0F);
	learnModeButton.setPosition(ofPoint(screenWidth / 2 - 15, screenHeight / 2 + 15));
	 
	// Conduct mode gui
	//gui.setup();
	gui.setup("", "settings.xml", 50.0F, 50.0F);
	gui.add(play.setup("play"));
	gui.add(volume.setup("volume", 1.0, 0.0, 1.0));
	gui.add(speed.setup("tempo", 1.0, 0.5, 2.0));
	gui.add(background.setup("background", 0, 0, 8));
	gui.add(instruments.setup("instruments", -1, -1, 11));
	gui.add(back.setup("back"));

	// Learn mode gui
	
	learnGui.setup("", "settings.xml", 50.0F, 500.0F);
	learnGui.add(learnPlay.setup("play"));
	learnGui.add(learnVolume.setup("volume", 1.0, 0.0, 1.0));
	learnGui.add(learnSpeed.setup("tempo", 1.0, 0.5, 2.0));
	learnGui.add(learnBackground.setup("background", 0, 0, 8));
	learnGui.add(learnPattern.setup("pattern", 1, 1, 3));
	learnGui.add(learnBack.setup("back"));
	
	finalVideo = new unsigned char[1440 * 1080 * 3];
	finalTexture.allocate(1440, 1080, GL_RGB);

	readInputFiles();

	for (int i = 0; i < 12; i++) {
		showInstrumentsVect.push_back(1);
	}

}

void ofApp::setupTheVideo() {
	video.loadMovie(videosDirectory + videoFile);
	video.setLoopState(OF_LOOP_NONE);
}

//--------------------------------------------------------------
void ofApp::update() {
	video.update();

	if (instruments == -1) {
		for (int z = 0; z < 12; z++) {
			instrumentsArr[z] = 1;
		}
	}
	else {
		for (int z = 0; z < 12; z++) {
			instrumentsArr[z] = 1;
		}
		instrumentsArr[instruments % 12] = 0;
		instrumentsArr[((instruments + 1) % 12)] = 0;
		instrumentsArr[((instruments + 2) % 12)] = 0;
		instrumentsArr[((instruments + 3) % 12)] = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	if(conductMode == 1 && learnMode == 0) {
		if (video.isFrameNew()) {

			unsigned char* pixels = video.getPixels();
			unsigned char* backgroundpixels = backgroundVect.at(background).getPixels();
			int nChannels = video.getPixelsRef().getNumChannels();
			int widthOfLine = video.getWidth();

			for (int j = 0; j < 1080; j++) {
				for (int i = 0; i < 1440; i++) {
					int red = pixels[(j * widthOfLine + i) * nChannels];
					int green = pixels[(j * widthOfLine + i) * nChannels + 1];
					int blue = pixels[(j * widthOfLine + i) * nChannels + 2];

					if (green <= 255 && green > 180) {
						finalVideo[(j * widthOfLine + i) * nChannels] = backgroundpixels[(j * widthOfLine + i) * nChannels];
						finalVideo[(j * widthOfLine + i) * nChannels + 1] = backgroundpixels[(j * widthOfLine + i) * nChannels + 1];
						finalVideo[(j * widthOfLine + i) * nChannels + 2] = backgroundpixels[(j * widthOfLine + i) * nChannels + 2];
					}

					else {
						finalVideo[(j * widthOfLine + i) * nChannels] = pixels[(j * widthOfLine + i) * nChannels];
						finalVideo[(j * widthOfLine + i) * nChannels + 1] = pixels[(j * widthOfLine + i) * nChannels + 1];
						finalVideo[(j * widthOfLine + i) * nChannels + 2] = pixels[(j * widthOfLine + i) * nChannels + 2];
					}
				}
			}

			for (int p = 0; p < componentCoordinateInfoVect.size(); p++) {
				if (instrumentsArr[p] == 0 && (video.getCurrentFrame() != video.getTotalNumFrames())) {
					ofImage x;
					x.cropFrom(backgroundVect.at(background), componentCoordinateInfoVect.at(p).x, componentCoordinateInfoVect.at(p).y, componentCoordinateInfoVect.at(p).width, componentCoordinateInfoVect.at(p).height);
					unsigned char* xPixels = x.getPixels();
					int widthOfLine1 = x.getWidth();
					//cout << "Height: " << x.getHeight() << " Width: " << x.getWidth() << endl;
					for (int j = 0; j < componentCoordinateInfoVect.at(p).height; j++) {
						for (int i = 0; i < componentCoordinateInfoVect.at(p).width; i++) {
							finalVideo[((j + componentCoordinateInfoVect.at(p).y) * widthOfLine + (i + componentCoordinateInfoVect.at(p).x)) * nChannels] = xPixels[(j * widthOfLine1 + i) * nChannels];
							finalVideo[((j + componentCoordinateInfoVect.at(p).y) * widthOfLine + (i + componentCoordinateInfoVect.at(p).x)) * nChannels + 1] = xPixels[(j * widthOfLine1 + i) * nChannels + 1];
							finalVideo[((j + componentCoordinateInfoVect.at(p).y) * widthOfLine + (i + componentCoordinateInfoVect.at(p).x)) * nChannels + 2] = xPixels[(j * widthOfLine1 + i) * nChannels + 2];
						}
					}
				}
			}


			if (video.getCurrentFrame() == video.getTotalNumFrames()) {
				start = 0;
				playing = 0;
			}

			finalTexture.loadData(finalVideo, 1440, 1080, GL_RGB);
		}
		finalTexture.draw(0, 0, 1440, 1080);
		//video.draw(0, 0, 1440, 1080);
		video.setVolume(volume);
		video.setSpeed(speed);
		float x = (speed - 1) * 100;
		counter = x;

		gui.draw();
	}

	else if (conductMode == 0 && learnMode == 1) {
		if (video.isFrameNew()) {

			unsigned char* pixels = video.getPixels();
			unsigned char* backgroundpixels = backgroundVect.at(learnBackground).getPixels();
			int nChannels = video.getPixelsRef().getNumChannels();
			int widthOfLine = video.getWidth();

			for (int j = 0; j < 1080; j++) {
				for (int i = 0; i < 1440; i++) {
					int red = pixels[(j * widthOfLine + i) * nChannels];
					int green = pixels[(j * widthOfLine + i) * nChannels + 1];
					int blue = pixels[(j * widthOfLine + i) * nChannels + 2];

					if (green <= 255 && green > 180) {
						finalVideo[(j * widthOfLine + i) * nChannels] = backgroundpixels[(j * widthOfLine + i) * nChannels];
						finalVideo[(j * widthOfLine + i) * nChannels + 1] = backgroundpixels[(j * widthOfLine + i) * nChannels + 1];
						finalVideo[(j * widthOfLine + i) * nChannels + 2] = backgroundpixels[(j * widthOfLine + i) * nChannels + 2];
					}

					else {
						finalVideo[(j * widthOfLine + i) * nChannels] = pixels[(j * widthOfLine + i) * nChannels];
						finalVideo[(j * widthOfLine + i) * nChannels + 1] = pixels[(j * widthOfLine + i) * nChannels + 1];
						finalVideo[(j * widthOfLine + i) * nChannels + 2] = pixels[(j * widthOfLine + i) * nChannels + 2];
					}
				}
			}

			if (video.getCurrentFrame() == video.getTotalNumFrames()) {
				start = 0;
				playing = 0;
			}

			finalTexture.loadData(finalVideo, 1440, 1080, GL_RGB);
		}
		finalTexture.draw(0, 0, 1440, 1080);
		//video.draw(0, 0, 1440, 1080);
		video.setVolume(learnVolume);
		video.setSpeed(learnSpeed);
		float x = (learnSpeed - 1) * 100;
		counter = x;
		learnGui.draw();
	
	}

	else if (conductMode == 0 && learnMode == 0) {
		//guiModeSelection.draw();
		conductModeButton.draw();
		learnModeButton.draw();
		
	}
}

void ofApp::playPressed() {
	if (playing == 0) {
		setupTheVideo();
		start = 1;
		//speed = 1.0;
		//background = 0;
		instruments = -1;
		playing = 1;
		video.play();
	}
}

void ofApp::backPressed() {
	if (playing == 0) {
		conductMode = 0;
		learnMode = 0;
		speed = 1.0;
		background = 0;
		instruments = -1;
	}
}

void ofApp::conductModeSelected() {
	conductMode = 1;
	learnMode = 0;
}

void ofApp::learnModeSelected() {
	conductMode = 0;
	learnMode = 1;
}

void ofApp::readInputFiles() {
	for (int i = 0; i < backgroundImagesVect.size(); i++) {
	std:string imgPath = imgsDirectory + backgroundImagesVect.at(i);
		backgroundImg.load(imgPath);
		backgroundImg.resize(1440, 1080);
		backgroundVect.push_back(backgroundImg);
	}

	componentCoordinateInfoVect.push_back({ 22,600,311,471 });
	componentCoordinateInfoVect.push_back({ 354,600,351,471 });
	componentCoordinateInfoVect.push_back({ 1087,400,112,202 });
	componentCoordinateInfoVect.push_back({ 840,400,242,202 });
	componentCoordinateInfoVect.push_back({ 311,400,212,202 });
	componentCoordinateInfoVect.push_back({ 124,375,182,227 });
	componentCoordinateInfoVect.push_back({ 1073,610,347,462 });
	componentCoordinateInfoVect.push_back({ 726,610,327,462 });
	componentCoordinateInfoVect.push_back({ 528,300,307,302 });
	componentCoordinateInfoVect.push_back({ 1204,405,112,197 });
	componentCoordinateInfoVect.push_back({ 7,400,112,202 });
	componentCoordinateInfoVect.push_back({ 1321,420,112,182 });
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
