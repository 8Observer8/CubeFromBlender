#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "FileOpenError.h"
#include "FileReadError.h"

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
    void on_actionLoad_triggered();
    void on_actionExit_triggered();

private:
    void readData( const QString &fileName, QString &all )
    throw (FileOpenError, FileReadError);

private:
    Ui::MainWindow *ui;
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
