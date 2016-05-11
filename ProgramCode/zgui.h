#ifndef ZGUI_H
#define ZGUI_H

#include <QMainWindow>

namespace Ui {
class zGui;
}

class zGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit zGui(QWidget *parent = 0);
    ~zGui();

private:
    Ui::zGui *ui;
};

#endif // ZGUI_H
