#pragma once

#include "QAbstractEventDispatcher.hpp"
#include "QTimer.hpp"
#include <map>
#include <queue>

class QEventDispatcherUNIX : public QAbstractEventDispatcher {
public:
    explicit QEventDispatcherUNIX(QObject* parent = nullptr);

    void registerTimer(QTimer* timer) override;
    void unregisterTimer(QTimer* timer) override;

    void registerSocketNotifier(QSocketNotifier* notifier) override;
    void unregisterSocketNotifier(int fd) override;

    void postEvent(QObject *receiver, QEvent* event) override;

    void processEvents() override;
    void interrupt() override;

private:
    std::map<QTimer::timerid_t, QTimer*> m_timers;
    std::map<int, QSocketNotifier*> m_socketNotifiers;
    std::queue<QEvent*> m_eventQueue;
    bool m_interrupted;
    static QEventDispatcherUNIX *m_instance;
};