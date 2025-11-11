#include "ExpressionDetector.hpp"

ExpressionDetector::ExpressionDetector(QWidget *parent) : QMainWindow(parent), m_faceDetect(), m_mode(DetectorMode::FaceDetect)
{
    setWindowTitle("Expression Detector");
    
    // set style sheet to define style for the application
    QFile styleFile("style/QTDark.stylesheet");
    bool stylesheetOpen = styleFile.open(QFile::ReadOnly);
    QString stylesheet = styleFile.readAll();
    setStyleSheet(stylesheet);

    m_frameViewer = new QLabel(this);

    m_mainWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(m_mainWidget); // TODO : remove pointer ?
    
    QVBoxLayout* detectionOptionsLayout = new QVBoxLayout(m_mainWidget);

    // radio button to set mode of the application on "no detection", basically only displaying camera stream
    m_noDetectionOptionBtn = new QRadioButton("No detection", m_mainWidget);
    connect(m_noDetectionOptionBtn, &QRadioButton::toggled, this, [=](bool checked) {this->modeChanged(m_noDetectionOptionBtn, checked); });

    //  radio button to set mode of the application on face detection mode
    m_faceDetectionOptionBtn = new QRadioButton("Face detection", m_mainWidget);
    m_faceDetectionOptionBtn->setChecked(true);
    connect(m_faceDetectionOptionBtn, &QRadioButton::toggled, this, [=](bool checked) {this->modeChanged(m_faceDetectionOptionBtn, checked); });

    //  radio button to set mode of the application on expression detection mode
    m_expDetectionOptionBtn = new QRadioButton("Expression detection", m_mainWidget);
    m_expDetectionOptionBtn->setDisabled(true);
    connect(m_expDetectionOptionBtn, &QRadioButton::toggled, this, [=](bool checked) {this->modeChanged(m_expDetectionOptionBtn, checked); });

    detectionOptionsLayout->addWidget(m_noDetectionOptionBtn);
    detectionOptionsLayout->addWidget(m_faceDetectionOptionBtn);
    detectionOptionsLayout->addWidget(m_expDetectionOptionBtn);
    
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
    delete m_noDetectionOptionBtn;
    delete m_faceDetectionOptionBtn;
    delete m_expDetectionOptionBtn;
    delete m_mainWidget;
}

void ExpressionDetector::updateFrame()
{
    cv::Mat capture = m_faceDetect.getCurrentFrame();
    QImage frame = ImageManager::convertOpencvImageToQImage(capture);
    
    switch (m_mode) {
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

void ExpressionDetector::modeChanged(QRadioButton* button, bool checked)
{
    if (checked) {
        if (button == m_noDetectionOptionBtn) {
            m_mode = DetectorMode::NoDetect;
        }
        else if (button == m_faceDetectionOptionBtn) {
            m_mode = DetectorMode::FaceDetect;
        }
        else if (button == m_expDetectionOptionBtn) {
            m_mode = DetectorMode::ExpressionDetect;
        }
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

