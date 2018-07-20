// testKinect.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "KinectV1Capture.h"

int main()
{
	KinectV1Capture kinect;
	
	if (kinect.Init() != S_OK) {
		return 0;
	}
	
	bool quit = false;

	cv::Mat colorimg;
	cv::Mat depthimg;
	cv::namedWindow("ColorImage", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("DepthImage", CV_WINDOW_AUTOSIZE);
	
	colorimg.create(kinect.GetColorImgSize(), kinect.GetColorImgType());
	depthimg.create(kinect.GetDepthImgSize(), CV_16UC1);

	while (1) {
		kinect.UpdateFrame();

		colorimg = kinect.GetColorImg();
		depthimg = kinect.GetDepthImg();

		cv::imshow("ColorImage", colorimg);
		cv::imshow("DepthImage", depthimg);

		int keyInput = cv::waitKey(10);
		if (keyInput != -1) {
			switch (keyInput) {
			case 'q':
				quit = true;
				break;
			default:
				break;
			}
		}

		if (quit) {
			break;
		}
	}

    return 0;
}

