#!/bin/sh

pnpm -C ./web-panel run build
cp -avr ./web-panel/dist/* ./iot/data/www