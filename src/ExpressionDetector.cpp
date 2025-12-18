#include "ExpressionDetector.hpp"

ExpressionDetector::ExpressionDetector(QWidget *parent) : QMainWindow(parent), m_faceDetect(), m_mode(DetectorMode::FaceDetect)
{
    setWindowTitle("Expression Detector");

    // create alias for UI images path
    QDir::addSearchPath("images", "./style/images");

    // set style sheet to define style for the application
    QString styleSheetPath("./style/ExpressionDetector.stylesheet");
    QFile styleFile(styleSheetPath);
    bool stylesheetOpen = styleFile.open(QFile::ReadOnly);
    if (stylesheetOpen) {
        QString stylesheet = styleFile.readAll();
        setStyleSheet(stylesheet);
    }
    else {
        qWarning() << "Could not open stylesheet file located at " << styleSheetPath << " !";
    }
    
    // status bar to display information about the application (number of faces detected)
    infoBar = this->statusBar();
    infoBarLbl = new QLabel(this);
    infoBar->addWidget(infoBarLbl);

    // viewer displaying camera stream with detection features
    m_frameViewer = new QLabel(this);

    m_mainWidget = new QWidget(this);
    // store respectively main layout of the application and the one containing radio buttons to change application mode
    m_mainLayout = new QHBoxLayout(m_mainWidget);
    m_detectionOptionsLayout = new QVBoxLayout(m_mainWidget);

    // group containing the different radio button to select detection modes
    m_detectionOptionsGrp = new QGroupBox("Detection modes", this);
    m_detectionOptionsGrp->setMaximumHeight(DETECTION_OPTIONS_GRP_MAX_HEIGHT);

    // radio button to set mode of the application on "no detection", basically only displaying camera stream
    m_noDetectionOptionBtn = new QRadioButton("No detection", m_mainWidget);
    connect(m_noDetectionOptionBtn, &QRadioButton::toggled, this, [this](bool checked) {modeChanged(m_noDetectionOptionBtn, checked); });

    //  radio button to set mode of the application on face detection mode
    m_faceDetectionOptionBtn = new QRadioButton("Face detection", m_mainWidget);
    m_faceDetectionOptionBtn->setChecked(true);
    connect(m_faceDetectionOptionBtn, &QRadioButton::toggled, this, [this](bool checked) {modeChanged(m_faceDetectionOptionBtn, checked); });

    //  radio button to set mode of the application on expression detection mode
    m_expDetectionOptionBtn = new QRadioButton("Expression detection", m_mainWidget);
    m_expDetectionOptionBtn->setDisabled(true);
    connect(m_expDetectionOptionBtn, &QRadioButton::toggled, this, [this](bool checked) {modeChanged(m_expDetectionOptionBtn, checked); });

    // add radio button to layout and set group box to contain this layout
    m_detectionOptionsLayout->addWidget(m_noDetectionOptionBtn);
    m_detectionOptionsLayout->addWidget(m_faceDetectionOptionBtn);
    m_detectionOptionsLayout->addWidget(m_expDetectionOptionBtn);
    m_detectionOptionsGrp->setLayout(m_detectionOptionsLayout);

    m_mainLayout->addWidget(m_detectionOptionsGrp, 0, Qt::AlignTop);
    m_mainLayout->addWidget(m_frameViewer);

    setCentralWidget(m_mainWidget);

    // timer to refresh viewer
    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &ExpressionDetector::updateFrame);
    m_refreshTimer->start(REFRESH_INTERVAL);
}

ExpressionDetector::~ExpressionDetector() = default;

void ExpressionDetector::updateFrame()
{
    // get current frame of the camera
    cv::Mat capture = m_faceDetect.getCurrentFrame();
    // convert it for qt processes
    QImage frame = ImageManager::convertOpencvImageToQImage(capture);
    
    switch (m_mode) {
        case DetectorMode::FaceDetect:
        {
            // detect faces in image
            std::vector<cv::Rect> faceObjects = m_faceDetect.detectFaces(capture);

            // draw rectangle to show faces detected
            for (const auto& face : faceObjects) {
                drawRectangle(frame, face.x, face.y, face.width, face.height);
            }

            // display number of faces detected in status bar
            infoBarLbl->setText(QString("Faces detected : %1").arg(faceObjects.size()));
            break;
        }
        default:
            // no process to do, only display image of the camera and reset status bar information
            infoBarLbl->setText("");
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
    return QSize(640, 480);
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

