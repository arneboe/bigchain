#include "strobe.h"
#include "ui_strobe.h"
#include "../Mode.h"
#include "../StrobeMode.h"

Strobe::Strobe(QSerialPort* port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Strobe),
    port(port),
    enabled(false)
{
    ui->setupUi(this);
}

Strobe::~Strobe()
{
    delete ui;
}

void Strobe::enable()
{
    enabled = true;
    send();
}

void Strobe::disable()
{
    enabled = false;
}

void Strobe::send()
{
    if(enabled)
    {
        QByteArray data;
        data.append((char)STROBE);
        data.append((char)ui->speedSlider->value());

        if(ui->buttonHalf->isChecked())
        {
            data.append((char)STROBE_HALF);
        }
        else if(ui->buttonRandom->isChecked())
        {
            data.append((char)STROBE_RANDOM);
        }
        else if(ui->buttonNormal->isChecked())
        {
            data.append((char)STROBE_NORMAL);
        }
        else if(ui->buttonSnake->isChecked())
        {
            data.append((char)STROBE_SNAKE);
        }
        else if(ui->buttonAreas->isChecked())
        {
            data.append((char)STROBE_AREA);
        }

        if(ui->checkBoxColor->isChecked())
        {
            data.append((char)1);
        }
        else
        {
            data.append((char) 0);
        }

        port->write(data);
    }
}


void Strobe::on_buttonNormal_clicked()
{
    ui->buttonHalf->setChecked(false);

    ui->buttonRandom->setChecked(false);
    ui->buttonNormal->setChecked(true);
    ui->buttonSnake->setChecked(false);
    ui->buttonAreas->setChecked(false);
    send();
}

void Strobe::on_buttonRandom_clicked()
{
    ui->buttonHalf->setChecked(false);

    ui->buttonRandom->setChecked(true);
    ui->buttonNormal->setChecked(false);
    ui->buttonSnake->setChecked(false);
    ui->buttonAreas->setChecked(false);
    send();
}

void Strobe::on_buttonHalf_clicked()
{
    ui->buttonHalf->setChecked(true);

    ui->buttonRandom->setChecked(false);
    ui->buttonNormal->setChecked(false);
    ui->buttonSnake->setChecked(false);
    ui->buttonAreas->setChecked(false);
    send();
}

void Strobe::on_buttonCircles_clicked()
{
    ui->buttonHalf->setChecked(false);

    ui->buttonRandom->setChecked(false);
    ui->buttonNormal->setChecked(false);
    ui->buttonSnake->setChecked(false);
    ui->buttonAreas->setChecked(false);
    send();
}

void Strobe::on_speedSlider_valueChanged(int val)
{
    ui->spinBoxSpeed->setValue(val);
    send();
}

void Strobe::on_checkBoxColor_clicked()
{
    send();
}

void Strobe::on_buttonSnake_clicked()
{
    ui->buttonHalf->setChecked(false);

    ui->buttonRandom->setChecked(false);
    ui->buttonNormal->setChecked(false);
    ui->buttonAreas->setChecked(false);
    ui->buttonSnake->setChecked(true);
    send();
}

void Strobe::on_buttonAreas_clicked()
{
    ui->buttonHalf->setChecked(false);

    ui->buttonRandom->setChecked(false);
    ui->buttonNormal->setChecked(false);
    ui->buttonSnake->setChecked(false);
    ui->buttonAreas->setChecked(true);
    send();
}
