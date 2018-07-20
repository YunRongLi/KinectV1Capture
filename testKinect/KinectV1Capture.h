#pragma once

#include <Windows.h>
#include <iostream>

#include <NuiApi.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#define colorResolution640x480 NUI_IMAGE_RESOLUTION_640x480
#define depthResolution320x240 NUI_IMAGE_RESOLUTION_320x240

#ifdef colorResolution640x480
#define color_height 480
#define color_width 640
#endif 

#ifdef depthResolution320x240
#define depth_height 240
#define depth_width 320
#endif


class KinectV1Capture {
private:
	cv::Mat colorImg, depthImg;

	HANDLE colorEvent, depthEvent, colorStream, depthStream;

	void UpdateColorFrame();
	void UpdateDepthFrame();



public:
	KinectV1Capture();
	~KinectV1Capture();

	bool Init();
	void UpdateFrame();

	cv::Mat GetColorImg();
	cv::Mat GetDepthImg();

	int GetColorImgType();
	int GetDepthImgType();
	
	cv::Size GetColorImgSize();
	cv::Size GetDepthImgSize();

	int buffer_max = 0;
	int buffer_min = 999999;
};