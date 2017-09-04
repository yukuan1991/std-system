QT += qml quick widgets core gui quickwidgets avwidgets charts xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++1z

SOURCES += main.cc \
    StdMain.cc \
    video.cc \
    video2.cc \
    video/video_analysis.cc \
    video/video_main.cc \
    video/video_widget.cc \
    video/form_widget.cpp \
    video/video_delegate.cc \
    video/video_form_model.cc \
    video/video_form_split.cc \
    video/first_dlg.cpp \
    video/whisker.cc \
    video/progress_label.cpp \
    utils/VideoRibbon.cc \
    mtm/data_widget.cc \
    mtm/mtm_analysis.cc \
    mtm/mtm_main.cc \
    mtm/mtm_widget.cc \
    mtm/Qt-Utils/des.cpp \
    mtm/Qt-Utils/encryption.cpp \
    mtm/Qt-Utils/tinyxml2.cpp \
    mtm/interface_control/about_us_dlg.cc \
    mtm/interface_control/push_button.cpp \
    mtm/interface_control/ribbon.cc \
    mtm/interface_control/ribbon_mtm.cc \
    mtm/pts/code_edit.cpp \
    mtm/pts/pts_delegate.cpp \
    mtm/pts/pts_model.cpp \
    utils/json_model.cpp \
    utils/json_model.cpp \
    utils/table_view.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

FORMS += \
    StdMain.ui \
    video.ui \
    video2.ui \
    video/video_analysis.ui \
    video/video_main.ui \
    video/video_widget.ui \
    video/form_widget.ui \
    video/first_dlg.ui \
    mtm/data_widget.ui \
    mtm/mtm_analysis.ui \
    mtm/mtm_main.ui \
    mtm/mtm_widget.ui

HEADERS += \
    StdMain.h \
    video.h \
    video2.h \
    video/video_analysis.h \
    video/video_main.h \
    video/video_widget.h \
    video/form_widget.h \
    video/video_delegate.h \
    video/video_form_model.h \
    utils/json.hpp \
    utils/utils.hpp \
    video/video_form_split.h \
    video/first_dlg.h \
    utils/video_player.hpp \
    video/whisker.h \
    video/progress_label.h \
    utils/VideoRibbon.h \
    mtm/arithmetic_resource.hpp \
    mtm/data_widget.h \
    mtm/mtm_analysis.h \
    mtm/mtm_main.h \
    mtm/mtm_widget.h \
    mtm/Qt-Utils/des.h \
    mtm/Qt-Utils/encryption.h \
    mtm/Qt-Utils/json.hpp \
    mtm/Qt-Utils/krys_application.hpp \
    mtm/Qt-Utils/qt.hpp \
    mtm/Qt-Utils/stl_extension.hpp \
    mtm/Qt-Utils/tinyxml2.h \
    mtm/interface_control/about_us_dlg.h \
    mtm/interface_control/push_button.h \
    mtm/interface_control/ribbon.h \
    mtm/interface_control/ribbon_mtm.h \
    mtm/pts/code_edit.h \
    mtm/pts/pts_delegate.h \
    mtm/pts/pts_model.h \
    utils/json_model.h \
    utils/json_model.h \
    utils/table_view.h

QMAKE_CXXFLAGS += -Wextra
QMAKE_CXXFLAGS += -Wno-deprecated-declarations
QMAKE_CXXFLAGS += -Werror=write-strings
QMAKE_CXXFLAGS += -Werror=return-type
QMAKE_CXXFLAGS += -Werror=parentheses
QMAKE_CXXFLAGS += -Werror=maybe-uninitialized

LIBS += -lboost_filesystem
LIBS += -lboost_system
LIBS += -lboost_regex
LIBS += -lboost_thread
LIBS += -lboost_locale
LIBS += -liconv
LIBS += -lwininet
LIBS += -lws2_32
