#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"

#include <QMainWindow>
#include <QGridLayout>

class GridMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridMainWidget(QWidget *parent = nullptr);

protected:

    QGridLayout* gridLayout;
    MainWidget *widget1, *widget10, *widget100, *widget1000;

signals:

public slots:
};

#endif // MAINWINDOW_H
