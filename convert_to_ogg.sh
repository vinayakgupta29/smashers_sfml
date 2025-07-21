#!/bin/bash
ffmpeg -i "$1" -c:a libvorbis -q:a 5 "assets/sounds/$2"
