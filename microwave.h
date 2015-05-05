#ifndef MICROWAVE_H
#define MICROWAVE_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>
#include <QTime>

namespace Ui {
class MicroWave;
}

class MicroWave : public QWidget
{
    Q_OBJECT

public:
    explicit MicroWave(QWidget *parent = 0);
    ~MicroWave();

private slots:
    void on_modeTea_clicked();

    void on_modeChicken_clicked();

    void on_modeSoup_clicked();

    void on_modePuree_clicked();

    void on_power450_clicked();

    void on_power600_clicked();

    void on_power800_clicked();

    void on_power1000_clicked();

    void on_timeSec_clicked();

    void on_timeMin_clicked();

    void on_timeTenMin_clicked();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    /********/
    void stopTimer();

    void checkTime(int& timeLCD, int mod);

    void setLCDTime();

    void updateTimeForQTime();

    void updateTimeForQTimer();

    void setLCDPower();

    void enableStartStopButton();

    void setLCDs();

    void updateDisplayTime();

    void enableButtonsTrue();

    void enableButtonsFalse();

    void turnOnLED();

    void turnOffLED();

private:
    Ui::MicroWave *ui;
    QTimer* timer; //timer del reloj
    QTime timeLCD; //Objeto para representar el tiempo en el LCD
    //Objeto de control del timer del reloj para apagarlo
    //utilizado especialmente para evitar intercalado de lineas de tiempo
    QTime timerStopLimit;
    int sec; //Unidades de segundos: 1 segundo
    int minUnt; //Unidades de minutos: 1 minuto
    int minDec; //Decenas de minutos: 10 minuto
    int totalMin; //Total minutos: unidades minutos + decenas minutos
    int totalTime; //Total de tiempo en segundos: unidades minutos * 60 + decenas minutos * 600 + unidades segundos
    int power; //Valor de potencia del microondas
    bool isStartStopPaired; //Variable de emparejamiento boton Start y Stop
};

#endif // MICROWAVE_H
