#ifndef FADE_H
#define FADE_H

#include <QWidget>

namespace Ui {
class Fade;
}

class Fade : public QWidget
{
    Q_OBJECT

public:
    explicit Fade(QWidget *parent = 0);
    ~Fade();

private:
    Ui::Fade *ui;
};

#endif // FADE_H
