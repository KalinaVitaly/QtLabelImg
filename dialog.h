#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "workwithfiles.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void SearchButtonClicked();
    void ItemClicked(QListWidgetItem *);
private:
    Ui::Dialog *ui;

    QString path;
};

#endif // DIALOG_H
