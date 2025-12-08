#include <QtWidgets/QApplication>
#include "ExpressionDetector.hpp"
#include "FaceDetection.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ExpressionDetector w;

    w.show();
    
    return app.exec();
}
