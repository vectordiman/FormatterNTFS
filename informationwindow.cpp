#include "informationwindow.h"
#include "ui_informationwindow.h"

void InformationWindow::createInformationWidgets()
{

    this->informationFont.setFamily("Alien Encounters");
    this->informationFont.setPixelSize(16);
    this->labelInformation = new QLabel("System information: ", this);
    this->labelInformation->setGeometry(15, 5, this->WIDTH - 30, 30);
    this->labelInformation->setFont(this->informationFont);
    this->labelInformation->show();

    QFile informationFile("./store/info/information.txt");
    informationFile.open(QFile::ReadOnly);
    this->informationFont.setFamily("Autumn");
    this->informationFont.setPixelSize(14);

    QFile styleFile(":/styleScrollBar.css");
    styleFile.open(QFile::ReadOnly);

    this->verticalScrollBar  = new QScrollBar(nullptr);
    this->verticalScrollBar->setStyleSheet(styleFile.readAll());

    this->textEditInformation = new QTextEdit(this);
    this->textEditInformation->setReadOnly(true);
    this->textEditInformation->setGeometry(15, 35, this->WIDTH - 30, this->HEIGHT - 95);
    this->textEditInformation->setText(informationFile.readAll());
    this->textEditInformation->setFont(this->informationFont);
    this->textEditInformation->setVerticalScrollBar(this->verticalScrollBar);
    this->textEditInformation->show();

    this->informationFont.setFamily("Good Times");
    this->informationFont.setPixelSize(11);
    this->buttonOK = new QPushButton("OK", this);
    this->buttonOK->setGeometry(this->WIDTH - 115, this->HEIGHT - 45, 100, 30);
    this->buttonOK->setFont(this->informationFont);
    this->buttonOK->show();
    connect(this->buttonOK,SIGNAL(clicked()),this,SLOT(handleInformationOK()));
}
void InformationWindow::handleInformationOK()
{
    this->close();
}

void InformationWindow::readInformation()
{
    QFile informationFile("./store/info/information.txt");
    informationFile.open(QFile::ReadOnly);

    if(informationFile.size() == 0)
    {
        informationFile.close();
        QString program = "msinfo32 /report ./store/info/information.txt";

        QProcess *myProcess = new QProcess(this);
        QString command = QString("cmd.exe %1 \"%2 \"").arg(" /C ").arg(program);
        myProcess->start(command);
        if (myProcess->waitForStarted(-1))
        {
            while(myProcess->waitForReadyRead(-1)){}
        }
        myProcess->kill();
        if(myProcess)
            delete myProcess;
    }
    else
        informationFile.close();
}

InformationWindow::InformationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationWindow)
{
    ui->setupUi(this);

    this->readInformation();

    this->informationIcon = new QIcon("./store/icons/mainIcon.ico");
    this->setWindowTitle("Information");
    this->setBaseSize(this->WIDTH, this->HEIGHT);
    this->setMaximumSize(this->WIDTH, this->HEIGHT);
    this->setMinimumSize(this->WIDTH, this->HEIGHT);
    this->setWindowIcon(*this->informationIcon);

    QFile styleFileMainWindow(":/styleInformationWindow.css");
    styleFileMainWindow.open(QFile::ReadOnly);
    this->setStyleSheet(styleFileMainWindow.readAll());
    this->createInformationWidgets();
}

InformationWindow::~InformationWindow()
{
    delete this->buttonOK;
    delete this->informationIcon;
    delete this->labelInformation;
    delete this->verticalScrollBar;
    delete this->textEditInformation;

    delete ui;
}
