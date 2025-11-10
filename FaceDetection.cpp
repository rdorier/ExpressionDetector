#include "FaceDetection.hpp"

using namespace std;
using namespace cv;

FaceDetection::FaceDetection() : m_drawColor(255, 255, 255), m_faceCascadeDetector("data/haarcascades/haarcascade_frontalface_alt.xml")
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
	/*
	Test function to capture webcam stream, detect faces and draw rectangles around.
	Images are simply displayed with opencv imshow method.
	*/

	// store resulting image to display
	Mat frame;

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
			vector<Rect> faceObjects = detectFaces(frame);
			// draw rectangle to show faces detected
			vector<Rect>::iterator faceIt;
			for (faceIt = faceObjects.begin(); faceIt != faceObjects.end(); ++faceIt) {
				rectangle(frame, *faceIt, m_drawColor);
			}
		}
		catch (Exception const& e) {
			cerr << "ERREUR : " << e.what() << endl;
		}

		// display frame
		imshow("Expression Detection", frame);

		// check if user has pressed escap key to stop capturing loop
		keyPressed = waitKey(30);
		if (keyPressed == 27) {
			break;
		}
	}
}

std::vector<cv::Rect> FaceDetection::detectFaces(Mat const& image)
{
	// vector storing all area where faces are detected
	vector<Rect> faceObjects;
	if (image.empty())
	{
		throw invalid_argument("Empty image given !");
	}
	else {
		// convert frame to grayscale for better result in face detection
		Mat grayscaleFrame(image);
		cvtColor(image, grayscaleFrame, COLOR_BGR2GRAY);

		// use cascade classifier to detect face
		m_faceCascadeDetector.detectMultiScale(grayscaleFrame, faceObjects);
	}

	return faceObjects;
}

cv::Mat FaceDetection::getCurrentFrame()
{
	// store resulting image to display
	Mat frame;
	// capture frame from camera
	m_capture.read(frame);

	return frame;
}
