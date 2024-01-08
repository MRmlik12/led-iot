#!/bin/sh

rm -rf ./iot/.pio
echo "Cleand ./iot/.pio folder"
rm -rf ./iot/data/www/*
echo "Cleaned iot/data/www folder"
rm -rf ./web-panel/dist
echo "Cleaned web-panel/dist folder"
