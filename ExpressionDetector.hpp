#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <vector>
#include "ui_ExpressionDetector.h"
#include "FaceDetection.hpp"
#include "ImageManager.hpp"

// enum representing the different modes of the expression detector
enum DetectorMode { NoDetect = 0, FaceDetect = 1, ExpressionDetect = 2 };

class ExpressionDetector : public QMainWindow
{
    Q_OBJECT

public:
    ExpressionDetector(QWidget *parent = nullptr);
    ~ExpressionDetector();

    void updateFrame();
    void modeChanged(QRadioButton* button, bool checked);
    QSize sizeHint() const;

    void drawRectangle(QImage& image, int x, int y, int width, int height);

private:
    DetectorMode m_mode;
    Ui::ExpressionDetectorClass ui;
    FaceDetection m_faceDetect;
    QTimer* m_refreshTimer;

    QWidget* m_mainWidget;
    QLabel* m_frameViewer;

    // radio buttons to set one of the three modes of the application
    QRadioButton* m_noDetectionOptionBtn;
    QRadioButton* m_faceDetectionOptionBtn;
    QRadioButton* m_expDetectionOptionBtn;
};

