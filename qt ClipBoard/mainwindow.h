#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QDateTime>
#include <QClipboard>
#include <QLineEdit>
#include <QApplication>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVBoxLayout *mainLayout;
    QPushButton *buttom_X;
    QPushButton *buttom_P;
    explicit MainWindow(QWidget *parent = 0);
    //~MainWindow();
private slots:
    void slotButton();
};

#endif // MAINWINDOW_H
