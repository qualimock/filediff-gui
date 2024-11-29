#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <filediff.h>

#include "comparewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBrowseButtonPress(const QString& path, Directory& dir);
    void onCompareButtonPress();

private:
    Directory dir1;
    Directory dir2;

    CompareWindow compareWindow;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
