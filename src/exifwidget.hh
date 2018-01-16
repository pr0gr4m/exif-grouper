#ifndef EXIFWIDGET_HH
#define EXIFWIDGET_HH

#include <QWidget>
#include <QStringList>
#include <vector>
#include "metadata.hh"

namespace Ui {
class ExifWidget;
}

class ExifWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExifWidget(std::vector<MetaData> &metaVector, int group, QWidget *parent = 0);
    ~ExifWidget();

private:
    Ui::ExifWidget *ui;
};

#endif // EXIFWIDGET_HH
