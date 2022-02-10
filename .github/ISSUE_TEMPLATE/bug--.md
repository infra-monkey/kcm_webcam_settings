---
name: 'Bug: '
about: Create a report to help us improve
title: ''
labels: ''
assignees: ''

---

**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

**Expected behavior**
A clear and concise description of what you expected to happen.

**Screenshots**
If applicable, add screenshots to help explain your problem.

**Desktop (please complete the following information):**
 - OS: [e.g. iOS]
 - Browser [e.g. chrome, safari]
 - Version [e.g. 22]

**Additional context**
Add any other context about the problem here.

**Device information**
Add device discovery information

>v4l2-ctl --list-devices

For each device:
>v4l2-ctl -d /dev/video0 --list-ctrls-menus
>v4l2-ctl -d /dev/video0 --get-fmt-video
>v4l2-ctl -d /dev/video0 --list-formats-ext
