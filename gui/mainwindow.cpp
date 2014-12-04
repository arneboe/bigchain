#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fade.h"
#include "strobe.h"

MainWindow::MainWindow(const std::string& ttyName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPort(ttyName);

    Fade* fade = new Fade(&port, this);
    modes.push_back((ModeUi*)fade);
    ui->tabWidget->addTab((QWidget*)fade,"Color Fade");

    Strobe* strobe = new Strobe(&port, this);
    modes.push_back((ModeUi*)strobe);
    ui->tabWidget->addTab((QWidget*)strobe,"Strobe");

    activeMode = 0;
    modes[0]->enable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPort(const std::string& ttyName)
{
    const qint32 baud = 9600;
    const QString portName(ttyName.c_str());
    port.setPortName(portName);

    if(!port.open(QIODevice::ReadWrite))
    {
      qFatal("Unable to open serial port");
      exit(1); //FIXME this is bad style :D
    }
    if(!port.setParity(QSerialPort::NoParity) ||
       !port.setStopBits(QSerialPort::OneStop) ||
       !port.setDataBits(QSerialPort::Data8) ||
       !port.setFlowControl(QSerialPort::NoFlowControl ) ||
       !port.setBaudRate(baud) ||
       !port.setDataTerminalReady(true))
    {
      qFatal("Unable to configure serial port");
      exit(1); //FIXME baaad
    }
    if(port.error() != QSerialPort::NoError)
    {
      qFatal("some error occurred!");
    }
}


void MainWindow::on_activateButton_clicked()
{
    modes[activeMode]->disable();
    //activate current tab mode
    activeMode = ui->tabWidget->currentIndex();
    modes[activeMode]->enable();

}
