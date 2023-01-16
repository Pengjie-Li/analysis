find ./ -name "*_1*"| while read id; do fileName=${id%.*}; mv $id $fileName".root"; done
