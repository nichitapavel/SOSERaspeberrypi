/**********************************************************************
* @titulo       Proyecto aplicacion Qt para RaspberryPi
* @subtitulo    Desarrollo de aplicacion Qt para sistemas empotrados
*               basados en RaspberryPi y pantalla tactil PiTFT.
* @author       Pavel Nichita
* @author       Alejandro Perez
* @version      1.0 04/05/15
* @asignatura   Sistemas Operativos Y Sistemas Empotrados
* @descripcion  La aplicacion simula el panel de control de
*               un microondas.
*               Dispone de modos predefinidos, selector de tiempos y
*               de potencia, asi como botones para arranque y parada.
*               La simulacion de la potencia del microondas se hace
*               mediante el encendido/apagado de un led. La potencia
*               del microondas varia pues en relacion con la frecuencia
*               de encendido de dicho led,esto es, a mayor frecuencia,
*               mayor potencia. La maxima frecuencia se expresa con
*               el led encendido durante el tiempo de programacion.
*               El acceso al led se hace mediante lectura/escritura en
*               la direccion de memoria del GPIO correspondiente en la
*               RaspberryPi. Las instrucciones de E/S estan definidas
*               en la libreria GPIOClass.
*               La aplicacion se compone de los siguientes modulos:
*               - Un formulario (microwave.ui)
*               - Control del microondas (microwave.h y microwave.cpp)
*               - Control del GPIO (GPIOClass.h GPIOClass.cpp)
*               - Programa principal Holamundo.cpp.
*
**************************************************************************/

#include <QApplication>
#include "microwave.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    MicroWave window;
    window.show();

    return app.exec();
}
