#include "ExpressionDetector.hpp"
#include <QtWidgets/QPushButton>
ExpressionDetector::ExpressionDetector(QWidget *parent) : QMainWindow(parent), m_faceDetect()
{
    setWindowTitle("Expression Detector");

    m_frameViewer = new QLabel(this);

    m_mainWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(m_mainWidget);

    layout->addWidget(new QLabel("Bonjour depuis le widget central !"));
    layout->addWidget(m_frameViewer);

    setCentralWidget(m_mainWidget);

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &ExpressionDetector::updateFrame);


    m_refreshTimer->start(20);
}

ExpressionDetector::~ExpressionDetector()
{
    delete m_refreshTimer;
}

void ExpressionDetector::updateFrame()
{
    cv::Mat dest = m_faceDetect.getCurrentFrame();
    
    QImage image1 = QImage((uchar*)dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    
    if (!image1.isNull()) {
        m_frameViewer->setPixmap(QPixmap::fromImage(image1));
    }
    
}


QSize ExpressionDetector::sizeHint() const
{
    return QSize(100, 110);
}
