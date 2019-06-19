#!/bin/sh
# 程序功能:找到指定文件的指定一行内容
# 初始化参数

function replaceWord(){
	file=$1
	name=$2	

	sed -e "s/cutg/$name/g" $file
	sed -i "s/cutg/$name/g" $file
	sed -i "s/CUTG/$name/g" $file
	sleep 1
}


for(( i = 0;i <2;i++)){
	for(( j = 0;j <7;j++)){
		fileName="side"$i"BarNo"$j".C"
		wordName="side"$i"BarNo"$j
		echo $fileName
		# -f 参数判断 $file 是否存在
		if [ ! -f "$fileName" ]; then
			echo "Not exists"
		elif [ $(cat -n $fileName |grep "CUTG" |awk '{print $1}'| sed -n '1p') > 0 ];then
			#echo "hello"
			replaceWord $fileName $wordName
		else
			echo "Alread add Line"
		fi
	}
}


