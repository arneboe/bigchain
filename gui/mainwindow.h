#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <vector>
#include "modeUi.h"
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const std::string& ttyName,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_activateButton_clicked();

private:
    void initPort(const std::string& ttyName);

    Ui::MainWindow *ui;
    QSerialPort port;
    std::vector<ModeUi*> modes;
    int activeMode;

};

#endif // MAINWINDOW_H
