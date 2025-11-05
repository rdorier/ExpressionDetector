#include "FaceDetection.hpp"

using namespace std;
using namespace cv;

FaceDetection::FaceDetection() : m_drawColor(255, 0, 0)
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
	Mat frame;

	// store ASCII code of key pressed by user
	int keyPressed = -1;

	// build cascade classifier to detect faces using OpenCV provided xml data
	CascadeClassifier faceCascadeDetector("data/haarcascades/haarcascade_frontalface_alt.xml");


	// capture loop
	while (true) {
		// capture frame from camera
		bool result = m_capture.read(frame);
		// check if resulting image is not empty and end capturing loop if so
		if (result == false || frame.empty()) {
			break;
		}

		// convert frame to grayscale for better result in face detection
		Mat grayscaleFrame(frame);
		cvtColor(frame, grayscaleFrame, COLOR_BGR2GRAY);

		// use cascade classifier to detect face
		vector<Rect> faceObjects;
		vector<Rect>::iterator faceIt;
		faceCascadeDetector.detectMultiScale(grayscaleFrame, faceObjects);

		// draw rectangle to show faces detected
		for (faceIt = faceObjects.begin(); faceIt != faceObjects.end(); ++faceIt) {
			rectangle(frame, *faceIt, m_drawColor);
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
