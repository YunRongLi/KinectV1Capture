#pragma once

#include <Windows.h>
#include <iostream>

#include <NuiApi.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#define color_height 480
#define color_width 640

#define depth_height 480
#define depth_width 640

class KinectV1Capture {
private:
	cv::Mat colorImg, depthImg, depthImg3H;

	HANDLE colorEvent, depthEvent, colorStream, depthStream;

	void UpdateColorFrame();
	void UpdateDepthFrame();
	void DepthImg1ChTo3CH();

	int depth_max = 31800;
	int depth_min = 6408;

	public:
	KinectV1Capture();
	~KinectV1Capture();

	bool Init();
	void UpdateFrame();
	void Close();

	cv::Mat GetColorImg();
	cv::Mat GetDepthImg();
	cv::Mat GetDepth3HImg();

	int GetColorImgType();
	int GetDepthImgType();

	cv::Size GetColorImgSize();
	cv::Size GetDepthImgSize();

	void SetMaxDepth(int);
	void SetMinDepth(int);
};
