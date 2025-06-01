QT = core gui charts sql printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        IDataReader.cpp \
        JsonReader.cpp \
        SQLiteReader.cpp \
        chartfactory.cpp \
        main.cpp \
        mainwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AppConfigurator.h \
    BarChartRender.h \
    DataModel.h \
    IChartRender.h \
    IDataReader.h \
    JsonReader.h \
    LineChartRender.h \
    PieChartRender.h \
    SQLiteReader.h \
    ScatterChartRender.h \
    chartfactory.h \
    ioc_container.h \
    mainwindow.h \
    observer.h \
    printer.h \
    readerfactory.h
