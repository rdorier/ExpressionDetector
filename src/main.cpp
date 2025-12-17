#include <QtWidgets/QApplication>
#include <QDebug>
#include "ExpressionDetector.hpp"
#include "FaceDetection.hpp"


int main(int argc, char *argv[])
{
    /*
    * Entry point for ExpressionDetector application.
    * Initialize the QApplication et launch the window
    */
    try {
        QApplication app(argc, argv);
        ExpressionDetector w;

        w.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        qCritical() << e.what();
        return EXIT_FAILURE;
    }
}
