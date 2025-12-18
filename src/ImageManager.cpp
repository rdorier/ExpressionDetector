#include "ImageManager.hpp"

QImage ImageManager::convertOpencvImageToQImage(cv::Mat const& imageToConvert)
{
    cv::Mat resultImg;
    // opencv images are written in BGR colorspace, but Qt handle RGB colorspace, so we convert input image into the RGB one
    cv::cvtColor(imageToConvert, resultImg, cv::COLOR_BGR2RGB);
    // convert image from OpenCV into a QImage
    QImage img = QImage((uchar*)resultImg.data, resultImg.cols, resultImg.rows, resultImg.step, QImage::Format_RGB888);
    // make a deep copy so QImage do not depend on local variable resultImg
    return img.copy();
}
