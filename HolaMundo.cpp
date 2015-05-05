/*
* @author Jose Alejandro Perez Rodriguez
* @author Pavel Nichita
* @version 1.0 04/05/15
* @asignatura Sistemas Operativos Y Sistemas Empotrados
*/

#include <QApplication>
#include "microwave.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    MicroWave window;
    window.show();

    return app.exec();
}
