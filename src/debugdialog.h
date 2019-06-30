#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_debugdialog.h"

namespace Ui {
class DebugDialog;
}

class DebugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DebugDialog(QWidget *parent = nullptr);
    ~DebugDialog();

    static void showDebug(MainWindow* main);
    static void setupDialog(MainWindow* main, QDialog* d, Ui_DebugDialog* req);
private:
    Ui::DebugDialog *ui;
};

#endif // DEBUGDIALOG_H
