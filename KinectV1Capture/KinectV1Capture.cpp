#include "KinectV1Capture.h"


KinectV1Capture::KinectV1Capture() {
	colorImg.create(color_height, color_width, CV_8UC3);
	depthImg.create(depth_height, depth_width, CV_8UC1);
	depthImg3H.create(depth_height, depth_width, CV_8UC3);

	colorEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	depthEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	colorStream = NULL;
	depthStream = NULL;
}

KinectV1Capture::~KinectV1Capture() {
	colorImg.release();
	depthImg.release();
	depthImg.release();

	NuiShutdown();
}

bool KinectV1Capture::Init() {
	HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH);

	if (hr != S_OK) {
		std::cout << "NuiInit failed" << std::endl;
		return hr;
	}

	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, NULL, 4, colorEvent, &colorStream);
	if (hr != S_OK) {
		std::cout << "Open Color Stream failed" << std::endl;
		NuiShutdown();
		return hr;
	}

	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH, NUI_IMAGE_RESOLUTION_640x480, NULL, 2, depthEvent, &depthStream);
	if (hr != S_OK) {
		std::cout << "Open depth Stream failed" << std::endl;
		NuiShutdown();
		return hr;
	}
}

void KinectV1Capture::UpdateColorFrame() {
	const NUI_IMAGE_FRAME *colorFrame = NULL;
	
	NuiImageStreamGetNextFrame(colorStream, 0, &colorFrame);
	INuiFrameTexture *pTexture = colorFrame->pFrameTexture;

	NUI_LOCKED_RECT LockedRect;
	pTexture->LockRect(0, &LockedRect, NULL, 0);

	if (LockedRect.Pitch != 0) {
		for (int i = 0; i < colorImg.rows; i++) {
			uchar *ptr = colorImg.ptr<uchar>(i);

			uchar *pBuffer = (uchar*)(LockedRect.pBits) + i * LockedRect.Pitch;
			for (int j = 0; j < colorImg.cols; j++) {
				ptr[3 * j] = pBuffer[4 * j];
				ptr[3 * j + 1] = pBuffer[4 * j + 1];
				ptr[3 * j + 2] = pBuffer[4 * j + 2];
			}
		}
	}
	else {
		std::cout << "Get Color Image failed" << std::endl;
	}

	//Filps Img
	cv::Mat nColorImg;
	colorImg.copyTo(nColorImg);
	cv::flip(nColorImg, colorImg, 1);
	nColorImg.release();

	pTexture->UnlockRect(0);
	NuiImageStreamReleaseFrame(colorStream, colorFrame);
}

void KinectV1Capture::UpdateDepthFrame() {
	const NUI_IMAGE_FRAME *depthFrame = NULL;

	NuiImageStreamGetNextFrame(depthStream, 0, &depthFrame);
	INuiFrameTexture *pTexture = depthFrame->pFrameTexture;

	NUI_LOCKED_RECT LockedRect;
	pTexture->LockRect(0, &LockedRect, NULL, 0);

	if (LockedRect.Pitch != 0) {

		for (int i = 0; i < depthImg.rows; i++) {
			uchar *ptr = depthImg.data;
			uchar *pBuffer = (uchar*)(LockedRect.pBits) + i * LockedRect.Pitch;
			USHORT *pBufferRun = (USHORT*)pBuffer;

			for (int j = 0; j < depthImg.cols; j++) {
				if (pBufferRun[j] < depth_min && pBufferRun[j] != 0)
					ptr[(i*depthImg.cols) + j] = 0;//6408
				else if (pBufferRun[j] > depth_max) {
					ptr[(i*depthImg.cols) + j] = 0;//31800
				}
				else {
					ptr[(i*depthImg.cols) + j] = 256 * pBufferRun[j] / 4095;
				}
			};
		}
	}
	else {
		std::cout << "Get Depth Image failed" << std::endl;
	}

	cv::flip(depthImg, depthImg, 1);

	DepthImg1ChTo3CH();

	pTexture->UnlockRect(0);
	NuiImageStreamReleaseFrame(depthStream, depthFrame);
}

void KinectV1Capture::DepthImg1ChTo3CH() {
	///cv::Mat depth8bit;
	cv::Mat depht3HMask = cv::Mat(depthImg.rows, depthImg.cols, CV_8UC3, cv::Scalar(0, 255, 255));
	//depthImg.convertTo(depth8bit, CV_8U, 255.0 / 10000);
	cv::cvtColor(depthImg, depthImg3H, CV_GRAY2BGR);
	cv::bitwise_and(depthImg3H, depht3HMask, depthImg3H);
}

void KinectV1Capture::UpdateFrame() {
	if (WaitForSingleObject(colorEvent, 0) == 0) {
		UpdateColorFrame();
	}

	if (WaitForSingleObject(depthEvent, 0) == 0) {
		UpdateDepthFrame();
	}
}

cv::Mat KinectV1Capture::GetColorImg() {
	return colorImg;
}

cv::Mat KinectV1Capture::GetDepthImg() {
	return depthImg;
}

cv::Mat KinectV1Capture::GetDepth3HImg() {
	return depthImg3H;
}

cv::Size KinectV1Capture::GetColorImgSize() {
	return colorImg.size();
}

cv::Size KinectV1Capture::GetDepthImgSize() {
	return depthImg.size();
}

int KinectV1Capture::GetColorImgType() {
	return colorImg.type();
}

int KinectV1Capture::GetDepthImgType() {
	return depthImg.type();
}

void KinectV1Capture::SetMinDepth(int min) {
	depth_min = 25392 * min / 1000 + 6408;
	
}

void KinectV1Capture::SetMaxDepth(int max) {
	depth_max = 25392 * max / 1000 + 6408;
}

void KinectV1Capture::Close() {
	colorImg.release();
	depthImg.release();
	depthImg3H.release();

	NuiShutdown();
}
