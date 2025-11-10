#include "ExpressionDetector.hpp"

ExpressionDetector::ExpressionDetector(QWidget *parent) : QMainWindow(parent), m_faceDetect()
{
    setWindowTitle("Expression Detector");

    m_frameViewer = new QLabel(this);

    m_mainWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(m_mainWidget); // TODO : remove pointer ?
    
    QVBoxLayout* detectionOptionsLayout = new QVBoxLayout(m_mainWidget);

    QRadioButton* noDetectionOptionBtn = new QRadioButton("No detection", m_mainWidget);
    QRadioButton* faceDetectionOptionBtn = new QRadioButton("Face detection", m_mainWidget);
    faceDetectionOptionBtn->setChecked(true);
    QRadioButton* expDetectionOptionBtn = new QRadioButton("Expression detection", m_mainWidget);
    expDetectionOptionBtn->setDisabled(true);

    detectionOptionsLayout->addWidget(noDetectionOptionBtn);
    detectionOptionsLayout->addWidget(faceDetectionOptionBtn);
    detectionOptionsLayout->addWidget(expDetectionOptionBtn);
    
    layout->addLayout(detectionOptionsLayout);
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

    DetectorMode mode = DetectorMode::FaceDetect;
    
    switch (mode) {
        case DetectorMode::FaceDetect:
        {
            std::vector<cv::Rect> faceObjects = m_faceDetect.detectFaces(capture);

            // draw rectangle to show faces detected
            std::vector<cv::Rect>::iterator faceIt;
            for (faceIt = faceObjects.begin(); faceIt != faceObjects.end(); ++faceIt) {
                drawRectangle(frame, faceIt->x, faceIt->y, faceIt->width, faceIt->height);
            }
            break;
        }
        default:
            break;
    }
    
    if (!frame.isNull()) {
        m_frameViewer->setPixmap(QPixmap::fromImage(frame));
    }
    
}


QSize ExpressionDetector::sizeHint() const
{
    return QSize(100, 110);
}

void ExpressionDetector::drawRectangle(QImage& image, int x, int y, int width, int height)
{   
    // draw on image
    QPainter painter(&image);
    painter.setPen(Qt::white); // line color
    painter.setBrush(QBrush(Qt::transparent)); // fill color
    // draw rectangle
    painter.drawRect(x, y, width, height);
}

