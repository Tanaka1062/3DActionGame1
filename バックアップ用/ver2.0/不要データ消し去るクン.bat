@echo off
del /q Log.txt
rd /s /q game\x64\Debug
rd /s /q game\x64\Release
rd /s /q .vs\game\v17\ipch
rd /s /q x64\Debug
rd /s /q x64\Release
