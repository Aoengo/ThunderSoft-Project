#!/bin/sh

if [ "$1" == "build" ]
then
    sudo make clean
    sudo make
elif [ "$1" == "run" ]
then
    sudo insmod ThunderSoft_Project.ko
    watch "dmesg | tail -20"
elif [ "$1" == "server" ]
then
    sudo make clean 
    sudo make 
    sudo mknod /dev/demo_char c 236 0
    sudo chmod 666 /dev/demo_char
    sudo rmmod ThunderSoft_Project.ko
    sudo insmod ThunderSoft_Project.ko
    watch "dmesg | tail -20"
elif [ "$1" == "exit" ]
then 
    sudo make clean 
    sudo rmmod ThunderSoft_Project.ko
else 
    echo "Error Command:$1"
fi


