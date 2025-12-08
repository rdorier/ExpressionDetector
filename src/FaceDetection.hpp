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

		/*
		Test function to capture webcam stream, detect faces and draw rectangles around.
		Images are simply displayed with opencv imshow method.
		*/
		void faceDetectionLoop();
		/*
		Use Haar cascade algorithm to detect faces inside an image.
		@param image, the image to detect faces in it, a cv::Mat.
		@return a vector of rectangles representing area where faces have been detected, a vector of cv::Rect objects.
		*/
		std::vector<cv::Rect> detectFaces(cv::Mat const& image);
		/*
		Get the current frame seen by active camera.
		@return the image currently seen by camera as a cv::Mat object.
		*/
		cv::Mat getCurrentFrame();
	private:
		// color to use when drawing figures inside opencv windows
		const cv::Scalar m_drawColor;
		// capturing stream for the camera
		cv::VideoCapture m_capture;
		// cascade classifier used to detect faces
		cv::CascadeClassifier m_faceCascadeDetector;
};

