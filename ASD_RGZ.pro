QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    btree.cpp \
    btree_add.cpp \
    dfs_bfs.cpp \
    dynamicprogramming.cpp \
    greedyalg.cpp \
    hashtable.cpp \
    heapsort.cpp \
    heapsort_add.cpp \
    huffman.cpp \
    list.cpp \
    main.cpp \
    mainwindow.cpp \
    shortest_path.cpp

HEADERS += \
    btree.h \
    btree_add.h \
    dfs_bfs.h \
    dynamicprogramming.h \
    greedyalg.h \
    hashtable.h \
    heapsort.h \
    heapsort_add.h \
    huffman.h \
    list.h \
    mainwindow.h \
    shortest_path.h

FORMS += \
    btree.ui \
    btree_add.ui \
    dfs_bfs.ui \
    dynamicprogramming.ui \
    greedyalg.ui \
    hashtable.ui \
    heapsort.ui \
    heapsort_add.ui \
    huffman.ui \
    mainwindow.ui \
    shortest_path.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
