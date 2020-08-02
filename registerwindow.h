#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

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
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private:

    int WIDTH = 480;
    int HEIGHT = 445;

    QLabel* labelRegister = nullptr;

    QPushButton* buttonOK;

    QTextEdit* textEditInformation = nullptr;
    QScrollBar* verticalScrollBar = nullptr;

    QFont registerFont;
    QIcon* registerIcon = nullptr;
    Ui::RegisterWindow *ui;

private slots:
    void createRegisterWidgets();
    void handleRegisterOK();
};

#endif // REGISTERWINDOW_H
