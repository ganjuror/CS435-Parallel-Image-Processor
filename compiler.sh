#!/bin/bash


g++ -O2 -o redfilter redfilter.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs`

./redfilter
