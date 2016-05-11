#include "zgui.h"
#include "ui_zgui.h"

zGui::zGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::zGui)
{
    ui->setupUi(this);
}

zGui::~zGui()
{
    delete ui;
}
