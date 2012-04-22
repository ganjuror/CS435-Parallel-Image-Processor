#!/bin/bash


g++ -O2 -o iteration2 iteration2main.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs`

./iteration2
