#ifndef UDEVHELPER_H
#define UDEVHELPER_H

#include <KAuth>
#include <QString>
#include <QFile>
#include <QTextStream>

using namespace KAuth;

class UdevHelper : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    ActionReply applyudevrules(const QVariantMap &args);
};

#endif