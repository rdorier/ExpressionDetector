#include "ImageManager.hpp"

QImage ImageManager::convertOpencvImageToQImage(cv::Mat const& imageToConvert)
{
    cv::Mat resultImg(imageToConvert);
    // opencv images are written in BGR colorspace, but Qt handle RGB colorspace, so we convert input image into the RGB one
    cv::cvtColor(imageToConvert, resultImg, cv::COLOR_BGR2RGB);

    return QImage((uchar*)resultImg.data, resultImg.cols, resultImg.rows, resultImg.step, QImage::Format_RGB888);
}
