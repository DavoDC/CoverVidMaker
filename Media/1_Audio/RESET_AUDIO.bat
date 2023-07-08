@echo off

set "folder=C:\Users\David\GitHubRepos\CoverVidMaker\Media\1_Audio"
set "extension=mp3"
set "count=0"

echo Deleting MP3 files in %folder%...

for %%F in ("%folder%\*.%extension%") do (
    del "%%F"
    set /a count+=1
)

echo %count% file(s) deleted.

pause