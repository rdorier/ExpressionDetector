#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QtWidgets/QWidget>

class ImageManager
{
	/**************************************************/
	/*Class used to do different treatments on images */
	/*It basically make the link between Qt and opencv*/
	/**************************************************/

	public:
		static QImage convertOpencvImageToQImage(cv::Mat const& imageToConvert);

	
};

