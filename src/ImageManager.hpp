#pragma once

#include <opencv2/core/mat.hpp>
#include <QImage>

class ImageManager
{
	/**************************************************/
	/*Class used to do different treatments on images */
	/*It basically make the link between Qt and opencv*/
	/**************************************************/

	public:
		/*
		* Convert image from OpenCV to a QImage.
		* @param imageToConvert : the OpenCV image to convert, a cv::Mat.
		* @return QImage : the resulting Qt Image corresponding to opencv image, a QImage.
		*/
		static QImage convertOpencvImageToQImage(cv::Mat const& imageToConvert);

	
};

