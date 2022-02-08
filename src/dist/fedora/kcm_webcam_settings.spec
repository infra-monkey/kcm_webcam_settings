%global kf5_version 5.89.0
%global qt5_version 5.15.2
Name:     {{{ git_dir_name }}}
Version:  0.0.1
Release:  1%{?dist}
Summary:  KDE Plasma system-settings module to configure your webcam
License:  GPLv3+
URL:      https://github.com/infra-monkey/kcm_webcam_settings
VCS:      {{{ git_dir_vcs }}}
Source:   {{{ git_dir_pack }}}
BuildArch: x86_64
BuildRequires: cmake >= 3.16
BuildRequires: kf5-ki18n-devel >= %{kf5_version}
BuildRequires: kf5-kcmutils-devel >= %{kf5_version}
BuildRequires: kf5-kdeclarative-devel >= %{kf5_version}
BuildRequires: qt5-qtsvg-devel >= %{qt5_version}
BuildRequires: kf5-plasma-devel >= %{kf5_version}
BuildRequires: qt5-qtmultimedia-devel >= %{qt5_version}
Requires: v4l2-utils
Requires: kf5-ki18n >= %{kf5_version}
Requires: kf5-kcmutils >= %{kf5_version}
Requires: kf5-kdeclarative >= %{kf5_version}
Requires: qt5-qtsvg >= %{qt5_version}
Requires: kf5-plasma >= %{kf5_version}
Requires: qt5-qtmultimedia >= %{qt5_version}

%description
This module for systemsettings in KDE Plasma 5.23+ allows to configure Video4Linux (Webcam devices) settings such as brightness, saturation, auto-focus or even absolute zomm when the controles are exposed by the device. The default resolution and pixel format can also be adjusted. Note that not all software will respect the resolution and format.

%prep
{{{ git_dir_setup_macro }}}
%setup -q

%build
%cmake_qt5
%make

%install
%makeinstall_std -C build

%files

%changelog
* Mon Feb 07 2022 Antoine Gatineau <antoine.gatineau@infra-monkey.com> - 0.0.1
- Initial version of the package