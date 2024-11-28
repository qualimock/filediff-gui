#ifndef COMPAREWINDOW_H
#define COMPAREWINDOW_H

#include <QWidget>

namespace Ui {
class CompareWindow;
}

class CompareWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CompareWindow(QWidget *parent = nullptr);
    ~CompareWindow();

private:
    Ui::CompareWindow *ui;
};

#endif // COMPAREWINDOW_H
