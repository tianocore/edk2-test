

svn co https://edk2.svn.sourceforge.net/svnroot/edk2/trunk/edk2 c:\edk2
svn co https://gcc-shell.svn.sourceforge.net/svnroot/gcc-shell/trunk/GccShellPkg  c:\edk2\EdkCompatibilityPkg/Other/Maintained/Application/Shell
decompress SctPkg to c:\edk2\SctPkg

To build with ARM RealView Compiler cd c:\edk2\SctPkg and execute RVCT31.bat
To build with Visual Studio 2003 for IA32 cd c:\edk2\SctPkg and execute VS2003.bat

There are still a large number of warnings with RVCT, but we can clean them up when we decide how 
to make the other fixes. The warnings will also be an issue with gcc. To support gcc build we will
also need to change \ in the .inf files to /. This has allready been done in the GccShellPkg.
