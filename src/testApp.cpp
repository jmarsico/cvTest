#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(100,100,100);
    vidPlayer.loadMovie("shopMall.mp4");
    vidPlayer.play();
    vidWidth = vidPlayer.getWidth();
    vidHeight = vidPlayer.getHeight();
    colorImg.allocate(854,480);
	grayImage.allocate(854,480);
	grayBg.allocate(854,480);
	grayDiff.allocate(854,480);

	bLearnBakground = true;
	threshold = 80;
    vidWidth = vidPlayer.getWidth();
    vidHeight = vidPlayer.getHeight();
    
    diffIMG.allocate(vidWidth, vidHeight, OF_IMAGE_GRAYSCALE);
    grIMG.allocate(vidWidth, vidHeight, OF_IMAGE_GRAYSCALE);
    bgIMG.allocate(vidWidth, vidHeight, OF_IMAGE_GRAYSCALE);
    finalIMG.allocate(vidWidth, vidHeight, OF_IMAGE_GRAYSCALE);
    
    bStartIMG = true;
    
    
    //black out the finalIMG
    for(int i = 0; i < vidWidth; i++)
    {
        for(int j = 0; j < vidHeight; j++)
        {
            finalIMG.setColor(i, j, 0);
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){

    

    bool bNewFrame = false;

	
    vidPlayer.update();
    bNewFrame = vidPlayer.isFrameNew();
    //test

	if (bNewFrame){

       //colorImg.setFromPixels(vidPlayer.getPixels(), 854,480);
        //grayImage = colorImg;
        
		if (bLearnBakground == true){
			bgIMG = grIMG;
            //grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            //black out the finalIMG
            for(int i = 0; i < vidWidth; i++)
            {
                for(int j = 0; j < vidHeight; j++)
                {
                    finalIMG.setColor(i, j, 0);
                }
            }
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		//grayDiff.absDiff(grayBg, grayImage);
		//grayDiff.threshold(threshold);
        
        grIMG = (vidPlayer.getPixelsRef());
        
        
        
        
        for(int i = 0; i < vidWidth; i++)
        {
            for(int j = 0; j < vidHeight; j++)
            {
               
                //create diffIMG by getting absolute value of current image - background image
                diffIMG.setColor(i,j, (abs(grIMG.getColor(i, j).getBrightness() - bgIMG.getColor(i,j).getBrightness())));
                
                //if absDiff is greater than the threshold, set diffIMG val to white
                if(diffIMG.getColor(i,j).getBrightness() > threshold)
                {
                    diffIMG.setColor(i, j, 255);
                }
                //if absDiff is lower than threshold, set diffIMG val to black
                else if(diffIMG.getColor(i,j).getBrightness() < threshold)
                {
                    diffIMG.setColor(i, j, 0);
                }
                
                
                
                if(diffIMG.getColor(i,j).getBrightness() == 255)
                {
                    finalIMG.setColor(i, j, 255);
                }
            }
        }
        
        bgIMG = grIMG;
    }

}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	//ofSetHexColor(0xffffff);
	//colorImg.draw(20,20);
	//grayImage.draw(360,20);
	//grayBg.draw(20,280);
    //grayDiff.draw(0,0);
    
    image = diffIMG;
    image.draw(0,0,vidWidth/3,vidHeight/3);
    
    finalImage = finalIMG;
    finalImage.draw(0, vidHeight/3 + 20, vidWidth/3, vidHeight/3);
    	
	// finally, a report:
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
			  << "press ' ' to capture bg" << endl
			  << "threshold " << threshold << " (press: +/-)" << endl
			  //<< "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate() << endl
              << " width: " << vidWidth <<", height: " << vidHeight;
	ofDrawBitmapString(reportStr.str(), 20, 600);
    
    
    grayBg = grayImage; //update the background image to be the current image
     

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
