#include <QApplication>
#include "microwave.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    MicroWave window;
    window.show();

    return app.exec();
}
