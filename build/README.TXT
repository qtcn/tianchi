make all                    // make shared&static's debug&release libs
make release                // make shared&static's release libs
make debug                  // make shared&static's debug libs
make sub-shared all         // make shared's release&debug libs
make sub-static all         // make static's release&debug libs
make sub-shared release     // make shared's release libs
make sub-shared debug       // make shared's debug libs
make sub-static release     // make static's release libs
make sub-static debug       // make static's debug libs

Notice: for msvc compiler, replace make to nmake
