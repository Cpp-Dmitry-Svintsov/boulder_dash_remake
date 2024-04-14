# boulder_dash_remake
boulder dash ramake by Svintsov Dmytro. Used SDL2_mix library for sounds. March 2024.
Game used Windows API for drawing - Windows Desctop Aplication Window. Only sounds use SDL2_mix library.
All spites, animation and text drawing by Windows API after game begin start and saved in HBITMAP structureб and after that it is not redrawn. BiBlt/BitTransparencyBlt commands are used instead. Therefore the game does not require graphic files.
For corractly working ints need SDL2_mix library.
