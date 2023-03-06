#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_heading_valueChanged(int arg1);

    void on_bearing_valueChanged(int arg1);

    void on_showHeading_stateChanged(int arg1);

    void on_showBearing_stateChanged(int arg1);

    void on_range_valueChanged(int arg1);

    void on_borderColor_clicked();

    void on_lineColor_clicked();

    void on_backgroundColor_clicked();

    void on_textColor_clicked();

    void on_bearingColor_clicked();

    void on_headingColor_clicked();

    void on_indicatorColor_clicked();

    void on_opacitySpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QColorDialog mColorDialog;
};
#endif // MAINWINDOW_H
