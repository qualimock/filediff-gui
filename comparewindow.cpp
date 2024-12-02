#include "comparewindow.h"
#include "ui_comparewindow.h"

CompareWindow::CompareWindow(QWidget *parent)
    : QWidget(parent)
    , m_outputType(true)
    , ui(new Ui::CompareWindow)
{
    ui->setupUi(this);

    m_aroundChunk = createBorders(ui->spinBox->value(), ui->spinBox->value());

    connect(ui->comboBox, SIGNAL(textActivated(const QString&)), this, SLOT(onComboBoxItemSelected(const QString&)));
    connect(ui->submitButton, &QPushButton::pressed, this, &CompareWindow::onSubmitButtonPress);
    connect(ui->changeOutputButton, &QPushButton::pressed, this, &CompareWindow::onChangeOutputButtonPress);

    ui->diffBrowser1->setText("Select file");
    ui->diffBrowser2->setText("Select file");
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

    QVector<QString> diff1;
    QVector<QString> diff2;

    for (auto borders : m_bordersMap.value(item)) {
        diff1.push_back(QString::fromStdString(getFileChunk(fs::path((path.first + item).toStdString()), &m_aroundChunk, &borders)));
        diff2.push_back(QString::fromStdString(getFileChunk(fs::path((path.second + item).toStdString()), &m_aroundChunk, &borders)));
    }

    for (auto chunk1 = diff1.begin(), chunk2 = diff2.begin();
         chunk1 != diff1.end() || chunk2 != diff2.end();
         chunk1++, chunk2++)
    {
        m_diff.first.push_back(*chunk1);
        m_diff.second.append(*chunk2);
    }

    m_diff = diff;
    m_diffHex = QPair<QByteArray, QByteArray>(m_diff.first.toUtf8().toHex(' '), m_diff.second.toUtf8().toHex(' '));

    m_outputType = true;
    onChangeOutputButtonPress();
}

void CompareWindow::onSubmitButtonPress() {
    if (ui->spinBox->value() != m_aroundChunk.left) {
        m_aroundChunk = createBorders(ui->spinBox->value(), ui->spinBox->value());
        emit ui->comboBox->textActivated(ui->comboBox->currentText());
    }
}

void CompareWindow::onChangeOutputButtonPress() {
    if (m_outputType) {
        ui->changeOutputButton->setText("To Hex");

        ui->diffBrowser1->setText(m_diff.first);
        ui->diffBrowser2->setText(m_diff.second);
    }
    else {
        ui->changeOutputButton->setText("To Text");

        ui->diffBrowser1->setText(m_diffHex.first);
        ui->diffBrowser2->setText(m_diffHex.second);
    }

    m_outputType = !m_outputType;
}
