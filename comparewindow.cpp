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

void CompareWindow::setDiffData(const QMap<QString, QVector<Borders>>& bordersMap,
                                const QMap<QString, QPair<QString, QString>>& filesMap) {
    m_bordersMap = bordersMap;
    m_filesMap = filesMap;

    for (auto file : filesMap.keys()) {
        ui->comboBox->addItem(file);
    }
}
