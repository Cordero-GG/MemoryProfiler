#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QHash>
#include <QPair>

struct QtMemoryInfo {
    qint64 size;
    QDateTime timestamp;
    QString file;
    int line;
};

struct QtMetrics {
    qint64 currentMemory;
    qint64 activeAllocations;
    qint64 totalAllocations;
    qint64 maxMemoryUsed;
};

struct QtFileSummary {
    QPair<qint64, qint64> countAndSize;  // count of allocations, total size
};

using QtMemoryMap = QHash<quintptr, QtMemoryInfo>;
using QtFileSummaryMap = QHash<QString, QtFileSummary>;
