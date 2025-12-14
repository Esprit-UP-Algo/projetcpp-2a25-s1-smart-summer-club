@echo off
echo Nettoyage des fichiers de compilation...
rmdir /s /q build
del /s /q *.pro.user
del /s /q Makefile
del /s /q Makefile.*
echo Nettoyage terminé.
pause
