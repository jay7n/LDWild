Welcome to the LDWild wiki!

#Overview
>__LDWild__ is an independent game developing project, which means " the Wild of a Lucid Dream ", also means "the Wild of a Loser's Dream". Note this is not the game name, but only a code name for the developing. 
>
>As a loser who's a rookie programmer in this reality, me, like most other guys, has a dream which is to make an independent game that could reflect the thought of myself.
>
>This project is still under a very beginning constructing phase and you may still get confused with the details of this project. Sorry about that, and I'll fill this page gradually.

#How to Build & Run
>Since the core game engine used in this project is __cocos2d-x__, plus __c++__(probably also with __lua__ in the near future) is used as the main programming language, this project could natively built and run in mutiple platforms(windows, mac os, etc). However, currently it ony has a VC project solution(.sln) 'cause I'm developing under a Win7 laptop. But I'll add a Mac Os solution later.
##Build
>If you work on a Win7 OS with one suite of "visual studio 2008", it's fairly easy for you to build the project. Just clone the repo to your own path, and open "LDWild.sln" and execute build in it. The compiler will tell you there're many of __Warnings__. You can just ignore it, since they're all of the legacy issues of the evolution of _cocos2d-x_ engine,  and I'll eliminate them at some time I refactor or refine the code. 
##Run
>If you built it successfully, you can find it In "Bin" folder. There's one file you built out named "LDWild.win32.exe". That's it. Double click it and you'll see the result.
##Troubleshooting
>Maybe you'll get troubles when you do some operations in the previous two steps(I guess probably this wouldn't happen, but I mean in case).
>
>The most case I can expect here may be the .dll files in "Bin" folder can not be loaded in the program. If you're at this case, you have to manually build the cocos2d-x engine first(At below there's one list telling which version of cocos2d-x this project is using). And simply you move all the .dll files you generated to "Bin" folder, and that's it.
>
>And feel free leave comments to me here or at __lookof@gmail.com__.

#Lib Dependency

* cocos2dx version = **[cocos2d-2.0-x-2.0.4](http://cocos2d-x.googlecode.com/files/cocos2d-2.0-x-2.0.4.zip)**
* Box2D version = **Box2D_v2.2.1** 
