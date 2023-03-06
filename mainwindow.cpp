#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->heading->setValue(ui->compass->heading());
  ui->bearing->setValue(ui->compass->bearing());
  ui->range->setValue(ui->compass->range());

  ui->showBearing->setCheckState(ui->compass->showBearing()
                                     ? Qt::CheckState::Checked
                                     : Qt::CheckState::Unchecked);

  ui->showHeading->setCheckState(ui->compass->showHeading()
                                     ? Qt::CheckState::Checked
                                     : Qt::CheckState::Unchecked);

  mColorDialog.setModal(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_heading_valueChanged(int arg1) {
  ui->compass->setHeading(arg1);
}

void MainWindow::on_bearing_valueChanged(int arg1) {
  ui->compass->setBearing(arg1);
}

void MainWindow::on_showHeading_stateChanged(int arg1) {
  ui->compass->setShowHeading(arg1);
}

void MainWindow::on_showBearing_stateChanged(int arg1) {
  ui->compass->setShowBearing(arg1);
}

void MainWindow::on_range_valueChanged(int arg1) {
  ui->compass->setRange(arg1);
}

void MainWindow::on_borderColor_clicked() {
    mColorDialog.setCurrentColor(ui->compass->borderColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setBorderColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}

void MainWindow::on_lineColor_clicked()
{
    mColorDialog.setCurrentColor(ui->compass->lineColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setLineColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_backgroundColor_clicked()
{
    mColorDialog.setCurrentColor(ui->compass->backgroundColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setBackgroundColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_textColor_clicked()
{
    mColorDialog.setCurrentColor(ui->compass->textColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setTextColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_bearingColor_clicked()
{
    mColorDialog.setCurrentColor(ui->compass->bearingColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setBearingColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_headingColor_clicked()
{
    mColorDialog.setCurrentColor(ui->compass->headingColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setHeadingColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}


void MainWindow::on_indicatorColor_clicked()
{
    mColorDialog.setCurrentColor(ui->compass->indicatorColor());

    auto conn = std::make_shared<QMetaObject::Connection>();

    *conn = connect(&mColorDialog, &QColorDialog::colorSelected, this,
                    [this, conn]() {
                      ui->compass->setIndicatorColor(mColorDialog.currentColor());
                      disconnect(*conn);
                    });

    mColorDialog.show();
}

