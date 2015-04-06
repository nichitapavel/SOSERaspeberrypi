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

    void checkTime(int& time, int mod);

    void setLCDTime();

    void updateTimeForQTime();

    void updateTimeForQTimer();

    void set_LCDPower();

    void enableStartStopButton();

    void setLCDs();

    void updateDisplayTime();

    void enableButtonsTrue();

    void enableButtonsFalse();

    void turnOnLED();

    void turnOffLED();

private:
    Ui::MicroWave *ui;
    QTimer* timer;
    QTimer* timerLED;
    QTime time;
    int sec;
    int minUnt;
    int minDec;
    int totalMin;
    int totalTime;
    int power;
    int timerNumber;
    int timerNumber2;
    bool pause;
};

#endif // MICROWAVE_H
