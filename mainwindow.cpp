#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMap>
#include <QVector>

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

    connect(ui->diffButton, &QPushButton::pressed, &compareWindow, &QWidget::show);
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
        files.append('\n');
    }

    ui->textBrowser->setText(files);

    ui->statusbar->showMessage("Loaded directory " + _path);
    ui->infoLabel->setText("Total files: " + QString::number(dir.files().size()));

    ui->compareButton->setEnabled(!(dir1.files().empty() || dir2.files().empty()) && dir1.path() != dir2.path());
}

void MainWindow::onCompareButtonPress() {
    auto commonFiles = dir1.compare(dir2);

    //   filename         borders
    QMap<QString, QVector<Borders>> bordersMap;

    //   filename        path1    path2
    QMap<QString, QPair<QString, QString>> filesMap;

    for (auto file : commonFiles) {
        fs::path file1 = dir1.path().generic_string() + file.first.generic_string();
        fs::path file2 = dir2.path().generic_string() + file.first.generic_string();

        ui->statusbar->showMessage("Comparing" + QString(file1.c_str()) + " and " + QString(file2.c_str()));

        auto stddiff = compareFiles(file1, file2);

        bordersMap.insert(file.first.c_str(), QVector<Borders>(stddiff.begin(), stddiff.end()));
        filesMap.insert(file.first.c_str(), QPair(dir1.path().c_str(), dir2.path().c_str()));
    }

    QString filesToShow;

    for (auto filename : filesMap.keys()) {
        filesToShow.append(filesMap.value(filename).first + filename);
        filesToShow.append("    -->    ");
        filesToShow.append(filesMap.value(filename).second + filename);
        filesToShow.append('\n');
    }

    if (!bordersMap.empty()) {
        compareWindow.setDiffData(bordersMap, filesMap);
        ui->textBrowser->setText(filesToShow);
        ui->infoLabel->setText("Files that differ: " + QString::number(bordersMap.size()));
        ui->statusbar->showMessage("Done");
        return;
    }

    ui->statusbar->showMessage("Directories do not differ");
}
