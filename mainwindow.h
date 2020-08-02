#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Windows.h>

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QCheckBox>
#include <QFont>
#include <QFrame>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDateTime>

#include <informationwindow.h>
#include <licensewindow.h>
#include <registerwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    int WIDTH = 450;
    int HEIGHT = 390;

    QPushButton* buttonStart = nullptr;
    QPushButton* buttonClose = nullptr;
    QPushButton* buttonBrowse = nullptr;
    QPushButton* buttonRegister = nullptr;
    QPushButton* buttonInformation = nullptr;
    QPushButton* buttonLicense = nullptr;

    QLabel* labelReady = nullptr;
    QProgressBar* progressBarStatus = nullptr;
    QFrame* horizontalLineStatus = nullptr;
    QFrame* horizontalLineFormattingOptions = nullptr;
    QFrame* horizontalLineDiscProperties = nullptr;

    QLabel* labelFileSystemText = nullptr;
    QLabel* labelFileSystem = nullptr;

    QLabel* labelClusterSizeText = nullptr;
    QComboBox* comboBoxClusterSize = nullptr;

    QLabel* labelNewDeviceName = nullptr;
    QLineEdit* lineEditNewDeviceName = nullptr;
    QLabel* labelDevice = nullptr;
    QComboBox* comboBoxDevice = nullptr;

    QLabel* labelFormattingOptions = nullptr;
    QLabel* labelDiscProperties = nullptr;
    QLabel* labelStatus = nullptr;

    QCheckBox* checkBoxSystem = nullptr;
    QCheckBox* checkBoxFormatterNTFS = nullptr;

    QIcon* mainIcon = nullptr;
    QIcon* licenseIcon = nullptr;
    QIcon* informationIcon = nullptr;
    QIcon* registerIcon = nullptr;
    QFont mainFont;
    QFont widgetFont;

    InformationWindow* informationWindow;
    LicenseWindow* licenseWindow;
    RegisterWindow* registerWindow;
    Ui::MainWindow *ui;

private slots:
    void createWidgets();
    void handleClose();
    void handleBrowse();
    void handleStart();
    void handleCheckSystem();
    void handleCheckFormatter();

    void handleInformation();
    void handleLicense();
    void handleRegister();
};
#endif // MAINWINDOW_H
