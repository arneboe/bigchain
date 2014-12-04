#include "fade.h"
#include "ui_fade.h"
#include "../Mode.h"

using namespace std;

Fade::Fade(QSerialPort* port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fade),
    port(port),
    enabled(false),
    randomColors(false),
    sameColors(false)
{
    Q_ASSERT(port);
    ui->setupUi(this);
}

Fade::~Fade()
{
    delete ui;
}

void Fade::enable()
{
    enabled = true;
    send();
}

void Fade::disable()
{
    enabled = false;
}

void Fade::send()
{
    if(enabled)
    {
        QByteArray data;
        data.append((char)FADE);
        data.append((char)ui->speedSlider->value());
        if(randomColors)
        {
            data.append((char)1);
            randomColors = false;
        }
        else if(sameColors)
        {
            data.append((char)2);
            sameColors = false;
        }
        else
        {
            data.append((char)0);
        }
        port->write(data);
    }
}

void Fade::on_randomColorsButton_clicked()
{
    randomColors = true;
    send();
}

void Fade::on_speedSlider_valueChanged(int value)
{
    send();
}

void Fade::on_pushButton_clicked()
{
    sameColors = true;
    send();
}
