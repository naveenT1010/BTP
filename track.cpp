//Following are supported algos:
//1. MIL
//2. BOOSTING
//3. MEDIANFLOW
//4. TLD - Performing comparitively better than others, scale invariant, captures subject again once goes Out of Frame
//5. KCF - Problematic when subject goes out of frame and comes back in, and also with scale.

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
	Mat frame;
	Ptr<Tracker> tracker = Tracker::create("TLD");
	VideoCapture cap(0);
	int frameW, frameH;
	frameW = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	frameH = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	bool check = cap.read(frame);
	Rect2d roi;
	roi = selectROI("tracker",frame);
	if(roi.width==0 || roi.height==0)
		return -1;
	tracker->init(frame,roi);
	cout<<"Starting Tracking"<<endl;
	
	while(check){
		check = cap.read(frame);
		if(frame.rows==0 || frame.cols==0)
			break;
		tracker->update(frame,roi);
		rectangle(frame,roi,Scalar(255,0,0),2,1);
		imshow("tracker",frame);
		if(waitKey(100)==27)
			break;
	}
	cout<<"Program Exit"<<endl;
	return 0;	
}
