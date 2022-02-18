#Kill master proces
killall -SIGKILL master
killall -SIGKILL Nodo
killall -SIGKILL Utente

#Cleaning all exc files and IPCs
make clean

#Closing terminal
killall -SIGKILL bash