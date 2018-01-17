# exif-grouper

[BOB6]DF12_Tech_03_박강민

* src : Source directory
* exif-parser : Executable file


Environment
===========

* OS : Ubuntu 16.04.3 64bit
* Kernel : 4.13.0-26-generic
* IDE : QT Creator


Dependency
==========

* qt5

```
$ sudo apt install g++ make build-essential
$ sudo apt install qt5-default qt5-qmake
```


Build
======

```
$ cd src
$ mkdir build
$ cd build
$ qmake ../
$ make
```


Usage
======

* Open : Open JPG Image Files
* Filter : EXIF Metadata to make group
* Apply : Make group by exif filter
* Detail : View the exif metadata for the selected group


Result
=======

![MainWindow](https://i.imgur.com/FgYFBtE.png)
