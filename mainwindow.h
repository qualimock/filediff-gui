#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <filediff.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadDirectory(const QString& path);

private:
    Directory dir1;
    Directory dir2;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
