qmake                       // use default config
qmake "CONFIG+=c++11"       // add C++11 support
make all                    // make shared&static's debug&release libs
make release                // make shared&static's release libs
make debug                  // make shared&static's debug libs
make sub-shared all         // make shared's release&debug libs
make sub-static all         // make static's release&debug libs
make sub-shared release     // make shared's release libs
make sub-shared debug       // make shared's debug libs
make sub-static release     // make static's release libs
make sub-static debug       // make static's debug libs

make sub-designerplugin     // make designer's release plugin

Notice 1: for msvc compiler, replace make to nmake, .lib/.so/.a files in output folder. 
Notice 2: TcDBProcess class need to use qmake "CONFIG+=c++11"
