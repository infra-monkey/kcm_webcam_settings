# Build Dependencies

cmake
v4l2-utils
kf5-ki18n-devel
kf5-kcmutils-devel
kf5-kdeclarative-devel
qt5-qtsvg-devel
kf5-plasma-devel

# Enable debug logging

export QT_LOGGING_RULES="webcam_settings_kcm.debug=true"
before running kcmshell5

# Test Build

mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=~/.local/kde
make -j8 install
source prefix.sh
kcmshell5 kcm_webcam_settings
