# HelenOS-Minisweeper-game
Simple game for HelenOS. 

Yes.. I was test, this work.
Maybe have bugs, maybe is ugly but work.
Nothing fancy, no graphic.
Game works inside Terminal.


How to install ?
Download code,  and put all in app/mines/  folder ( of course only files)
Add under "uspace/app" inside "meson.build" game name,
Open meson.build, and add 'mines' in app list. 

Exapmple:

apps = [
.
.
.
'lprint',
'mines',    // this is yor new game
'mixerctl',
.
.
]

Save changes.
Compile HelenOs
Start-> open Terminal
write inside mines
happy gaming :)
