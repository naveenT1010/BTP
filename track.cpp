#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
	Mat frame;
	Ptr<Tracker> tracker = Tracker::create("KCF");
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
	cout<<"Starting"<<endl;
	
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
	return 0;	
}
