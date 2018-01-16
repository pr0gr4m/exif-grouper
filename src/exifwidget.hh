#ifndef EXIFWIDGET_HH
#define EXIFWIDGET_HH

#include <QWidget>
#include <QStringList>

namespace Ui {
class ExifWidget;
}

class ExifWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExifWidget(QStringList fileList, QWidget *parent = 0);
    ~ExifWidget();

private:
    Ui::ExifWidget *ui;
};

#endif // EXIFWIDGET_HH
