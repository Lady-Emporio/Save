#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
QWidget *window = new QWidget;
this->setCentralWidget(window);
mainLayout =new QVBoxLayout(this);
QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
buttom_P= new QPushButton("P");
buttom_X= new QPushButton("X");
buttom_P->setSizePolicy(sizePolicy);
buttom_X->setSizePolicy(sizePolicy);
QLineEdit *testPole=new QLineEdit;
mainLayout->addWidget(buttom_P);
mainLayout->addWidget(buttom_X);
mainLayout->addWidget(testPole);
window->setLayout(mainLayout);
connect(buttom_P, SIGNAL(clicked()), this, SLOT(slotButton()));
connect(buttom_X, SIGNAL(clicked()), this, SLOT(slotButton()));
}
void MainWindow::slotButton(){
QObject* obj = sender();
QDate dateToday = QDate::currentDate();
if (obj==buttom_P){
    QString now=dateToday.toString("Р dd.MM.yy Л2");
    buttom_P->setText(now);
    QClipboard* c = QApplication::clipboard();
    c->setText( now );
    buttom_X->setText("X");
}
else if (obj==buttom_X){
    QString now=dateToday.toString("X dd.MM.yy Л2");
    buttom_X->setText(now);
    QClipboard* c = QApplication::clipboard();
    c->setText( now );
    buttom_P->setText("P");
}
}
