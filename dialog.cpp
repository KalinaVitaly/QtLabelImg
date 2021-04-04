#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QStringListModel>
#include <photowidget.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

void Dialog::ItemClicked(QListWidgetItem *item)
{
    QPixmap pix(path + "/" + item->text());
    PhotoWidget *pw = new PhotoWidget();
    pw->setPathToPhoto(path + "/" + item->text());
    pw->show();
}

void Dialog::SearchButtonClicked()
{
    QStringList list;
    path = ui->PathEdit->text();
    list = WorkWithFiles::getDirictoryContent(path);
    ui->listWidget->addItems(list);
    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Dialog::~Dialog()
{
    delete ui;

}
