#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui//highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

class FaceDetection
{
	public:
		FaceDetection();
		~FaceDetection();

		void faceDetectionLoop();
	private:
		const cv::Scalar m_drawColor;
		cv::VideoCapture m_capture;
};

