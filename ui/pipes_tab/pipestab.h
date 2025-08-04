//
// Created by User on 05.08.2025.
//

#ifndef PIPESTAB_H
#define PIPESTAB_H

#include <QWidget>

namespace UI {
QT_BEGIN_NAMESPACE
namespace Ui { class PipesTab; }
QT_END_NAMESPACE

class PipesTab : public QWidget {
Q_OBJECT

public:
    explicit PipesTab(QWidget *parent = nullptr);
    ~PipesTab() override;

private:
    Ui::PipesTab *ui;
};
} // UI

#endif //PIPESTAB_H
