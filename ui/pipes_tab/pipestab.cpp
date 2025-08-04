//
// Created by User on 05.08.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PipesTab.h" resolved

#include "pipestab.h"
#include "ui_PipesTab.h"

namespace UI {
PipesTab::PipesTab(QWidget *parent) :
    QWidget(parent), ui(new Ui::PipesTab) {
    ui->setupUi(this);
}

PipesTab::~PipesTab() {
    delete ui;
}
} // UI
