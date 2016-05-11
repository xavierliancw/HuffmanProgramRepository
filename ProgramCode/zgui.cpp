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
//Encode the text area
{
    //Clear out the text field
    ui->homeResultsTE->clear();

    //Move this to private and change how constructor works
    Huffman encoder(ui->homeOrigTE->toPlainText());
    ui->homeResultsTE->setPlainText(encoder.getEncoding());

    //Update a UI label to tell user that this is encoded text
    ui->homeResultLbl->setText("Encoded Text");

    //Move the UI to show area of interest
    ui->homeTabWdg->setCurrentIndex(1);
}

void zGui::on_homeDecodeBt_clicked()
{

}

void zGui::on_homeImportBt_clicked()
//Import a text file
{
    int proceed;    //User prompt answer

    //Move the UI to show area of interest
    ui->homeTabWdg->setCurrentIndex(0);

    if (ui->homeOrigTE->toPlainText() != "")
    {
        proceed = QMessageBox::warning(this, tr("Warning"),
                                       tr("Importing a text file "
                                          "will overwrite "
                                          "the current text.\n"
                                          "Are you sure you want to "
                                          "import?"),
                                           QMessageBox::Yes
                                           | QMessageBox::Cancel);
    }
    //If Yes was pressed of the field is empty, proceed
    if (proceed == 16384
        || ui->homeOrigTE->toPlainText() == "")
    {
        //Open a file browser
        QString fileName = QFileDialog
                ::getOpenFileName(this,tr("Open File"),
                                  "C://","Text File (*.txt)");
        //Clear the text edit
        ui->homeOrigTE->clear();

        //Validate the file
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, "File Error",
                                     file.errorString());
        }

        //Import
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            ui->homeOrigTE->setPlainText(line);
        }
        file.close();
    }
}











