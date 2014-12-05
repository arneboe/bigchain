#ifndef STROBE_H
#define STROBE_H

#include <QWidget>
#include "modeUi.h"
#include <QtSerialPort/QSerialPort>

namespace Ui {
class Strobe;
}

class Strobe : public QWidget, public ModeUi
{
    Q_OBJECT

public:
    explicit Strobe(QSerialPort* port, QWidget *parent = 0);
    ~Strobe();

    virtual void enable();
    virtual void disable();

private slots:
    void on_buttonNormal_clicked();

    void on_buttonRandom_clicked();

    void on_buttonHalf_clicked();

    void on_buttonCircles_clicked();

    void on_speedSlider_valueChanged(int value);

    void on_checkBoxColor_clicked();

    void on_buttonSnake_clicked();

    void on_buttonAreas_clicked();

private:
    void send();
    Ui::Strobe *ui;
    QSerialPort* port;
    bool enabled;
};

#endif // STROBE_H
