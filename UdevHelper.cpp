#include "UdevHelper.h"


ActionReply UdevHelper::applyudevrules(const QVariantMap &args)
{
    ActionReply reply;
    std::string cmd;
    QString filename = args["filename"].toString();
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        reply = ActionReply::HelperErrorReply();
        reply.setErrorDescription(file.errorString());
        return reply;
    }
    QTextStream stream(&file);
    for (const QString &rule : args["contents"].toStringList()) {
        if (rule.size()>0){
            stream << rule << Qt::endl;
        }
    }
    std::string("udevadm control --reload-rules");
    exec_cmd(cmd);
    return reply;
}


KAUTH_HELPER_MAIN("kcm.webcam.settings.udevhelper", UdevHelper)

#include "UdevHelper.moc"