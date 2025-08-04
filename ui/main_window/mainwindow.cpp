//
// Created by User on 30.07.2025.
//

#include "mainwindow.h"

#include "configtab.h"
#include "pipestab.h"
#include "ui_MainWindow.h"

namespace UI {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->ui->tabWidget->addTab(new ConfigTab(this), tr("Settings"));
    this->ui->tabWidget->addTab(new PipesTab(this), tr("Pipes"));
}

MainWindow::~MainWindow() {
    delete ui;
}
} // UI
