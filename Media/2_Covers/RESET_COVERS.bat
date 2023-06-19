@echo off

set "folder=C:\Users\David\GitHubRepos\CoverVidMaker\Media\2_Covers"
set "extension=png"
set "count=0"

echo Deleting PNG files in %folder%...

for %%F in ("%folder%\*.%extension%") do (
    del "%%F"
    set /a count+=1
)

echo %count% file(s) deleted.

pause
