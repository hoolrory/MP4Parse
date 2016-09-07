file="$1"
make
if [ ! -z $2 ] 
then
    flag="$1"
    file="$2"
    build/bin/mp4parse "$flag" "$file"
else
    file="$1"
    build/bin/mp4parse "$file"
fi
