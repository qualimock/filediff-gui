#include "comparewindow.h"
#include "ui_comparewindow.h"

CompareWindow::CompareWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CompareWindow)
{
    ui->setupUi(this);
}

CompareWindow::~CompareWindow()
{
    delete ui;
}
