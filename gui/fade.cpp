#include "fade.h"
#include "ui_fade.h"

Fade::Fade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fade)
{
    ui->setupUi(this);
}

Fade::~Fade()
{
    delete ui;
}
