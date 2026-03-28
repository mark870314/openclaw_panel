QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    webview.cpp \
    widget.cpp

HEADERS += \
    webview.h \
    widget.h

FORMS += \
    widget.ui
macx{
    ICON = resources/icon.icns
}
QMAKE_CXXFLAGS += -Wno-implicit-function-declaration
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    OpenClaw_en_US.ts \
    OpenClaw_zh_CN.ts

DISTFILES +=
