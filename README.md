# Description

kcm_webcam_settings is quite self explanatory. It is a module for KDE Plasma System Settings that allows to adjust and apply some settings for the webcam if available. Be aware that not all webcams expose settings.

It also defines udev rules so that whenever the webcam is plugged in, the settings are automatically applied again. This allows for instance to switch cameras and have customized settings for each of them.

kcm_webcam_setttings also support multiple devices.

![Screenshot](/resources/screenshot_kcm_webcam_settings.png "Webcam Settings")


# Build Dependencies

    cmake
    kf5-ki18n-devel
    kf5-kcmutils-devel
    kf5-kdeclarative-devel
    qt5-qtsvg-devel
    kf5-plasma-devel
    qt5-qtmultimedia-devel

# Runtime Dependencies

    v4l-utils
    kf5-ki18n
    kf5-kcmutils
    kf5-kdeclarative
    qt5-qtsvg
    kf5-plasma

# Enable debug logging

Before running `kcmshell5 kcm_webcam_settings` or `systemsettings5`

    export QT_LOGGING_RULES="kcm.webcam_settings.debug=true"


# Test Build

    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=~/.local/kde
    make
    sudo make install
    source prefix.sh
    kcmshell5 kcm_webcam_settings

# Install from source

    git clone https://github.com/infra-monkey/kcm_webcam_settings.git
    cd kcm_webcam_settings
    cmake ..
    make
    sudo make install

# Known issues

The unique identifier of the device is probably not that unique depending on the model. In the case of two devices with the same serialid, only the first one would be configured.

The resolution and pixel format is defined through Video4Linux but the applications don't seem to always use it. The result in the applications might not be what is configured in systemsettings.

The settings are set system wide. This means that if multiple users are configured on the system and define different settings, the last one to modify the settings will define it for everyone.

The Zoom Client will not use the settings defined in this module if "HD" is checked in the "Zoom application" camera settings.

# Security and permissions

The kcm need root permission to write the udev rules.
An action is create allowing one function to use root privileges. This function only writes in `/etc/udev/rules.d/99-persistent-webcam.rules` and reloads the udev rules.

# Packaging

I maintain rpm for Fedora in [Copr](https://copr.fedorainfracloud.org/coprs/monkeybizness/kcm_webcam_settings/).

Supported platforms are :
- Fedora 34 (x86_64,aarch64)
- Fedora 35 (x86_64,aarch64)
- Fedora 36 (x86_64,aarch64)
