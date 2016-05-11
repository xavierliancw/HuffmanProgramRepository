#ifndef ZGUI_H
#define ZGUI_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QMovie>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {class zGui;}

class zGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit zGui(QWidget *parent = 0);
    ~zGui();

private slots:
    //Index 0 - start ----------------------------------------------------
    void on_startBeginBt_clicked();

    //Index 1 - home------------------------------------------------------
    void on_homeBackBt_clicked();

    void on_homeEncodeBt_clicked();

    void on_homeDecodeBt_clicked();

private:
    Ui::zGui *ui;
};

#endif // ZGUI_H
