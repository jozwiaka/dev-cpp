#!/bin/bash

# Start the VNC server
vncserver :1 -geometry 1280x800 -depth 24

# Start the desktop environment (LXDE in this example)
startlxde &
