QtUPnP framework is a C++ framework, based on QT5, to build easily an UPnP control point.
It focuses on the UPnP/AV standards.
For this, a set of classes are created to handle easily media servers and media renderers and to hide the UPnP protocol.
Of course UPnP protocol (UPnP/AV use UPnP) is implemented and your can handle every compatible devices.

For a better description, unzip /upnp/docs/html.zip and choose index.html.

Build the framework and the test program need to install QT5. QtUPnP has been coded from:
  - Windows "qt-opensource-windows-x86-mingw530-5.8.0.exe" installer download from https://download.qt.io/official_releases/qt/5.8/5.8.0/.
    The built version is a 32 bits. It runs from Windows Vista to Windows 10 32 or 64 bits. 
    It has been tested on Vista 32 bits and Windows 10 32 and 64 bits.
    Do not forget to add to the path (global or QtCreator) the access to qtupnp.dll or change qtupnp library by a static library.

  - Linux "qt-opensource-linux-x64-5.8.0.run" installer download from https://download.qt.io/official_releases/qt/5.8/5.8.0/.
    The built version is a 64 bits. It has been tested on Kubuntu under VirtualBox and Ubuntu native.
    The actual pro file creates a static library.

The framework use only QT API, no other system dependent API.

chupnp is the program for developer to test the framework.
After discovery of devices, it is possible to invoke the actions and see the results.

Shortly, I will commit a new application using QtUPnP.
This application will be user oriented. It will be a complet control point to drive media servers and media renderers.
The main fonctionnalities will be:
  - A remote control format (small size on the screen).
  - Discover and show servers and renderers.
  - Browse the servers directories.
  - Manage renderers like a player (volume, seek, mute, suffle, repeat, cover, previous, next...).
  - Create audio, image, video playlists and favorites.
  - And a lot of another things. 






