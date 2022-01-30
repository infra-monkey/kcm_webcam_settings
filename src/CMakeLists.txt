# SPDX-FileCopyrightText: Year Author <email@company.com>
#
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)

project(webcamkcm)

set(QT_MIN_VERSION "5.15.2")
set(KF5_MIN_VERSION "5.87.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Quick
    Svg
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    KCMUtils
    Declarative
    Config
    PlasmaQuick
    Auth
)

set(QWebcamSettings_SRCS
    QWebcamSettings.cpp
    VideoDevice.cpp
    VideoDeviceList.cpp
    VideoDeviceCtrl.cpp
    VideoDeviceCapFormat.cpp
    VideoDeviceResolution.cpp
    helpers.cpp
)

add_executable(udevhelper UdevHelper.cpp UdevHelper.h)
target_link_libraries(udevhelper KF5::Auth)
install(TARGETS udevhelper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
kauth_install_helper_files(udevhelper kcm_webcam_settings.udevhelper root)

add_library(kcm_webcam_settings MODULE ${QWebcamSettings_SRCS})

target_link_libraries(kcm_webcam_settings
    KF5::ConfigCore
    KF5::CoreAddons
    KF5::Declarative
    KF5::I18n
    KF5::PlasmaQuick
    KF5::QuickAddons
)
target_compile_options (kcm_webcam_settings PUBLIC -fexceptions)
target_link_libraries(kcm_webcam_settings -lv4l2)
kcoreaddons_desktop_to_json(kcm_webcam_settings "package/metadata.desktop")

install(TARGETS kcm_webcam_settings DESTINATION ${KDE_INSTALL_PLUGINDIR}/kcms)
install(FILES package/metadata.desktop RENAME kcm_webcam_settings.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR}) # Install the desktop file


kpackage_install_package(package kcm_webcam_settings kcms) # Install our QML kpackage.                                                                                               
