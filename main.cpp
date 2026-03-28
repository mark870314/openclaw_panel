#include "widget.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QLocale locale = QLocale::system();
    QString language = locale.name();
    QTranslator translator;
    if(!translator.load(QString(":/translations/OpenClaw_%1.qm").arg(language))){
        translator.load(QString(":/translations/OpenClaw_en_US.qm"));
    }
    QApplication a(argc, argv);
    a.installTranslator(&translator);
    Widget w;
    w.show();
    return a.exec();
}
