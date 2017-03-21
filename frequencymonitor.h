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
    Q_PROPERTY(int refreshFrequency READ refreshFrequency WRITE setRefreshFrequency NOTIFY refreshFrequencyChanged)
public:
    explicit FrequencyMonitor(QQuickItem *parent = 0);

    int fps() const;
    void setFps(int fps);

    // by default refresh one time per 1000 msec
    int refreshFrequency() const;
    void setRefreshFrequency(int msec);

signals:
    void fpsChanged();
    void refreshFrequencyChanged();

public slots:
    void handleAfterRendering();
    void handleWindowChanged(QQuickWindow * window);

protected:
    QMetaObject::Connection m_windowConnection;
    QTime m_time;
    int m_fps;
    int m_counter;
    int m_refreshFrequency;

};

#endif // FREQUENCYMONITOR_H
