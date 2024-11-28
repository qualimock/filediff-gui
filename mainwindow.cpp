#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fileButton1, &QPushButton::pressed, this, [=](){ loadDirectory(ui->fileInput1->text()); });
    connect(ui->fileButton2, &QPushButton::pressed, this, [=](){ loadDirectory(ui->fileInput2->text()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDirectory(const QString& path) {
    bool loaded = false;

    ui->textBrowser->clear();

    ui->statusbar->showMessage("Loading directory " + path);

    if (path.isEmpty()) {
        loaded = dir1.load();
    }
    else {
        loaded = dir1.load(path.toStdString());
    }

    if (!loaded) {
        ui->textBrowser->setText("Cannot load directory " + path);
        ui->statusbar->showMessage("Cannot load directory " + path);
        return;
    }

    QString _path = QString(dir1.path().c_str());

    QString files;

    for (auto file : dir1.files()) {
        files.append(_path + QString(file.first.c_str()));
        files.append("\n");
    }

    ui->textBrowser->setText(files);

    ui->statusbar->showMessage("Loaded directory " + _path);
    ui->infoLabel->setText("Total files: " + QString::number(dir1.files().size()));

    ui->compareButton->setEnabled(!(dir1.files().empty() || dir2.files().empty()) && dir1.path() != dir2.path());
}
