QT += qml quick widgets core gui quickwidgets avwidgets charts xlsx printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++1z

SOURCES += main.cc \
    StdMain.cc \
    video/video_analysis.cc \
    video/video_widget.cc \
    video/form_widget.cpp \
    video/video_delegate.cc \
    video/video_form_model.cc \
    video/video_form_split.cc \
    video/first_dlg.cpp \
    video/whisker.cc \
    video/progress_label.cpp \
    mtm/mtm_analysis.cc \
    mtm/mtm_main.cc \
    mtm/mtm_widget.cc \
    mod/mod_analysis.cc \
    mod/mod_main.cc \
    mod/mod_widget.cc \
    utils/interface_control/about_us_dlg.cc \
    utils/interface_control/push_button.cpp \
    utils/model/json_model.cpp \
    utils/pts/pts_delegate.cpp \
    utils/pts/pts_model.cpp \
    utils/Qt-Utils/des.cpp \
    utils/Qt-Utils/encryption.cpp \
    utils/Qt-Utils/tinyxml2.cpp \
    utils/view/table_view.cpp \
    mod/ribbon/ribbon_mod.cc \
    mtm/ribbon/ribbon_mtm.cc \
    mtm/mtm_data_widget.cc \
    mod/mod_data_widget.cc \
    most/ribbon/ribbon_most.cc \
    most/most_analysis.cc \
    most/most_main.cc \
    most/most_selection_dlg.cpp \
    most/most_widget.cc \
    most/most_data_widget.cc \
    utils/ribbon.cc \
    video/video_ribbon.cc \
    video/VideoMainMassive.cc \
    IoManipulator.cc \
    HttpIoManipulator.cc \
    tcp.cc \
    utils/JsonTree.cc \
    product-family/ProductFamilyWidget.cc \
    database/database.cc \
    video/videotrial/FormWidget.cpp \
    video/videotrial/VideoAnalysis.cc \
    video/videotrial/VideoFormModel.cc \
    video/videotrial/VideoMainTrial.cc \
    video/videotrial/VideoTrialRibbon.cc \
    pwh_contrast/PwhContrastMain.cc \
    utils/data_veryfication.cpp \
    utils/Qt-Utils/openaf.cc \
    pwh_contrast/ribbon/PwhContrastRibbon.cc \
    pwh_contrast/PieView.cc \
    pwh_contrast/production_management_button_tree_dlg.cpp \
    pwh_contrast/PwhContrast.cc \
    pwh_contrast/PwhListWidget.cc \
    pwh_contrast/StatView.cc \
    utils/model/product_info_model.cpp \
    utils/model/product_structure_model.cpp \
    approval/ExamineApproveMain.cpp

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

DISTFILES += \
    mod/mod.data \
    most/most.data \
    database/test.json \
    approval/test.json \
    approval/2.vaf

FORMS += \
    StdMain.ui \
    video/video_analysis.ui \
    video/video_widget.ui \
    video/form_widget.ui \
    video/first_dlg.ui \
    mtm/mtm_analysis.ui \
    mtm/mtm_main.ui \
    mtm/mtm_widget.ui \
    mod/mod_analysis.ui \
    mod/mod_main.ui \
    mod/mod_widget.ui \
    mod/mod_data_widget.ui \
    mtm/mtm_data_widget.ui \
    most/most_analysis.ui \
    most/most_main.ui \
    most/most_selection_dlg.ui \
    most/most_widget.ui \
    most/most_data_widget.ui \
    video/VideoMainMassive.ui \
    product-family/productfamilywidget.ui \
    database/database.ui \
    video/videotrial/FormWidget.ui \
    video/videotrial/VideoAnalysis.ui \
    video/videotrial/VideoMainTrial.ui \
    pwh_contrast/pwhcontrastmain.ui \
    pwh_contrast/production_management_button_tree_dlg.ui \
    pwh_contrast/pwhcontrast.ui \
    pwh_contrast/StatView.ui \
    approval/ExamineApproveMain.ui

HEADERS += \
    StdMain.h \
    video/video_analysis.h \
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
    mtm/mtm_analysis.h \
    mtm/mtm_main.h \
    mtm/mtm_widget.h \
    utils/ribbon.h \
    video/video_ribbon.h \
    mod/mod_analysis.h \
    mod/mod_main.h \
    mod/mod_widget.h \
    utils/interface_control/about_us_dlg.h \
    utils/interface_control/push_button.h \
    utils/model/json_model.h \
    utils/pts/pts_delegate.h \
    utils/pts/pts_model.h \
    utils/Qt-Utils/des.h \
    utils/Qt-Utils/encryption.h \
    utils/Qt-Utils/json.hpp \
    utils/Qt-Utils/krys_application.hpp \
    utils/Qt-Utils/qt.hpp \
    utils/Qt-Utils/stl_extension.hpp \
    utils/Qt-Utils/tinyxml2.h \
    utils/view/table_view.h \
    mod/ribbon/ribbon_mod.h \
    mtm/ribbon/ribbon_mtm.h \
    utils/arithmetic_resource.hpp \
    mtm/mtm_data_widget.h \
    mod/mod_data_widget.h \
    most/ribbon/ribbon_most.h \
    most/most_analysis.h \
    most/most_main.h \
    most/most_selection_dlg.h \
    most/most_widget.h \
    most/most_data_widget.h \
    video/VideoMainMassive.h \
    IoManipulator.h \
    HttpIoManipulator.h \
    tcp.h \
    utils/JsonTree.h \
    product-family/ProductFamilyWidget.h \
    database/database.h \
    video/videotrial/FormWidget.h \
    video/videotrial/VideoAnalysis.h \
    video/videotrial/VideoFormModel.h \
    video/videotrial/VideoMainTrial.h \
    video/videotrial/VideoTrialRibbon.h \
    pwh_contrast/PwhContrastMain.h \
    utils/data_veryfication.h \
    utils/Qt-Utils/openaf.h \
    pwh_contrast/ribbon/PwhContrastRibbon.h \
    pwh_contrast/PieView.h \
    pwh_contrast/production_management_button_tree_dlg.h \
    pwh_contrast/PwhContrast.h \
    pwh_contrast/PwhListWidget.h \
    pwh_contrast/StatView.h \
    utils/model/product_info_model.h \
    utils/model/product_structure_model.h \
    approval/ExamineApproveMain.h

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
