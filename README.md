# boulder_dash_remake
boulder dash ramake by Svintsov Dmytro. Used SDL2_mix library for sounds. March 2024.
Game used Windows API for drawing - Windows Desctop Aplication Window. Only sounds use SDL2_mix library.
All spites, animation and text drawing by Windows API after game begin start and saved in HBITMAP structureб and after that it is not redrawn. BiBlt/BitTransparencyBlt commands are used instead. Therefore the game does not require graphic files.
For corractly working ints need SDL2_mix library.
All level data - it's an array. Every level has own timing and how much diamonds its need to win. Its only 3 lives. If all lives is spented the game state retrun to Title. It's need to pres SPACE to start game again.
The game has only 2 levels to show mekanics of game. I created two type of anemys: butterfly and rombus. If butterfly is dead (the stone fall down into him) the space 3x3 wiil be filled with diamonds unlike rombus dead.
I dont created lava.
