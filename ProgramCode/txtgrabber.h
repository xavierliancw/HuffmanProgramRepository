#ifndef TXTGRABBER_H
#define TXTGRABBER_H

#include <QDialog>

namespace Ui {
class TxtGrabber;
}

class TxtGrabber : public QDialog
{
    Q_OBJECT

public:
    explicit TxtGrabber(QWidget *parent = 0);
    ~TxtGrabber();

private:
    Ui::TxtGrabber *ui;
};

#endif // TXTGRABBER_H
