#include "UdevHelper.h"


ActionReply UdevHelper::writeudevrulefile(const QVariantMap &args)
{
    ActionReply reply;
    QString filename = args["filename"].toString();
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite)) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(file.errorString());
        return reply;
    }
    QTextStream stream(&file);
    QString contents;
    stream >> contents;
    reply.addData("contents", contents);
    return reply;
}

ActionReply UdevHelper::reloadudevrules(const QVariantMap &args)
{
    ActionReply reply;
    
    return reply;
}

KAUTH_HELPER_MAIN("kcm.webcam_settings.udevhelper", UdevHelper)

#include "UdevHelper.moc"