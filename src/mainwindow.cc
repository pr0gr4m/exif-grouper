#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "filter.hh"
#include "exifwidget.hh"

#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listFiles->setSelectionMode(QListWidget::MultiSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayList()
{
    ui->listFiles->clear();
    QStringList::iterator it;

    for (it = imgFiles.begin(); it != imgFiles.end(); it++) {
        // add Item with Filter
        ifstream inFile(it->toStdString(), ios::binary | ios::ate);
        ifstream::pos_type pos = inFile.tellg();

        int length = pos;
        unsigned char *buf = new unsigned char[length];
        inFile.seekg(0, ios::beg);
        inFile.read((char*)buf, length);

        easyexif::EXIFInfo result;
        int code = result.parseFrom(buf, length);
        delete[] buf;
        inFile.close();

        if (!code && !Filter::getInstance()->cmpFilter(result))
            continue;

        ui->listFiles->addItem(*it);
    }
}

void MainWindow::on_btnOpen_clicked()
{
    char buf[256];
    getcwd(buf, 256);
    QString curr{ buf };
    imgFiles = QFileDialog::getOpenFileNames(this,
                                  tr("Open Image"),
                                  curr,
                                  tr("Image Files (*.jpg)"));
    displayList();
}

void MainWindow::on_btnApply_clicked()
{
    if (!Filter::getInstance()->setFilter(
                ui->lineLatitudeMin->text().toStdString(),
                ui->lineLatitudeMax->text().toStdString(),
                ui->lineLongtitudeMin->text().toStdString(),
                ui->lineLongtitudeMax->text().toStdString(),
                ui->lineVedor->text().toStdString(),
                ui->lineModel->text().toStdString(),
                ui->lineWidthMin->text().toStdString(),
                ui->lineWidthMax->text().toStdString(),
                ui->lineHeightMin->text().toStdString(),
                ui->lineHeightMax->text().toStdString(),
                ui->lineDateMin->text().toStdString(),
                ui->lineDateMax->text().toStdString(),
                ui->lineTimeMin->text().toStdString(),
                ui->lineTimeMax->text().toStdString())) {
        // alert
        QMessageBox errorMessage;
        errorMessage.critical(0, "Filter Error", "Filter Format Error!");
        errorMessage.setFixedSize(500, 200);
    }
    displayList();
}

void MainWindow::on_btnDetail_clicked()
{
    QList<QListWidgetItem*> items = ui->listFiles->selectedItems();
    QList<QListWidgetItem*>::iterator it;
    QStringList list;
    for (it = items.begin(); it != items.end(); it++) {
        list << (*it)->text();
    }

    ExifWidget *newWidget = new ExifWidget(list);
    newWidget->show();
}
