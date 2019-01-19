QT += qml quick sql quickcontrols2
QTPLUGIN += qsqlite
TEMPLATE = lib
CONFIG += c++17
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ./../../../boost/boost_1_69_0/
INCLUDEPATH += ./container/
INCLUDEPATH += ./../QXlsx/header/

SOURCES += \
    middleware/event.cpp \
    middleware/IcalGenerator.cpp \
    middleware/JahreskalenderParser.cpp \
    middleware/main.cpp \
    middleware/sqleventmodel.cpp \
    middleware/SqlTableNames.cpp \
    middleware/uebungskartegenerator.cpp \
    middleware/adf.cpp \
    middleware/fwunit.cpp \
    middleware/drilltype.cpp \
    middleware/firebrigade.cpp \
    middleware/init.cpp \
    database/fwUnitDb.cpp \
    database/fwdrilltypeDb.cpp \
    database/dbconnectioninterface.cpp \
    ImportExport/calendarparser.cpp

HEADERS += \
    middleware/event.h \
    middleware/IcalGenerator.hpp \
    middleware/JahreskalenderParser.hpp \
    middleware/sqleventmodel.h \
    middleware/SqlTableNames.hpp \
    middleware/uebungskartegenerator.hpp \
    middleware/adf.hpp \
    middleware/firefighter.hpp \
    middleware/fwunit.hpp \
    middleware/drilltype.hpp \
    middleware/firebrigade.hpp \
    middleware/init.hpp \
    database/fwUnitDb.hpp \
    database/fwdrilltypeDb.hpp \
    database/dbconnectioninterface.hpp \
    database/dbtabledefinition.hpp \
    ImportExport/calendarparser.hpp \
    ImportExport/cellfilters.hpp \
    ImportExport/calendarlayout.hpp

RESOURCES += \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/eventindicator.png \
    images/eventindicator1.png \
    images/eventindicator2.png \
    images/eventindicator3.png \
    images/eventindicator4.png \
    images/eventindicator5.png \
    images/eventindicator6.png \
    images/eventindicator7.png \
    src/src.pri


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
