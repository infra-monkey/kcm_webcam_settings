#include "UdevHelper.h"


ActionReply UdevHelper::applyudevrules(const QVariantMap &args)
{
    ActionReply reply;
    QString filename = args["filename"].toString();
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(file.errorString());
        return reply;
    }
    QTextStream stream(&file);
    stream << args["contents"].toString() << Qt::endl;
    reply.addData("contents", args["contents"].toString());
    return reply;
}


KAUTH_HELPER_MAIN("kcm.webcam.settings.udevhelper", UdevHelper)

#include "UdevHelper.moc"