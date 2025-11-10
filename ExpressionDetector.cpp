#include "ExpressionDetector.hpp"

ExpressionDetector::ExpressionDetector(QWidget *parent) : QMainWindow(parent), m_faceDetect()
{
    setWindowTitle("Expression Detector");

    m_frameViewer = new QLabel(this);

    m_mainWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(m_mainWidget);
    layout->addWidget(m_frameViewer);

    setCentralWidget(m_mainWidget);

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &ExpressionDetector::updateFrame);


    m_refreshTimer->start(20);
}

ExpressionDetector::~ExpressionDetector()
{
    // delete pointers to avoid memory leak
    delete m_refreshTimer;
    delete m_frameViewer;
    delete m_mainWidget;
}

void ExpressionDetector::updateFrame()
{
    cv::Mat capture = m_faceDetect.getCurrentFrame();
    QImage frame = ImageManager::convertOpencvImageToQImage(capture);
    
    if (!frame.isNull()) {
        m_frameViewer->setPixmap(QPixmap::fromImage(frame));
    }
    
}


QSize ExpressionDetector::sizeHint() const
{
    return QSize(100, 110);
}
