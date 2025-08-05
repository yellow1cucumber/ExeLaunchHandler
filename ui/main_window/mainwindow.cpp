//
// Created by User on 30.07.2025.
//

#include "mainwindow.h"

#include "configtab.h"
#include "ui_MainWindow.h"

namespace UI {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->ui->tabWidget->addTab(new ConfigTab(this), tr("Settings"));
}

MainWindow::~MainWindow() {
    delete ui;
}
} // UI
