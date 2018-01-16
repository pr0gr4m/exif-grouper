#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QStringList>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnOpen_clicked();

    void on_btnApply_clicked();

    void on_btnDetail_clicked();

private:
    void displayList();

private:
    Ui::MainWindow *ui;
    QStringList imgFiles;
};

#endif // MAINWINDOW_HH
