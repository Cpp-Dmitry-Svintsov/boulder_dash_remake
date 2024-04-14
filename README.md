# boulder_dash_remake
boulder dash ramake by Svintsov Dmytro. Used SDL2_mix library for sounds. March 2024.
Game used Windows API for drawing - Windows Desctop Aplication Window. Only sounds use SDL2_mix library.
All spites, animation and text drawing by Windows API after game begin start and saved in HBITMAP structureб and after that it is not redrawn. BiBlt/BitTransparencyBlt commands are used instead. Therefore the game does not require graphic files.
For corractly working ints need SDL2_mix library.
All level data - it's an array. Every level has own timing and how much diamonds its need to win. Its only 3 lives. If all lives is spented the game state retrun to Title. It's need to pres SPACE to start game again.
The game has only 2 levels to show mekanics of game. I created two type of anemys: butterfly and rombus. If butterfly is dead (the stone fall down into him) the space 3x3 wiil be filled with diamonds unlike rombus dead.
I dont created lava.
The algoritm of pythfind by anemy is simple and the enemy look at the right side of his direction, if it's free it changed his direction, if not look at the direction,...
The algoritm of sone fallen is simple = We go for array for all stones in DOWN - TOP direction. If the cell undes the current stone is free stne moove down, if we have two free cail in the left and left-bottom and dont have stobe in left-top - moove left, and ....
The Camera algoritm I use fow SCROPLLING game level, because the game area is bigger than screen.
The Moover - Moove objects in the game.
In this game I Use Singleton for two instance: AsFrameDc and Camera. It need to use AsSingletonInstance::Get_Instance() to get instance. And when game is ending all singletons it's need to delete - AsSingletonInstance::Delete_Instance();
Because of merging screen I use double buffering.
