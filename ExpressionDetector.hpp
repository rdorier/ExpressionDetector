#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include "ui_ExpressionDetector.h"
#include "FaceDetection.hpp"
#include "ImageManager.hpp"

class ExpressionDetector : public QMainWindow
{
    Q_OBJECT

public:
    ExpressionDetector(QWidget *parent = nullptr);
    ~ExpressionDetector();

    void updateFrame();
    QSize sizeHint() const;

private:
    Ui::ExpressionDetectorClass ui;
    FaceDetection m_faceDetect;
    QTimer* m_refreshTimer;

    QWidget* m_mainWidget;
    QLabel* m_frameViewer;
};

