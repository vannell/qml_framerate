#ifndef FREQUENCYMONITOR_H
#define FREQUENCYMONITOR_H

#include <QQuickItem>
#include <QTime>
#include <QMetaObject>

class QQuickWindow;

class FrequencyMonitor : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)
    Q_PROPERTY(int refreshPeriod READ refreshPeriod WRITE setRefreshPeriod NOTIFY refreshPeriodChanged)
public:
    explicit FrequencyMonitor(QQuickItem *parent = 0);

    int fps() const;
    void setFps(int fps);

    // by default refresh one time per 1000 msec
    int refreshPeriod() const;
    void setRefreshPeriod(int msec);

signals:
    void fpsChanged();
    void refreshPeriodChanged();

public slots:
    void handleAfterRendering();
    void handleWindowChanged(QQuickWindow * window);

protected:
    QMetaObject::Connection m_windowConnection;
    QTime m_time;
    int m_fps;
    int m_counter;
    int m_refreshPeriod;

};

#endif // FREQUENCYMONITOR_H
