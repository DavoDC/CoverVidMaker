@echo off

set "folder=C:\Users\David\GitHubRepos\CoverVidMaker\Media\3_Videos"
set "extension=mp4"
set "count=0"

echo Deleting MP4 files in %folder%...

for %%F in ("%folder%\*.%extension%") do (
    del "%%F"
    set /a count+=1
)

echo %count% file(s) deleted.

pause