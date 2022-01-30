#ifndef UDEVHELPER_H
#define UDEVHELPER_H
#undef QT_NO_CAST_FROM_ASCII

#include <KAuth>
#include <QString>
#include <QFile>
#include <QTextStream>

using namespace KAuth;

class UdevHelper : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    ActionReply writeudevrulefile(const QVariantMap &args);
    ActionReply reloadudevrules(const QVariantMap &args);
};

#endif