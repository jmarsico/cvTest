#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"


class testApp : public ofBaseApp{

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		

 
    ofVideoPlayer 		vidPlayer;      //set up videoplayer object

    //allocate memory for different opencv images
    ofxCvColorImage			colorImg;
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;

    ofxCvContourFinder 	contourFinder;
    
    ofPixels grIMG;
    ofPixels bgIMG;
    ofPixels diffIMG;
    ofPixels finalIMG;
    ofImage image;
    ofImage finalImage;

    int threshold;
    bool bLearnBakground;
    bool bStartIMG;
    float vidHeight;
    float vidWidth;


};

