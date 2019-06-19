#!/bin/sh
# 程序功能:找到指定文件的指定一行内容
# 初始化参数

function commentLine(){
	import_file=$1
	totalLineNumber=$(wc -l $import_file|cut -d " " -f1)
	echo $totalLineNumber
	lineNumber=$(cat -n $import_file |grep "Draw" |awk '{print $1}')
	echo $lineNumber
	nextLine=$(($totalLineNumber-$lineNumber))
	echo $nextLine
	#数据导入
	head -n $(($lineNumber-1)) $import_file > newfile.txt
	tail -n $nextLine $import_file >> newfile.txt
	mv newfile.txt $import_file
	sleep 1
}


for(( i = 0;i <2;i++)){
	for(( j = 0;j <7;j++)){
		fileName="side"$i"BarNo"$j".C"
		echo $fileName
		# -f 参数判断 $file 是否存在
		if [ ! -f "$fileName" ]; then
			echo "Not exists"
		elif [ $(cat -n $fileName |grep "Draw" |awk '{print $1}') > 0 ];then
			commentLine $fileName
		else
			echo "Alread add Line"
		fi
	}
}


