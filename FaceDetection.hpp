#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
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
		std::vector<cv::Rect> detectFaces(cv::Mat const& image);
	private:
		const cv::Scalar m_drawColor;
		cv::VideoCapture m_capture;
		cv::CascadeClassifier m_faceCascadeDetector;
};

