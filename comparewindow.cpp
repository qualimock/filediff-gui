#include "comparewindow.h"
#include "ui_comparewindow.h"

CompareWindow::CompareWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CompareWindow)
{
    ui->setupUi(this);

    connect(ui->comboBox, SIGNAL(activated(const QString&)), this, SLOT(onComboBoxItemSelected(const QString&)));
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

void CompareWindow::onComboBoxItemSelected(const QString& item) {
    QPair<QString, QString> diff;
    QPair<QString, QString> path = m_filesMap.value(item);

    Borders aroundChunk = createBorders(ui->spinBox->value(), ui->spinBox->value());

    QVector<QString> diff1;
    QVector<QString> diff2;

    for (auto borders : m_bordersMap.value(item)) {
        diff1.push_back(getFileChunk(fs::path((path.first + item).toStdString()), &aroundChunk, &borders).c_str());
        diff2.push_back(getFileChunk(fs::path((path.second + item).toStdString()), &aroundChunk, &borders).c_str());
    }

    auto chunk1 = diff1.begin();
    for (auto chunk2 : diff2) {
        diff.first.append(chunk1);
        diff.second.append(chunk2);

        if (chunk1 != diff1.end())
            chunk1++;
    }

    m_diff = diff;
    m_diffHex = QPair(diff.first.toUtf8().toHex(' '), diff.second.toUtf8().toHex(' '));
}
