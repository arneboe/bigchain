#include "strobe.h"
#include "ui_strobe.h"

Strobe::Strobe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Strobe)
{
    ui->setupUi(this);
}

Strobe::~Strobe()
{
    delete ui;
}
