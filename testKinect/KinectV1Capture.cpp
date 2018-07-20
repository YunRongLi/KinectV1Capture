#include "KinectV1Capture.h"

KinectV1Capture::KinectV1Capture() {
	colorImg.create(color_height, color_width, CV_8UC3);
	depthImg.create(depth_height, depth_width, CV_8UC1);

	colorEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	depthEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	colorStream = NULL;
	depthStream = NULL;
}

KinectV1Capture::~KinectV1Capture() {
	colorImg.release();
	depthImg.release();
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

	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH, NUI_IMAGE_RESOLUTION_320x240, NULL, 2, depthEvent, &depthStream);
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

	pTexture->UnlockRect(0);
	NuiImageStreamReleaseFrame(colorStream, colorFrame);
}

void KinectV1Capture::UpdateDepthFrame() {
	const NUI_IMAGE_FRAME *depthFrame = NULL;

	NuiImageStreamGetNextFrame(depthStream, 0, &depthFrame);
	INuiFrameTexture *pTexture = depthFrame->pFrameTexture;

	NUI_LOCKED_RECT LockedRect;
	pTexture->LockRect(0, &LockedRect, NULL, 0);


	uchar* mat_ptr = depthImg.data;

	if (LockedRect.Pitch != 0) {
		for (int i = 0; i < depthImg.rows; i++) {
			uchar *ptr = depthImg.ptr<uchar>(i);
			uchar *pBuffer = (uchar*)(LockedRect.pBits) + i * LockedRect.Pitch;
			USHORT *pBufferRun = (USHORT*)pBuffer;

			for (int j = 0; j < depthImg.cols; j++) {
				//ptr[j] = 255 - (uchar)(256 * pBufferRun[j] / 4095);
				//t_buffer[i][j] = pBufferRun[j];
				mat_ptr[(i*depthImg.cols)+j] = pBufferRun[j] / 206;
				if (pBufferRun[j] < buffer_min && pBufferRun[j] !=0)
					buffer_min = pBufferRun[j];//6408
				if(pBufferRun[j] > buffer_max)
					buffer_max = pBufferRun[j];//31800
			}
		}
	}
	else {
		std::cout << "Get Depth Image failed" << std::endl;
	}

	pTexture->UnlockRect(0);
	NuiImageStreamReleaseFrame(depthStream, depthFrame);
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