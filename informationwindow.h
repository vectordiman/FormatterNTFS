#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

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
#include <QTextEdit>
#include <QScrollArea>
#include <QScrollBar>

namespace Ui {
class InformationWindow;
}

class InformationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformationWindow(QWidget *parent = nullptr);
    ~InformationWindow();

private:

    int WIDTH = 480;
    int HEIGHT = 445;

    QLabel* labelInformation = nullptr;

    QPushButton* buttonOK;

    QTextEdit* textEditInformation = nullptr;
    QScrollBar* verticalScrollBar = nullptr;

    QFont informationFont;
    QIcon* informationIcon = nullptr;
    Ui::InformationWindow *ui;

private slots:
    void createInformationWidgets();
    void handleInformationOK();
    void readInformation();
};

#endif // INFORMATIONWINDOW_H
