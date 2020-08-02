#include "licensewindow.h"
#include "ui_licensewindow.h"

void LicenseWindow::createLicenseWidgets()
{
    this->licenseFont.setFamily("Alien Encounters");
    this->licenseFont.setPixelSize(16);
    this->labelName = new QLabel("Formatter NTFS - formatting utility NTFS", this);
    this->labelName->setGeometry(15, 5, this->WIDTH - 30, 30);
    this->labelName->setFont(this->licenseFont);
    this->labelName->show();

    this->licenseFont.setFamily("Autumn");
    this->licenseFont.setPixelSize(14);
    this->labelVersion = new QLabel("Version 2.1 (Build 35)", this);
    this->labelVersion->setGeometry(15, 25, this->WIDTH - 30, 30);
    this->labelVersion->setFont(this->licenseFont);
    this->labelVersion->show();

    this->licenseFont.setFamily("Autumn");
    this->licenseFont.setPixelSize(14);
    this->labelCopyright = new QLabel("Copyright © 2001 - 2020 Diman Vector / Vector Inc.", this);
    this->labelCopyright->setGeometry(15, 55, this->WIDTH - 30, 30);
    this->labelCopyright->setFont(this->licenseFont);
    this->labelCopyright->show();

    this->licenseFont.setFamily("Autumn");
    this->licenseFont.setPixelSize(14);
    this->labelSiteOne = new QLabel("https://github.com/vectordiman/FormatterNTFS", this);
    this->labelSiteOne->setGeometry(15, 75, this->WIDTH - 30, 30);
    this->labelSiteOne->setFont(this->licenseFont);
    this->labelSiteOne->show();

    this->licenseFont.setFamily("Autumn");
    this->licenseFont.setPixelSize(14);
    this->labelTellError = new QLabel("Report a bug or suggest improvement to the website", this);
    this->labelTellError->setGeometry(15, 105, this->WIDTH - 30, 30);
    this->labelTellError->setFont(this->licenseFont);
    this->labelTellError->show();

    this->licenseFont.setFamily("Autumn");
    this->licenseFont.setPixelSize(14);
    this->labelSiteTwo = new QLabel("https://github.com/vectordiman/FormatterNTFS", this);
    this->labelSiteTwo->setGeometry(15, 125, this->WIDTH - 30, 30);
    this->labelSiteTwo->setFont(this->licenseFont);
    this->labelSiteTwo->show();

    this->licenseFont.setFamily("Alien Encounters");
    this->licenseFont.setPixelSize(16);
    this->labelLicense = new QLabel("License: ", this);
    this->labelLicense->setGeometry(15, 155, this->WIDTH - 30, 30);
    this->labelLicense->setFont(this->licenseFont);
    this->labelLicense->show();

    QFile licenseFile("./store/info/license.txt");
    licenseFile.open(QFile::ReadOnly);
    this->licenseFont.setFamily("Autumn");
    this->licenseFont.setPixelSize(14);

    QFile styleFile(":/styleScrollBar.css");
    styleFile.open(QFile::ReadOnly);

    this->verticalScrollBar  = new QScrollBar(nullptr);
    this->verticalScrollBar->setStyleSheet(styleFile.readAll());

    this->textEditLicense = new QTextEdit(this);
    this->textEditLicense->setReadOnly(true);
    this->textEditLicense->setGeometry(15, 185, this->WIDTH - 30, this->HEIGHT - 245);
    this->textEditLicense->setText(licenseFile.readAll());
    this->textEditLicense->setFont(this->licenseFont);
    this->textEditLicense->setVerticalScrollBar(this->verticalScrollBar);
    this->textEditLicense->show();

    this->licenseFont.setFamily("Good Times");
    this->licenseFont.setPixelSize(11);
    this->buttonOK = new QPushButton("OK", this);
    this->buttonOK->setGeometry(this->WIDTH - 115, this->HEIGHT - 45, 100, 30);
    this->buttonOK->setFont(this->licenseFont);
    this->buttonOK->show();
    connect(this->buttonOK,SIGNAL(clicked()),this,SLOT(handleLicenseOK()));
}
void LicenseWindow::handleLicenseOK()
{
    this->close();
}

LicenseWindow::LicenseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LicenseWindow)
{
    ui->setupUi(this);

    this->licenseIcon = new QIcon("./store/icons/mainIcon.ico");
    this->setWindowTitle("License");
    this->setBaseSize(this->WIDTH, this->HEIGHT);
    this->setMaximumSize(this->WIDTH, this->HEIGHT);
    this->setMinimumSize(this->WIDTH, this->HEIGHT);
    this->setWindowIcon(*this->licenseIcon);

    QFile styleFileLicenseWindow(":/styleLicenseWindow.css");
    styleFileLicenseWindow.open(QFile::ReadOnly);
    this->setStyleSheet(styleFileLicenseWindow.readAll());
    this->createLicenseWidgets();
}

LicenseWindow::~LicenseWindow()
{
    delete this->labelName;
    delete this->labelVersion;
    delete this->labelCopyright;
    delete this->labelSiteOne;
    delete this->labelTellError;
    delete this->labelSiteTwo;
    delete this->labelLicense;
    delete this->licenseIcon;

    delete this->buttonOK;

    delete this->textEditLicense;
    delete this->verticalScrollBar;

    delete ui;
}
