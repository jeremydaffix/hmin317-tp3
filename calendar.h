#ifndef CALENDAR_H
#define CALENDAR_H

#include <QBasicTimer>
#include <QObject>
#include <QDebug>

#include <mainwidget.h>

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(MainWidget *w1, MainWidget *w2, MainWidget *w3, MainWidget *w4, QObject *parent = nullptr);

signals:

public slots:

protected:

    QBasicTimer timerSeason;
    void timerEvent(QTimerEvent *e) override;
    int currentDay = 0;

    MainWidget *widget1, *widget2, *widget3, *widget4;

};

#endif // CALENDAR_H
