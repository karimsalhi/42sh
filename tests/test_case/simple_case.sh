var=zoo
var2=chat
var3=mouton
case $var2 in
    a*) echo le mot commence par a
    ;;
    t* | u*) echo le mot commence par t ou u
    ;;
    chat | mouton ) echo $var2 fait miaou ou baaahhh
    ;;
esac ;

