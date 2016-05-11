#include "txtgrabber.h"
#include "ui_txtgrabber.h"

TxtGrabber::TxtGrabber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TxtGrabber)
{
    ui->setupUi(this);
}

TxtGrabber::~TxtGrabber()
{
    delete ui;
}
