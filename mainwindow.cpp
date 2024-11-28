#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fileInput1->setText("Select a directory");
    ui->fileInput2->setText("Select a directory");

    connect(ui->browseButton1, &QPushButton::pressed, this, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, tr("Pick Directory"),
                                                        "/",
                                                        QFileDialog::ShowDirsOnly |
                                                        QFileDialog::DontResolveSymlinks);
        ui->fileInput1->setText(dir);
        onBrowseButtonPress(dir, dir1);
    });

    connect(ui->browseButton2, &QPushButton::pressed, this, [=](){
        QString dir = QFileDialog::getExistingDirectory(this, tr("Pick Directory"),
                                                        "/",
                                                        QFileDialog::ShowDirsOnly |
                                                        QFileDialog::DontResolveSymlinks);
        ui->fileInput2->setText(dir);
        onBrowseButtonPress(dir, dir2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBrowseButtonPress(const QString& path, Directory& dir) {
    bool loaded = false;

    ui->textBrowser->clear();

    ui->statusbar->showMessage("Loading directory " + path);

    if (path.isEmpty()) {
        loaded = dir.load();
    }
    else {
        loaded = dir.load(path.toStdString());
    }

    if (!loaded) {
        ui->textBrowser->setText("Cannot load directory " + path);
        ui->statusbar->showMessage("Cannot load directory " + path);
        return;
    }

    QString _path = QString(dir.path().c_str());

    QString files;

    for (auto file : dir.files()) {
        files.append(_path + QString(file.first.c_str()));
        files.append("\n");
    }

    ui->textBrowser->setText(files);

    ui->statusbar->showMessage("Loaded directory " + _path);
    ui->infoLabel->setText("Total files: " + QString::number(dir.files().size()));

    ui->compareButton->setEnabled(!(dir1.files().empty() || dir2.files().empty()) && dir1.path() != dir2.path());
}
