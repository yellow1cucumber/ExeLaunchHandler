//
// Created by User on 30.07.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "../config_managment_widget/configtab.h"

namespace UI {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->ui->tabWidget->addTab(new ConfigTab(this), tr("Конфигурация"));
}

MainWindow::~MainWindow() {
    delete ui;
}
} // UI
