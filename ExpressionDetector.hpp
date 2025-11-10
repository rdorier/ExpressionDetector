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


enum DetectorMode { NoDetect = 0, FaceDetect = 1, ExpressionDetect = 2 };

class ExpressionDetector : public QMainWindow
{
    Q_OBJECT

public:
    ExpressionDetector(QWidget *parent = nullptr);
    ~ExpressionDetector();

    void updateFrame();
    QSize sizeHint() const;

    void drawRectangle(QImage& image, int x, int y, int width, int height);

private:
    Ui::ExpressionDetectorClass ui;
    FaceDetection m_faceDetect;
    QTimer* m_refreshTimer;

    QWidget* m_mainWidget;
    QLabel* m_frameViewer;
};

