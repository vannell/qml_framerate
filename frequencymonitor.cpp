#include "frequencymonitor.h"
#include <QQuickWindow>

FrequencyMonitor::FrequencyMonitor(QQuickItem *parent) :
    QQuickItem(parent),
    m_counter(0),
    m_refreshFrequency(1000)
{
    connect(this, &FrequencyMonitor::windowChanged, this, &FrequencyMonitor::handleWindowChanged);
}

int FrequencyMonitor::fps() const
{
    return m_fps;
}

void FrequencyMonitor::setFps(int fps)
{
    if (m_fps == fps)
        return;

    m_fps = fps;
    emit fpsChanged();
}

int FrequencyMonitor::refreshFrequency() const
{
    return m_refreshFrequency;
}

void FrequencyMonitor::setRefreshFrequency(int msec)
{
    if (m_refreshFrequency == msec)
        return;

    m_refreshFrequency = msec;
    emit refreshFrequencyChanged();
}

void FrequencyMonitor::handleAfterRendering()
{
    const int elapsedMsec = m_time.elapsed();

    m_counter++;

    if (elapsedMsec >= m_refreshFrequency)
    {
        setFps(m_counter / (elapsedMsec / 1000.0));

        m_counter = 0;
        m_time.restart();
    }
}

void FrequencyMonitor::handleWindowChanged(QQuickWindow *window)
{
    if (m_windowConnection)
        this->disconnect(m_windowConnection);

    if (window)
    {
        m_time.restart();
        m_windowConnection = connect(window, &QQuickWindow::afterRendering, this, &FrequencyMonitor::handleAfterRendering);
    }
}
