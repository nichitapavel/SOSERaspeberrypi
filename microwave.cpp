#include "microwave.h"
#include "ui_microwave.h"

MicroWave::MicroWave(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MicroWave)
{
    ui->setupUi(this);
    ui->lcdTime->display(0);

    timer = new QTimer(this);
    timerLED = new QTimer(this);
    timeLCD = QTime();
    timerStopLimit = QTime();

    sec = 0;
    minUnt = 0;
    minDec = 0;
    totalMin = 0;
    totalTime = 0;
    power = 0;

    //Variable de emparejamiento boton Start y Stop
    //Si Start ha sido pulsado valor FALSE, no están emparejados
    //Si Start ha sido pulsado y Stop también valor TRUE, están emparejados
    //El valor siempre cambio si se pulsa Start
    //Si se pulsa Stop depende de unas condiciones
    isStartStopPaired = true;
}

MicroWave::~MicroWave()
{
    delete ui;
    delete timer;
}


/*
 * Menu Preconfigurado
 */
void MicroWave::on_modeTea_clicked(void)
{
        power = 1000;
        minDec = 0; minUnt = 1; sec = 0;
        updateTimeForQTime();
        setLCDs();
}

void MicroWave::on_modeChicken_clicked()
{
        power = 800;
        minDec = 0; minUnt = 2; sec = 30;
        updateTimeForQTime();
        setLCDs();

}

void MicroWave::on_modeSoup_clicked()
{
        power = 600;
        minDec = 0; minUnt = 4; sec = 0;
        updateTimeForQTime();
        setLCDs();
}

void MicroWave::on_modePuree_clicked()
{
    power = 450;
    minDec = 0; minUnt = 6; sec = 0;
    updateTimeForQTime();
    setLCDs();
}

/*
 * Elegir potencia
 */
void MicroWave::on_power450_clicked()
{
    power = 450;
    set_LCDPower();
}

void MicroWave::on_power600_clicked()
{
    power = 600;
    set_LCDPower();
}

void MicroWave::on_power800_clicked()
{
    power = 800;
    set_LCDPower();
}

void MicroWave::on_power1000_clicked()
{
    power = 1000;
    set_LCDPower();
}

/*
 * Añadir tiempo
 */
void MicroWave::on_timeSec_clicked()
{
    sec += 10;
    checkTime(sec, 60);
    updateTimeForQTime();
    setLCDTime();
}

void MicroWave::on_timeMin_clicked()
{
    minUnt += 1;
    checkTime(minUnt, 10);
    updateTimeForQTime();
    setLCDTime();
}

void MicroWave::on_timeTenMin_clicked()
{
    minDec += 10;
    checkTime(minDec, 60);
    updateTimeForQTime();
    setLCDTime();
}

/*
 * Start & Stop
 */
void MicroWave::on_startButton_clicked()
{
    delete timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDisplayTime()));
    timer->start(1000);
    QTimer::singleShot(totalTime * 1000, this, SLOT(stopTimer()));
    timerStopLimit = QTime::currentTime();
    timerStopLimit = timerStopLimit.addSecs(totalTime);
    isStartStopPaired = false;
    enableStartStopButton(); //desactivar boton Start
    enableButtonsFalse(); //desactivar los botones Menu, Potencia, Tiempo
    turnOnLED(); //Activar LED
}

void MicroWave::on_stopButton_clicked()
{
    // STOP1, si se esta ejecutando
    if (timer->isActive()){ //timer->isActive() = true
        timer->stop();
        enableStartStopButton(); //Activar botones de Start
        enableButtonsTrue(); //Activar los botones Menu, Potencia, Tiempo
        turnOffLED();
        isStartStopPaired = true;
    }
    //STOP2, Estado por defecto, limpia los datos
    else { //timer->isActive() = false
        minDec = minUnt = sec = 0;
        power = 0;
        updateTimeForQTime();
        setLCDs();
        enableStartStopButton();
        enableButtonsTrue();
    }
}


/*
 * Cosas
 */
//parar el timer si esta activo
void MicroWave::stopTimer()
{
    if (timerStopLimit <= QTime::currentTime() && !isStartStopPaired) //isStartStopPaired = false
    {
        timer->stop();
        minDec = minUnt = sec = 0;
        power = 0;
        setLCDs();
        enableStartStopButton();
        isStartStopPaired = true;
        enableButtonsTrue();
        turnOffLED();
    }
}

//Actualizar cada segundo el LCD de tiempo
//Quitamos un segundo para cada vez que se ejecute
void MicroWave::updateDisplayTime()
{
    totalTime -= 1;
    updateTimeForQTimer();
    turnOnLED();
    setLCDTime();
}

//Encender led y setear el temporizador para apagarlo
void MicroWave::turnOnLED(){
    ui->textEdit->setText("ON");
    if (power != 1000)
        QTimer::singleShot(power, this, SLOT(turnOffLED()));
}

void MicroWave::turnOffLED(){
    ui->textEdit->setText("OFF");
}

//Poner los valores de las variables de segundos, unidades de minutos, decenas de minutos
//A partir del tiempo total en segundos
void MicroWave::updateTimeForQTimer()
{
    int minutes = totalTime;

    minDec = minutes / 60;
    minutes = minutes - minDec * 60;
    minUnt = minutes / 60;
    sec = minutes % 60;

    updateTimeForQTime();
}

//Se actualiza el la parte de tiempo de los minutos
//Se actualiza el tiempo total en segundos
void MicroWave::updateTimeForQTime()
{
    totalMin = minDec + minUnt;
    totalTime = totalMin * 60 + sec;
    timeLCD.setHMS(0, totalMin, sec); //Se pone la hora en 0:minutos:segundos:0 (hh:mm:ss:ms)
}

//Comprobar las unidades de tiempo
//Para segundos se divide sobre 60 (60 segundos = 1 minuto, cada 60 segundos pone a 0)
//Para unidades de minutos se divide sobre 10 (1 minuto = 10 minutos, cada 10 minutos se vuelve a 0)
//Para decenas de minutos se divide sobre 60 (60 minutos = 1 hora, cada 60 minutos se vuelve a 0)
void MicroWave::checkTime(int& time, int mod)
{
    if ((time % mod) == 0)
        time = 0;
}

//Se pone la potencia (power) en el LCD de potencia
//Activa desactiva botones de Start y Stop
void MicroWave::set_LCDPower()
{
    ui->lcdPower->display(power);
    enableStartStopButton();
}

//Se pone los minutos y segundos (time) en el LCD de tiempo
//Activa desactiva botones de Start y Stop
void MicroWave::setLCDTime()
{
    if (totalTime != 0) //si tiempo en segundos es mayor a 0 poner el tiempo
        ui->lcdTime->display(timeLCD.toString("mm:ss"));
    else
        ui->lcdTime->display(0);

    enableStartStopButton();
}

//Pone "power" en LCD de Potencia y
void MicroWave::setLCDs()
{
    set_LCDPower();
    setLCDTime();
}

//Activa o Desactiva (según lo necesario) los botones de Start y Stop
void MicroWave::enableStartStopButton(){
    if (!(timer->isActive()) and (power != 0) and (totalTime != 0))
        ui->startButton->setEnabled(true);
    else
        ui->startButton->setEnabled(false);

    if (power != 0 or totalTime != 0)
        ui->stopButton->setEnabled(true);
    else
        ui->stopButton->setEnabled(false);
}

//Activa los botones de Menu preconfigurado, Potencia y Tiempo
void MicroWave::enableButtonsTrue()
{
    ui->modeTea->setEnabled(true);
    ui->modeChicken->setEnabled(true);
    ui->modeSoup->setEnabled(true);
    ui->modePuree->setEnabled(true);

    ui->timeSec->setEnabled(true);
    ui->timeMin->setEnabled(true);
    ui->timeTenMin->setEnabled(true);

    ui->power450->setEnabled(true);
    ui->power600->setEnabled(true);
    ui->power800->setEnabled(true);
    ui->power1000->setEnabled(true);
}

//Desactivar los botones de Menu preconfigurado, Potencia y Tiempo
void MicroWave::enableButtonsFalse()
{
    ui->modeTea->setEnabled(false);
    ui->modeChicken->setEnabled(false);
    ui->modeSoup->setEnabled(false);
    ui->modePuree->setEnabled(false);

    ui->timeSec->setEnabled(false);
    ui->timeMin->setEnabled(false);
    ui->timeTenMin->setEnabled(false);

    ui->power450->setEnabled(false);
    ui->power600->setEnabled(false);
    ui->power800->setEnabled(false);
    ui->power1000->setEnabled(false);
}
