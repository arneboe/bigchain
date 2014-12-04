#ifndef STROBE_H
#define STROBE_H

#include <QWidget>

namespace Ui {
class Strobe;
}

class Strobe : public QWidget
{
    Q_OBJECT

public:
    explicit Strobe(QWidget *parent = 0);
    ~Strobe();

private:
    Ui::Strobe *ui;
};

#endif // STROBE_H
