#include "FaceDetection.hpp"


FaceDetection::FaceDetection() : m_drawColor(255, 255, 255), m_faceCascadeDetector("./data/haarcascades/haarcascade_frontalface_alt.xml")
{
	// Open the default camera (device ID 0)
	int deviceID = 0;
	int apiID = cv::CAP_ANY; // Auto-detect the backend API

	if (!m_capture.open(deviceID, apiID)) {
		throw std::runtime_error("Could not open camera device 0 !");
	}
}

FaceDetection::~FaceDetection()
{
	// release VideoCapture
	m_capture.release();
}

std::vector<cv::Rect> FaceDetection::detectFaces(cv::Mat const& image)
{
	// vector storing all area where faces are detected
	std::vector<cv::Rect> faceObjects;
	if (image.empty())
	{
		throw std::invalid_argument("Empty image given !");
	}
	else {
		// convert frame to grayscale for better result in face detection
		cv::Mat grayscaleFrame(image);
		cvtColor(image, grayscaleFrame, cv::COLOR_BGR2GRAY);

		try {
			// use cascade classifier to detect face
			m_faceCascadeDetector.detectMultiScale(grayscaleFrame, faceObjects);
		}
		catch (const cv::Exception& e) {
			std::cerr << "OpenCV exception caught: " << e.what() << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Standard exception caught: " << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "Unknown exception caught!" << std::endl;
		}

	}

	return faceObjects;
}

cv::Mat FaceDetection::getCurrentFrame()
{
	// store resulting image to display
	cv::Mat frame;
	// capture frame from camera
	m_capture.read(frame);

	return frame;
}
