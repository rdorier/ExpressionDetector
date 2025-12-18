#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

class FaceDetection
{
	public:
		FaceDetection();
		~FaceDetection();

		// forbid copy operator as the class manage a camera resource
		FaceDetection(const FaceDetection&) = delete;
		FaceDetection operator=(const FaceDetection&) = delete;
		
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

