#include "mainwindow.h"
#include "ui_mainwindow.h"

void format(char* path);

void MainWindow::createWidgets()
{
    this->widgetFont.setFamily("Good Times");
    this->checkBoxSystem = new QCheckBox("System Formatter", this);
    this->checkBoxSystem->setGeometry(15, 45, this->WIDTH / 2 - 15, 30);
    this->checkBoxSystem->setFont(this->widgetFont);
    this->checkBoxSystem->show();
    connect(this->checkBoxSystem,SIGNAL(clicked()),this,SLOT(handleCheckSystem()));

    this->widgetFont.setFamily("Good Times");
    this->checkBoxFormatterNTFS = new QCheckBox("Formatter NTFS", this);
    this->checkBoxFormatterNTFS->setGeometry(this->WIDTH / 2 + 15, 45, this->WIDTH / 2 - 30, 30);
    this->checkBoxFormatterNTFS->setFont(this->widgetFont);
    this->checkBoxFormatterNTFS->show();
    connect(this->checkBoxFormatterNTFS,SIGNAL(clicked()),this,SLOT(handleCheckFormatter()));

    this->widgetFont.setFamily("Good Times");
    this->buttonClose = new QPushButton("Close", this);
    this->buttonClose->setGeometry(this->WIDTH - 115, this->HEIGHT - 45, 100, 30);
    this->buttonClose->setFont(this->widgetFont);
    this->buttonClose->show();
    connect(this->buttonClose,SIGNAL(clicked()),this,SLOT(handleClose()));

    this->widgetFont.setFamily("Good Times");
    this->buttonStart = new QPushButton("Start", this);
    this->buttonStart->setGeometry(this->WIDTH - 230, this->HEIGHT - 45, 100, 30);
    this->buttonStart->setEnabled(false);
    this->buttonStart->setFont(this->widgetFont);
    this->buttonStart->show();
    connect(this->buttonStart,SIGNAL(clicked()),this,SLOT(handleStart()));

    this->licenseIcon = new QIcon("./store/icons/licenseIcon.png");
    this->buttonLicense = new QPushButton("", this);
    this->buttonLicense->setGeometry(15, this->HEIGHT - 45, 30, 30);
    this->buttonLicense->setIcon(*this->licenseIcon);
    this->buttonLicense->show();
    connect(this->buttonLicense,SIGNAL(clicked()),this,SLOT(handleLicense()));

    this->informationIcon = new QIcon("./store/icons/informationIcon.png");
    this->buttonInformation = new QPushButton("", this);
    this->buttonInformation->setGeometry(60, this->HEIGHT - 45, 30, 30);
    this->buttonInformation->setIcon(*this->informationIcon);
    this->buttonInformation->show();
    connect(this->buttonInformation,SIGNAL(clicked()),this,SLOT(handleInformation()));

    this->registerIcon = new QIcon("./store/icons/registerIcon.png");
    this->buttonRegister = new QPushButton("", this);
    this->buttonRegister->setGeometry(105, this->HEIGHT - 45, 30, 30);
    this->buttonRegister->setIcon(*this->registerIcon);
    this->buttonRegister->show();
    connect(this->buttonRegister,SIGNAL(clicked()),this,SLOT(handleRegister()));

    this->widgetFont.setFamily("Good Times");
    this->labelReady = new QLabel("Ready", this);
    this->labelReady->setGeometry(15, this->HEIGHT - 90, this->WIDTH - 30, 30);
    this->labelReady->setFrameShape(QFrame::Box);
    this->labelReady->setAlignment(Qt::AlignCenter);
    this->labelReady->setFont(this->widgetFont);
    this->labelReady->setEnabled(false);
    this->labelReady->show();

    this->mainFont.setFamily("Alien Encounters");
    this->labelStatus = new QLabel("Status", this);
    this->labelStatus->setGeometry(15, this->HEIGHT - 125, 80, 30);
    this->mainFont.setPixelSize(20);
    this->labelStatus->setFont(this->mainFont);
    this->labelStatus->show();

    this->horizontalLineStatus = new QFrame(this);
    this->horizontalLineStatus->setGeometry(103, this->HEIGHT - 123, this->WIDTH - 118, 30);
    this->horizontalLineStatus->setFrameShape(QFrame::HLine);
    this->horizontalLineStatus->setFont(this->mainFont);
    this->horizontalLineStatus->show();

    this->widgetFont.setFamily("Good Times");
    this->labelFileSystem = new QLabel("NTFS", this);
    this->labelFileSystem->setGeometry(15, this->HEIGHT - 160, this->WIDTH / 2  - 30, 30);
    this->labelFileSystem->setFrameShape(QFrame::Box);
    this->labelFileSystem->setFont(this->widgetFont);
    this->labelFileSystem->setEnabled(false);
    this->labelFileSystem->show();

    this->widgetFont.setFamily("Good Times");
    this->labelFileSystemText = new QLabel("File system", this);
    this->labelFileSystemText->setGeometry(15, this->HEIGHT - 185, this->WIDTH / 2  - 30, 30);
    this->labelFileSystemText->setFont(this->widgetFont);
    this->labelFileSystemText->show();

    this->widgetFont.setFamily("Good Times");
    this->labelClusterSizeText = new QLabel("Cluster size", this);
    this->labelClusterSizeText->setGeometry(this->WIDTH / 2, this->HEIGHT - 185, this->WIDTH / 2  - 15, 30);
    this->labelClusterSizeText->setFont(this->widgetFont);
    this->labelClusterSizeText->show();

    this->widgetFont.setFamily("Good Times");
    this->lineEditNewDeviceName = new QLineEdit(this);
    this->lineEditNewDeviceName->setGeometry(15, this->HEIGHT - 220, this->WIDTH - 30, 30);
    this->lineEditNewDeviceName->setPlaceholderText("USB Disk");
    this->lineEditNewDeviceName->setFont(this->widgetFont);
    this->lineEditNewDeviceName->show();

    this->widgetFont.setFamily("Good Times");
    this->labelNewDeviceName = new QLabel("New device name", this);
    this->labelNewDeviceName->setGeometry(15, this->HEIGHT - 245, this->WIDTH - 30, 30);
    this->labelNewDeviceName->setFont(this->widgetFont);
    this->labelNewDeviceName->show();

    this->mainFont.setFamily("Alien Encounters");
    this->labelFormattingOptions = new QLabel("Formatting options", this);
    this->labelFormattingOptions->setGeometry(15, this->HEIGHT - 270, 230, 30);
    this->mainFont.setPixelSize(20);
    this->labelFormattingOptions->setFont(this->mainFont);
    this->labelFormattingOptions->show();

    this->horizontalLineFormattingOptions = new QFrame(this);
    this->horizontalLineFormattingOptions->setGeometry(240, this->HEIGHT - 268, this->WIDTH - 255, 30);
    this->horizontalLineFormattingOptions->setFrameShape(QFrame::HLine);
    this->horizontalLineFormattingOptions->setFont(this->mainFont);
    this->horizontalLineFormattingOptions->show();

    this->mainFont.setFamily("Good Times");
    this->comboBoxDevice = new QComboBox(this);
    this->comboBoxDevice->setGeometry(15, this->HEIGHT - 304, this->WIDTH - 145, 28);
    this->mainFont.setPixelSize(20);
    this->comboBoxDevice->setFont(this->mainFont);
    this->comboBoxDevice->show();

    this->widgetFont.setFamily("Good Times");
    this->buttonBrowse = new QPushButton("Browse", this);
    this->buttonBrowse->setGeometry(this->WIDTH - 115, this->HEIGHT - 305, 100, 30);
    this->buttonBrowse->setFont(this->widgetFont);
    this->buttonBrowse->show();
    connect(this->buttonBrowse,SIGNAL(clicked()),this,SLOT(handleBrowse()));

    this->mainFont.setFamily("Alien Encounters");
    this->labelDiscProperties = new QLabel("Disk properties", this);
    this->labelDiscProperties->setGeometry(15, 10, 185, 30);
    this->mainFont.setPixelSize(20);
    this->labelDiscProperties->setFont(this->mainFont);
    this->labelDiscProperties->show();

    this->horizontalLineDiscProperties = new QFrame(this);
    this->horizontalLineDiscProperties->setGeometry(200, 10, this->WIDTH - 215, 30);
    this->horizontalLineDiscProperties->setFrameShape(QFrame::HLine);
    this->horizontalLineDiscProperties->setFont(this->mainFont);
    this->horizontalLineDiscProperties->show();

    this->widgetFont.setFamily("Good Times");
    this->comboBoxClusterSize = new QComboBox(this);
    this->comboBoxClusterSize->addItem("512");
    this->comboBoxClusterSize->addItem("1024");
    this->comboBoxClusterSize->addItem("2048");
    this->comboBoxClusterSize->addItem("4096");
    this->comboBoxClusterSize->addItem("8192");
    this->comboBoxClusterSize->addItem("16K");
    this->comboBoxClusterSize->addItem("32K");
    this->comboBoxClusterSize->addItem("64K");
    this->comboBoxClusterSize->setCurrentText("4096");
    this->comboBoxClusterSize->setGeometry(this->WIDTH / 2, this->HEIGHT - 160, this->WIDTH / 2  - 15, 30);
    this->comboBoxClusterSize->setFont(this->widgetFont);
    this->comboBoxClusterSize->setEnabled(false);
    this->comboBoxClusterSize->show();
}

void MainWindow::handleClose()
{
    this->close();
}

void MainWindow::handleCheckSystem()
{
    if(!this->checkBoxFormatterNTFS->isHidden())
    {
       this->checkBoxFormatterNTFS->hide();
       this->checkBoxSystem->setGeometry(15, 45, this->WIDTH - 30, 30);
       this->lineEditNewDeviceName->setEnabled(true);
       if(this->comboBoxDevice->count())
       {
           this->comboBoxClusterSize->setEnabled(true);
           this->labelFileSystem->setEnabled(true);
           this->labelReady->setEnabled(false); //
           this->buttonStart->setEnabled(true);
       }
    }
    else
    {
        this->lineEditNewDeviceName->setEnabled(true);
        this->checkBoxSystem->setGeometry(15, 45, this->WIDTH / 2 - 15, 30);
        this->checkBoxFormatterNTFS->show();
        this->comboBoxClusterSize->setEnabled(false);
        this->labelFileSystem->setEnabled(false);
        this->labelReady->setEnabled(false); //
        this->buttonStart->setEnabled(false);
    }
}

void MainWindow::handleCheckFormatter()
{
    if(!this->checkBoxSystem->isHidden())
    {
       this->checkBoxSystem->hide();
       this->checkBoxFormatterNTFS->setGeometry(15, 45, this->WIDTH - 30, 30);
       this->lineEditNewDeviceName->setEnabled(false);
       if(this->comboBoxDevice->count())
       {
           this->comboBoxClusterSize->setEnabled(false);
           this->labelFileSystem->setEnabled(true);
           this->labelReady->setEnabled(false); //
           this->buttonStart->setEnabled(true);
       }
    }
    else
    {
        this->checkBoxFormatterNTFS->setGeometry(this->WIDTH / 2 + 15, 45, this->WIDTH / 2 - 30, 30);
        this->checkBoxSystem->show();
        this->lineEditNewDeviceName->setEnabled(true);
        this->comboBoxClusterSize->setEnabled(false);
        this->labelFileSystem->setEnabled(false);
        this->labelReady->setEnabled(false); //
        this->buttonStart->setEnabled(false);
    }
}

void MainWindow::handleStart()
{
    if(!this->checkBoxSystem->isHidden() && this->checkBoxFormatterNTFS->isHidden())
    {
        if(this->lineEditNewDeviceName->text().size() != 0)
        {
            QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Question", "You really want to \nformat your USB Disk?",
                                                                      QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::Yes)
            {
                this->comboBoxClusterSize->setEnabled(false);
                this->labelFileSystem->setEnabled(false);
                this->buttonStart->setEnabled(false);
                this->lineEditNewDeviceName->setEnabled(false);

                if(this->labelReady)
                    delete this->labelReady; //
                this->progressBarStatus = new QProgressBar(this);
                this->progressBarStatus->setGeometry(15, this->HEIGHT - 90, this->WIDTH - 30, 30);
                this->progressBarStatus->setValue(0);
                this->progressBarStatus->setTextVisible(false);
                this->progressBarStatus->setAlignment(Qt::AlignCenter);
                this->progressBarStatus->setMinimum(0);
                this->progressBarStatus->setMaximum(100);
                this->progressBarStatus->show();
                int count = 0;
                QString program = "format " + this->comboBoxDevice->currentText() + "FS:NTFS /V:" + this->lineEditNewDeviceName->text() + "/X /A:" + this->comboBoxClusterSize->currentText() + "/Q /y";

                QProcess *myProcess = new QProcess(this);
                QString command = QString("cmd.exe %1 \"%2 \"").arg(" /C ").arg(program);
                myProcess->start(command);
                if (myProcess->waitForStarted(-1))
                {
                    while(myProcess->waitForReadyRead(-1))
                    {
                        this->progressBarStatus->setValue(count);
                        count += 13;
                    }
                }
                while(this->progressBarStatus->value() != 100)
                {
                    this->progressBarStatus->setValue(count);
                    count++;
                    _sleep(30);
                }

                QDateTime dateTime = QDateTime::currentDateTimeUtc();
                QFile registerFile("./store/info/register.txt");
                registerFile.open(QFile::Append);
                QString registerString = "Device " + this->comboBoxDevice->currentText() + " was formatted to NTFS " + dateTime.toString("hh:mm dd/MM/yyyy") + "\n";
                registerFile.write(registerString.toUtf8());
                registerFile.close();
                if(this->progressBarStatus)
                    delete this->progressBarStatus;
                myProcess->kill();
                if(myProcess)
                    delete myProcess;
                this->widgetFont.setFamily("Good Times");
                this->labelReady = new QLabel("Ready", this);
                this->labelReady->setGeometry(15, this->HEIGHT - 90, this->WIDTH - 30, 30);
                this->labelReady->setFrameShape(QFrame::Box);
                this->labelReady->setAlignment(Qt::AlignCenter);
                this->labelReady->setFont(this->widgetFont);
                this->labelReady->setEnabled(true);
                this->labelReady->show();

                this->comboBoxClusterSize->setEnabled(true);
                this->labelFileSystem->setEnabled(true);
                this->buttonStart->setEnabled(true);
                this->lineEditNewDeviceName->setEnabled(true);

            }
            if(reply == QMessageBox::No)
            {
                //
            }
        }
        else
        {
            int warningMessage = QMessageBox::warning(nullptr, "Warning",  "Some values are empty!", QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::NoButton);
        }
    }
    if(!this->checkBoxFormatterNTFS->isHidden() && this->checkBoxSystem->isHidden())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Question", "You really want to \nformat your USB Disk?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            if(this->labelReady)
                delete this->labelReady; //
            this->progressBarStatus = new QProgressBar(this);
            this->progressBarStatus->setGeometry(15, this->HEIGHT - 90, this->WIDTH - 30, 30);
            this->progressBarStatus->setValue(0);
            this->progressBarStatus->setTextVisible(false);
            this->progressBarStatus->setAlignment(Qt::AlignCenter);
            this->progressBarStatus->setMinimum(0);
            this->progressBarStatus->setMaximum(100);
            this->progressBarStatus->show();
            int count = 0;
            format((char*)(this->comboBoxDevice->currentText().toStdString().c_str()));
            while(this->progressBarStatus->value() != 100)
            {
                this->progressBarStatus->setValue(count);
                count++;
                _sleep(30);
            }
            QDateTime dateTime = QDateTime::currentDateTimeUtc();
            QFile registerFile("./store/info/register.txt");
            registerFile.open(QFile::Append);
            QString registerString = "Device " + this->comboBoxDevice->currentText() + " was formatted to NTFS " + dateTime.toString("hh:mm dd/MM/yyyy") + "\n";
            registerFile.write(registerString.toUtf8());
            registerFile.close();
            if(this->progressBarStatus)
                delete this->progressBarStatus;
            this->widgetFont.setFamily("Good Times");
            this->labelReady = new QLabel("Ready", this);
            this->labelReady->setGeometry(15, this->HEIGHT - 90, this->WIDTH - 30, 30);
            this->labelReady->setFrameShape(QFrame::Box);
            this->labelReady->setAlignment(Qt::AlignCenter);
            this->labelReady->setFont(this->widgetFont);
            this->labelReady->setEnabled(true);
            this->labelReady->show();
        }
        if(reply == QMessageBox::No)
        {
            //
        }
    }
}

void MainWindow::handleBrowse()
{
    QString directoryBrowse = QFileDialog::getExistingDirectory(this, tr("Find USB Disk"), QDir::currentPath());
    if (!directoryBrowse.isEmpty())
    {
        if (this->comboBoxDevice->findText(directoryBrowse) == -1)
            this->comboBoxDevice->addItem(directoryBrowse);
        this->comboBoxDevice->setCurrentIndex(this->comboBoxDevice->findText(directoryBrowse));
    }
    if(this->comboBoxDevice->count())
    {
        if(!this->checkBoxFormatterNTFS->isHidden() && this->checkBoxSystem->isHidden())
        {
            this->comboBoxClusterSize->setEnabled(false);
            this->labelFileSystem->setEnabled(true);
            this->labelReady->setEnabled(false); //
            this->buttonStart->setEnabled(true);
        }
        if(this->checkBoxFormatterNTFS->isHidden() && !this->checkBoxSystem->isHidden())
        {
            this->comboBoxClusterSize->setEnabled(true);
            this->labelFileSystem->setEnabled(true);
            this->labelReady->setEnabled(false); //
            this->buttonStart->setEnabled(true);
        }
    }
}

void MainWindow::handleInformation()
{
   this->informationWindow = new InformationWindow();
   this->informationWindow->show();
}

void MainWindow::handleLicense()
{
    this->licenseWindow = new LicenseWindow();
    this->licenseWindow->show();
}

void MainWindow::handleRegister()
{
    this->registerWindow = new RegisterWindow();
    this->registerWindow->show();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mainIcon = new QIcon("./store/icons/mainIcon.ico");
    this->setWindowTitle("FormatterNTFS");
    this->setBaseSize(this->WIDTH, this->HEIGHT);
    this->setMaximumSize(this->WIDTH, this->HEIGHT);
    this->setMinimumSize(this->WIDTH, this->HEIGHT);
    this->setWindowIcon(*this->mainIcon);

    QFile styleFileMainWindow(":/styleMainWindow.css");
    styleFileMainWindow.open(QFile::ReadOnly);
    this->setStyleSheet(styleFileMainWindow.readAll());

    this->createWidgets();
}

MainWindow::~MainWindow()
{
    delete this->horizontalLineDiscProperties;
    delete this->labelDiscProperties;
    delete this->buttonBrowse;
    delete this->comboBoxDevice;
    delete this->horizontalLineFormattingOptions;
    delete this->labelFormattingOptions;
    delete this->labelNewDeviceName;
    delete this->lineEditNewDeviceName;
    delete this->labelClusterSizeText;
    delete this->labelFileSystemText;
    delete this->comboBoxClusterSize;
    delete this->labelFileSystem;
    delete this->horizontalLineStatus;
    delete this->labelStatus;
    if(this->labelReady)
        delete this->labelReady;
    if(this->progressBarStatus)
        delete this->progressBarStatus;
    delete this->buttonClose;
    delete this->buttonStart;
    delete this->buttonInformation;
    delete this->buttonLicense;
    delete this->buttonRegister;

    delete this->checkBoxSystem;
    delete this->checkBoxFormatterNTFS;

    delete this->mainIcon;
    delete this->licenseIcon;
    delete this->informationIcon;
    delete this->registerIcon;

    delete this->informationWindow;
    delete this->licenseWindow;
    delete this->registerWindow;
    delete ui;
}

