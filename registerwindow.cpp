#include "registerwindow.h"
#include "ui_registerwindow.h"

void RegisterWindow::createRegisterWidgets()
{
    this->registerFont.setFamily("Alien Encounters");
    this->registerFont.setPixelSize(16);
    this->labelRegister = new QLabel("Register: ", this);
    this->labelRegister->setGeometry(15, 5, this->WIDTH - 30, 30);
    this->labelRegister->setFont(this->registerFont);
    this->labelRegister->show();

    QFile informationFile("./store/info/register.txt");
    informationFile.open(QFile::ReadOnly);
    this->registerFont.setFamily("Autumn");
    this->registerFont.setPixelSize(14);

    QFile styleFile(":/styleScrollBar.css");
    styleFile.open(QFile::ReadOnly);

    this->verticalScrollBar  = new QScrollBar(nullptr);
    this->verticalScrollBar->setStyleSheet(styleFile.readAll());

    this->textEditInformation = new QTextEdit(this);
    this->textEditInformation->setReadOnly(true);
    this->textEditInformation->setGeometry(15, 35, this->WIDTH - 30, this->HEIGHT - 95);
    this->textEditInformation->setText(informationFile.readAll());
    this->textEditInformation->setFont(this->registerFont);
    this->textEditInformation->setVerticalScrollBar(this->verticalScrollBar);
    this->textEditInformation->show();

    this->registerFont.setFamily("Good Times");
    this->registerFont.setPixelSize(11);
    this->buttonOK = new QPushButton("OK", this);
    this->buttonOK->setGeometry(this->WIDTH - 115, this->HEIGHT - 45, 100, 30);
    this->buttonOK->setFont(this->registerFont);
    this->buttonOK->show();
    connect(this->buttonOK,SIGNAL(clicked()),this,SLOT(handleRegisterOK()));
}

void RegisterWindow::handleRegisterOK()
{
    this->close();
}

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    this->registerIcon = new QIcon("./store/icons/mainIcon.ico");
    this->setWindowTitle("Register");
    this->setBaseSize(this->WIDTH, this->HEIGHT);
    this->setMaximumSize(this->WIDTH, this->HEIGHT);
    this->setMinimumSize(this->WIDTH, this->HEIGHT);
    this->setWindowIcon(*this->registerIcon);

    QFile styleFileMainWindow(":/styleRegisterWindow.css");
    styleFileMainWindow.open(QFile::ReadOnly);
    this->setStyleSheet(styleFileMainWindow.readAll());
    this->createRegisterWidgets();
}

RegisterWindow::~RegisterWindow()
{
    delete this->buttonOK;
    delete this->registerIcon;
    delete this->labelRegister;
    delete this->verticalScrollBar;
    delete this->textEditInformation;

    delete ui;
}
