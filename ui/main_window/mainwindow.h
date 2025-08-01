//
// Created by User on 30.07.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../export.h"
#include <QMainWindow>

namespace UI {
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class EXELAUNCHHANDLER_UI_API MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};
} // UI

#endif //MAINWINDOW_H
