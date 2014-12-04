#ifndef FADE_H
#define FADE_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include "modeUi.h"

namespace Ui {
class Fade;
}

class Fade : public QWidget, public ModeUi
{
    Q_OBJECT

public:
    explicit Fade(QSerialPort* port, QWidget *parent = 0);
    ~Fade();
    virtual void enable();
    virtual void disable();

private slots:
    void on_randomColorsButton_clicked();

    void on_speedSlider_valueChanged(int value);

    void on_pushButton_clicked();

private:
    void send();
    Ui::Fade *ui;
    QSerialPort* port;
    bool enabled;
    bool randomColors;
    bool sameColors;
};

#endif // FADE_H
