QT += quick sql
QTPLUGIN += qsqlite
CONFIG += c++17

INCLUDEPATH += ./../../../boost/boost_1_72_0/
INCLUDEPATH += ./../FirefighterTrainingPlaner/database
INCLUDEPATH += ./../FirefighterTrainingPlaner/ImportExport
INCLUDEPATH += ./../FirefighterTrainingPlaner/middleware
INCLUDEPATH += ./../QXlsx/header/
INCLUDEPATH += ./../FirefighterTrainingPlaner/container

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FirefighterTrainingPlaner/ -lFirefighterTrainingPlaner
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FirefighterTrainingPlaner/ -lFirefighterTrainingPlanerd
else:unix: LIBS += -L$$OUT_PWD/../FirefighterTrainingPlaner/ -lFirefighterTrainingPlaner

INCLUDEPATH += $$PWD/../FirefighterTrainingPlaner
DEPENDPATH += $$PWD/../FirefighterTrainingPlaner

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/libFirefighterTrainingPlaner.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/libFirefighterTrainingPlanerd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/FirefighterTrainingPlaner.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/FirefighterTrainingPlanerd.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../FirefighterTrainingPlaner/libFirefighterTrainingPlaner.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QXlsx/ -lQXlsx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QXlsx/ -lQXlsxd
else:unix: LIBS += -L$$OUT_PWD/../QXlsx/ -lQXlsx

INCLUDEPATH += $$PWD/../QXlsx
DEPENDPATH += $$PWD/../QXlsx

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/libQXlsx.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/libQXlsxd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/QXlsx.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/QXlsxd.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QXlsx/libQXlsx.a
