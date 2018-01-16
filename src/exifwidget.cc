#include "exifwidget.hh"
#include "ui_exifwidget.h"
#include "exif.hh"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ExifWidget::ExifWidget(std::vector<MetaData> &metaVector, int group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExifWidget)
{
    ui->setupUi(this);

    for (int i = 0; i < metaVector.size(); i++) {

        if (metaVector[i].group() != group)
            continue;

        ifstream inFile(metaVector[i].fileName(), ios::binary | ios::ate);
        ifstream::pos_type pos = inFile.tellg();

        int length = pos;
        unsigned char *buf = new unsigned char[length];
        inFile.seekg(0, ios::beg);
        inFile.read((char*)buf, length);

        easyexif::EXIFInfo result;
        int code = result.parseFrom(buf, length);
        delete[] buf;
        inFile.close();

        ui->textBrowser->append(QString::fromStdString(string("File Name : " + metaVector[i].fileName() + "\n")));
        if (code) {
            ui->textBrowser->append(QString("Error parsing EXIF"));
        } else {
            ui->textBrowser->append(QString::fromStdString(string("Camera vendor : ") + result.Make));
            ui->textBrowser->append(QString::fromStdString(string("Camera model : ") + result.Model));
            ui->textBrowser->append(QString::fromStdString(string("Software : ") + result.Software));
            ui->textBrowser->append(QString::fromStdString(string("Bits per sample : ") + to_string(result.BitsPerSample)));
            ui->textBrowser->append(QString::fromStdString(string("Image Width : ") + to_string(result.ImageWidth)));
            ui->textBrowser->append(QString::fromStdString(string("Image Height : ") + to_string(result.ImageHeight)));
            ui->textBrowser->append(QString::fromStdString(string("Image Description : ") + result.ImageDescription));
            ui->textBrowser->append(QString::fromStdString(string("Image Height : ") + to_string(result.Orientation)));
            ui->textBrowser->append(QString::fromStdString(string("Image Copyright : ") + result.Copyright));
            ui->textBrowser->append(QString::fromStdString(string("Image Date/Time : ") + result.DateTime));
            ui->textBrowser->append(QString::fromStdString(string("Original Date/Time : ") + result.DateTimeOriginal));
            ui->textBrowser->append(QString::fromStdString(string("Digitize Date/Time : ") + result.DateTimeDigitized));
            ui->textBrowser->append(QString::fromStdString(string("Subsecond Time : ") + result.SubSecTimeOriginal));
            ui->textBrowser->append(QString::fromStdString(string("Exposure Time : ") + to_string(result.ExposureTime)));
            ui->textBrowser->append(QString::fromStdString(string("Exposure Program : ") + to_string(result.ExposureProgram)));
            ui->textBrowser->append(QString::fromStdString(string("Subject Distance : ") + to_string(result.SubjectDistance)));
            ui->textBrowser->append(QString::fromStdString(string("ISO Speed : ") + to_string(result.ISOSpeedRatings)));
            ui->textBrowser->append(QString::fromStdString(string("Flash Used : ") + to_string(result.Flash)));
            ui->textBrowser->append(QString::fromStdString(string("Flash Mode : ") + to_string(result.FlashMode)));
            ui->textBrowser->append(QString::fromStdString(string("GPS Latitude : ") + to_string(result.GeoLocation.Latitude)));
            ui->textBrowser->append(QString::fromStdString(string("GPS Longtitude : ") + to_string(result.GeoLocation.Longitude)));
            ui->textBrowser->append(QString::fromStdString(string("GPS Altitude : ") + to_string(result.GeoLocation.Altitude)));
            ui->textBrowser->append(QString::fromStdString(string("GPS Precision : ") + to_string(result.GeoLocation.DOP)));
            ui->textBrowser->append(QString::fromStdString(string("Lens Focal Length : ") + to_string(result.FocalLength)));
            ui->textBrowser->append(QString::fromStdString(string("35mm Focal Length : ") + to_string(result.FocalLengthIn35mm)));
            ui->textBrowser->append(QString::fromStdString(string("Lens vendor : ") + result.LensInfo.Make));
            ui->textBrowser->append(QString::fromStdString(string("Lens model : ") + result.LensInfo.Model));
            ui->textBrowser->append(QString::fromStdString(string("Focal plane XRes : ") + to_string(result.LensInfo.FocalPlaneXResolution)));
            ui->textBrowser->append(QString::fromStdString(string("Focal plane YRes : ") + to_string(result.LensInfo.FocalPlaneYResolution)));
        }
        ui->textBrowser->append(QString("===================================================="));
        ui->textBrowser->append(QString("\n"));
    }
}

ExifWidget::~ExifWidget()
{
    delete ui;
}
