#include "mainwindow.h"

#include <QApplication>
#include <GL/glut.h>
#include <QLabel>
#include "./algoritmi_studentski_projekti/coinsonashelf.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

#ifndef QT_NO_OPENGL
    MainWindow w;
    w.showMaximized();
    w.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

//    CoinsOnAShelf* coas = new CoinsOnAShelf(nullptr, 10);
//    coas->pokreniAlgoritam();
//    coas->pokreniNaivniAlgoritam();

    return a.exec();
    return 0;
}
