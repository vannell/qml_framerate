#include "frequencymonitor.h"
#include <QQuickWindow>

FrequencyMonitor::FrequencyMonitor(QQuickItem *parent) :
    QQuickItem(parent),
    m_counter(0),
    m_refreshPeriod(1000)
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

int FrequencyMonitor::refreshPeriod() const
{
    return m_refreshPeriod;
}

void FrequencyMonitor::setRefreshPeriod(int msec)
{
    if (m_refreshPeriod == msec)
        return;

    m_refreshPeriod = msec;
    emit refreshPeriodChanged();
}

void FrequencyMonitor::handleAfterRendering()
{
    const int elapsedMsec = m_time.elapsed();

    m_counter++;

    if (elapsedMsec >= m_refreshPeriod)
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
