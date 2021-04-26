QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainwindow.cpp \
    CodeEditor.cpp \
    main.cpp \
    modelsetting.cpp \
    showview.cpp \
    src/data/rule/action.cpp \
    src/data/cell.cpp \
    src/data/map.cpp \
    src/data/model.cpp \
    src/controller.cpp \
    src/data/rule/fireaction.cpp \
    src/data/rule/isolationaction.cpp \
    src/data/rule/sandaction.cpp \
    src/data/rule/voteaction.cpp \
    src/data/rule/wlaction.cpp \
    src/tool/expanalysis.cpp

HEADERS += \
    mainwindow.h \
    CodeEditor.h \
    modelsetting.h \
    showview.h \
    src/data/rule/action.h \
    src/data/cell.h \
    src/data/map.h \
    src/data/model.h \
    src/controller.h \
    src/data/rule/fireaction.h \
    src/data/rule/isolationaction.h \
    src/data/rule/sandaction.h \
    src/data/rule/voteaction.h \
    src/data/rule/wlaction.h \
    src/tool/expanalysis.h

FORMS += \
    CodeEditor.ui \
    mainwindow.ui \
    modelsetting.ui

TRANSLATIONS += \
    SimulationGroupDesktop_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
