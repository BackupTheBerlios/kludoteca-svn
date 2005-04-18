#!/bin/bash
# arregla los estupidos permisos dañados por el estupido sistema vfat

mv todo TODO
mv readme README
mv news NEWS
mv copying COPYING
mv authors AUTHORS
mv install INSTALL

find . -type f -exec chmod 644 {} \;
find . -type d -exec chmod 755 {} \;

find . -name "*.sh" -exec chmod 755 {} \;
find . -name "*.pl" -exec chmod 755 {} \;

chmod 755 admin/*
chmod 755 configure
chmod 755 libtool


