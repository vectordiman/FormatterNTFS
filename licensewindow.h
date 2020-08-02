#ifndef LICENSEWINDOW_H
#define LICENSEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QFont>
#include <QFrame>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QScrollArea>
#include <QTextEdit>
#include <QScrollBar>

namespace Ui {
class LicenseWindow;
}

class LicenseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LicenseWindow(QWidget *parent = nullptr);
    ~LicenseWindow();

private:

    int WIDTH = 480;
    int HEIGHT = 545;

    QLabel* labelName = nullptr;
    QLabel* labelVersion = nullptr;
    QLabel* labelCopyright = nullptr;
    QLabel* labelSiteOne = nullptr;
    QLabel* labelTellError = nullptr;
    QLabel* labelSiteTwo = nullptr;
    QLabel* labelLicense = nullptr;

    QPushButton* buttonOK = nullptr;

    QTextEdit* textEditLicense = nullptr;
    QScrollBar* verticalScrollBar = nullptr;

    QFont licenseFont;
    QIcon* licenseIcon = nullptr;

    Ui::LicenseWindow *ui;

private slots:
    void createLicenseWidgets();
    void handleLicenseOK();
};

#endif // LICENSEWINDOW_H
