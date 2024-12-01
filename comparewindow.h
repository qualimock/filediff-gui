#ifndef COMPAREWINDOW_H
#define COMPAREWINDOW_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVector>

#include <filediff.h>

namespace Ui {
class CompareWindow;
}

class CompareWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CompareWindow(QWidget *parent = nullptr);
    ~CompareWindow();

    void setDiffData(const QMap<QString, QVector<Borders>>& bordersMap,
                     const QMap<QString, QPair<QString, QString>>& filesMap);

private slots:
    void onComboBoxItemSelected(const QString& item);

private:
    Ui::CompareWindow *ui;

    QPair<QString, QString> m_diff;
    QPair<QString, QString> m_diffHex;

    QMap<QString, QVector<Borders>> m_bordersMap;
    QMap<QString, QPair<QString, QString>> m_filesMap;
};

#endif // COMPAREWINDOW_H
