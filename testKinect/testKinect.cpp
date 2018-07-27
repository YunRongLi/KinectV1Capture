// testKinect.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "KinectV1Capture.h"


int main()
{
	KinectV1Capture kinect;
	
	if (kinect.Init() != S_OK) {
		system("pause");
		return 0;
	}
	
	bool quit = false;
	std::vector<int> quality;
	//std::vector<std::vector<cv::Point>> contour_point;
	int count = 0;
	//::Mat colorimg;
	cv::Mat depthimg;
	cv::namedWindow("DepthImage", CV_WINDOW_AUTOSIZE);
	
	//colorimg.create(kinect.GetColorImgSize(), kinect.GetColorImgType());
	//depthimg.create(kinect.GetDepthImgSize(), kinect.GetDepthImgType());

	while (1) {
		kinect.UpdateFrame();

		kinect.GetDepthImg().copyTo(depthimg);
		//kinect.GetDepth3HImg().copyTo(depthimg);
		//cv::threshold(depthimg, binary, 100.0, 255.0, cv::THRESH_BINARY);	

		/*cv::findContours()*/

		cv::imshow("DepthImage", depthimg);
		//cv::imshow("BinaryImage", binary);

		int keyInput = cv::waitKey(10);
		if (keyInput != -1) {
			switch (keyInput) {
			case 'q':
				quit = true;
				break;
			case 's':
				quality.push_back(CV_IMWRITE_PNG_COMPRESSION);
				quality.push_back(0);
				cv::imwrite("Depth_" + std::to_string(count) + ".png", depthimg, quality);
				count++;
				//cv::imwrite("Binary.png", binary, quality);
				break;
			default:
				break;
			}
		}

		if (quit) {
			break;
		}
	}

	kinect.Close();

    return 0;
}

