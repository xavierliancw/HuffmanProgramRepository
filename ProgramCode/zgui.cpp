#include "zgui.h"
#include "ui_zgui.h"

zGui::zGui(QWidget *parent) : QMainWindow(parent), ui(new Ui::zGui)
//GUI constructor
{
    //GUI initializations
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/icon.png"));

    //Setup start screen's gif
    QMovie *titleMovie = new QMovie(":/images/binary.gif");
    QLabel *movieLabel = new QLabel(ui->start);
    movieLabel->setMovie(titleMovie);
    movieLabel->setScaledContents(true);
    movieLabel->setAlignment(Qt::AlignCenter);
    QStackedLayout *stackLay = new QStackedLayout;
    stackLay->addWidget(ui->frame);
    stackLay->addWidget(movieLabel);
    stackLay->setStackingMode(QStackedLayout::StackAll);
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addLayout(stackLay);
    ui->start->setLayout(lay);
    movieLabel->show();
    titleMovie->start();
}

zGui::~zGui()
//Destructor
{delete ui;}

void zGui::on_startBeginBt_clicked()
{ui->stackWidg->setCurrentIndex(1);}

void zGui::on_homeBackBt_clicked()
{ui->stackWidg->setCurrentIndex(0);}

void zGui::on_homeEncodeBt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                    "C://","Text File (*.txt)");
    QMessageBox::information(this,tr("Title of msg box"),fileName);
}

void zGui::on_homeDecodeBt_clicked()
{

}
