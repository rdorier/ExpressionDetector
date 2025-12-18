#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QGroupBox>
#include <QDebug>
#include <QStatusBar>
#include <opencv2/core/core.hpp>
#include <vector>
#include "FaceDetection.hpp"
#include "ImageManager.hpp"

// enum representing the different modes of the expression detector
enum DetectorMode {
    NoDetect = 0, // no detection : the interface only display what camera sees
    FaceDetect = 1, // face detection : the interface draw a figure around areas where faces are detected
    ExpressionDetect = 2 // expression detection : the interface draw a figure around areas where faces are detected and display the name of the emotion
};

// refresh interval to use to redraw frame
constexpr int REFRESH_INTERVAL = 20;
constexpr int DETECTION_OPTIONS_GRP_MAX_HEIGHT = 120;


// ExpressionDetector: main window of the application.
// Displays camera stream and handles detection modes. Also display information in the status bar.
class ExpressionDetector : public QMainWindow
{
    Q_OBJECT

public:
    ExpressionDetector(QWidget *parent = nullptr);
    ~ExpressionDetector();

    // forbid copy of ExpressionDetector but allow 
    ExpressionDetector(const ExpressionDetector&) = delete;
    ExpressionDetector& operator=(const ExpressionDetector&) = delete;
    // allow moving object using std::move
    ExpressionDetector(ExpressionDetector&&) = default;
    ExpressionDetector& operator=(ExpressionDetector&&) = default;

    // function connected to a timer to refresh frame display by interface in m_frameViewer
    void updateFrame();
    /*
     * Change mode of the application (DetectorMode)
     * This function is connected to radio buttons for user to choose mode with interface.
     * @param button, a pointer to the QRadioButton that launch the function.
     * @param checked, a boolean to tell if button is checked or not.
     */
    void modeChanged(QRadioButton* button, bool checked);
    // return recommended size for the application
    QSize sizeHint() const;
    /*
    * Draw rectangle on a given image.
    * @param image: the image to draw rectangle on, a QImage.
    * @param x : the x-coordinates of the upper left corner point of the rectangle to draw, an integer.
    * @param y : the y-coordinates of the upper left corner point of the rectangle to draw, an integer.
    * @param width, the width of the rectangle to draw, an integer.
    * @param height, the height of the rectangle to draw, an integer.
    */
    void drawRectangle(QImage& image, const int x, const int y, const int width, const int height);

private:
    // mode the application is currently in
    DetectorMode m_mode;
    // face detection engine used to detect faces and expressions
    FaceDetection m_faceDetect;
    // timer to refresh viewer
    QTimer* m_refreshTimer;

    // members storing interface elements
    QWidget* m_mainWidget;
    QLabel* m_frameViewer; // viewer displaying camera stream with detection features
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_detectionOptionsLayout;

    // a status bar to display information about the application (number of faces detected)
    QStatusBar* infoBar;
    QLabel* infoBarLbl; // label displaying informations in status bar

    // group containing the different radio button to select detection modes
    QGroupBox* m_detectionOptionsGrp;
    // radio buttons to set one of the three modes of the application
    QRadioButton* m_noDetectionOptionBtn;
    QRadioButton* m_faceDetectionOptionBtn;
    QRadioButton* m_expDetectionOptionBtn;
};

