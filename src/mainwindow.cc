#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "exifwidget.hh"
#include "metadata.hh"

#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

extern bool compSoftware(const MetaData& a, const MetaData& b);
extern bool compSize(const MetaData& a, const MetaData& b);
extern bool compDate(const MetaData& a, const MetaData& b);
extern bool compISO(const MetaData& a, const MetaData& b);
extern bool compExpo(const MetaData& a, const MetaData& b);
extern bool compAltitude(const MetaData& a, const MetaData& b);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    openFlag(false),
    groupFlag(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->listFiles->addItems(imgFiles);

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

        MetaData m(it->toStdString(), result);
        metaVector.push_back(m);
    }

    openFlag = true;
}

void MainWindow::on_btnApply_clicked()
{
    if (!openFlag)
        return;

    ui->listFiles->clear();
    MetaData::groupCounter = 1;

    unsigned int flag = 0;
    if (ui->checkSoftware->isChecked()) {
        flag |= MetaData::SOFTWARE;
        stable_sort(metaVector.begin(), metaVector.end(), compSoftware);
    }
    if (ui->checkSize->isChecked()) {
        flag |= MetaData::SIZE;
        stable_sort(metaVector.begin(), metaVector.end(), compSize);
    }
    if (ui->checkDate->isChecked()) {
        flag |= MetaData::DATE;
        stable_sort(metaVector.begin(), metaVector.end(), compDate);
    }
    if (ui->checkISO->isChecked()) {
        flag |= MetaData::ISO;
        stable_sort(metaVector.begin(), metaVector.end(), compISO);
    }
    if (ui->checkExpo->isChecked()) {
        flag |= MetaData::EXPO;
        stable_sort(metaVector.begin(), metaVector.end(), compExpo);
    }
    if (ui->checkAltitude->isChecked()) {
        flag |= MetaData::ALTITUDE;
        stable_sort(metaVector.begin(), metaVector.end(), compAltitude);
    }

    int i;
    for (i = 0; i < metaVector.size() - 1; i++) {
        metaVector[i].group(MetaData::groupCounter);
        if (!(metaVector[i].isEqual(metaVector[i + 1], flag))) {
            // new group
            MetaData::groupCounter++;
        }
    }
    metaVector[i].group(MetaData::groupCounter);

    std::vector<int> tmp(MetaData::groupCounter + 1, 0);
    for (int i = 0; i < metaVector.size(); i++) {
        tmp[metaVector[i].group()] += 1;
    }
    std::vector<int>::iterator maxIt = max_element(tmp.begin(), tmp.end());

    for (int i = 1; i <= MetaData::groupCounter; i++) {
        ui->listFiles->addItem(QString::fromStdString(string("Group ") + to_string(i)));
    }

    groupFlag = true;

    QMessageBox *maxMessage = new QMessageBox();
    maxMessage->setText(QString::fromStdString(string("Largest - Group ")
                                              + to_string( distance(tmp.begin(), maxIt) )
                                              + " : #"
                                              + to_string(*maxIt)));
    maxMessage->show();
}

void MainWindow::on_btnDetail_clicked()
{
    if (!openFlag || !groupFlag)
        return;

    QList<QListWidgetItem*> list = ui->listFiles->selectedItems();
    if (list.begin() == list.end())
        return;
    QString str = (*(list.begin()))->text();
    string grpStr = str.toStdString();
    ExifWidget *newWidget = new ExifWidget(metaVector, grpStr.at(6) - '0');

    newWidget->show();
}
