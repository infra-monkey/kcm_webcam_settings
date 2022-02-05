# Build Dependencies

    cmake
    kf5-ki18n-devel
    kf5-kcmutils-devel
    kf5-kdeclarative-devel
    qt5-qtsvg-devel
    kf5-plasma-devel
    qt5-qtmultimedia-devel

# Runtime Dependencies

    cmake
    v4l2-utils
    kf5-ki18n
    kf5-kcmutils
    kf5-kdeclarative
    qt5-qtsvg
    kf5-plasma

# Enable debug logging

export QT_LOGGING_RULES="kcm.webcam_settings.debug=true"
before running kcmshell5

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

The unique identifier of the device is probably not that unique depending on the model. In the case of twa devices with the same uid, only the first one would be configured.

The resolution and pixel format is defined through v4l2 but the applications don't seem to use it. The result might not be what is configured here.
