#include "FaceDetection.hpp"


FaceDetection::FaceDetection() : m_drawColor(255, 255, 255), m_faceCascadeDetector("./data/haarcascades/haarcascade_frontalface_alt.xml")
{
	// Open the default camera (device ID 0)
	int deviceID = 0;
	int apiID = cv::CAP_ANY; // Auto-detect the backend API

	m_capture.open(deviceID, apiID);
}

FaceDetection::~FaceDetection()
{
	// clear memory
	m_capture.release();
	cv::destroyAllWindows();
}

void FaceDetection::faceDetectionLoop()
{
	// store resulting image to display
	cv::Mat frame;

	// store ASCII code of key pressed by user
	int keyPressed = -1;


	// capture loop
	while (true) {
		// capture frame from camera
		bool result = m_capture.read(frame);
		// check if resulting image is not empty and end capturing loop if so
		if (result == false || frame.empty()) {
			break;
		}

		try {
			// use cascade classifier to detect face
			std::vector<cv::Rect> faceObjects = detectFaces(frame);
			// draw rectangle to show faces detected
			std::vector<cv::Rect>::iterator faceIt;
			for (faceIt = faceObjects.begin(); faceIt != faceObjects.end(); ++faceIt) {
				rectangle(frame, *faceIt, m_drawColor);
			}
		}
		catch (cv::Exception const& e) {
			std::cerr << "ERREUR : " << e.what() << std::endl;
		}

		// display frame
		imshow("Expression Detection", frame);

		// check if user has pressed escap key to stop capturing loop
		keyPressed = cv::waitKey(30);
		if (keyPressed == 27) {
			break;
		}
	}
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
