'''
Created on 2011/05/21

@author: t

ディレクトリを走査して、.pyファイルの行数の合計を数えます
'''

import os

extList = [".py"]
def isPyFile(path):
	_, fileExt = os.path.splitext(path)
	for ext in extList:
		if fileExt == ext:
			return True
	return False

lineCount = 0

for dirpath, dirname, filenames in os.walk("./"):
	for filename in filenames:
		path = os.path.join(dirpath, filename)
		
		if isPyFile(path):
			file = open(path, encoding="utf-8")
			
			fileLineCount = 0
			for line in file:
				lineCount += 1
				fileLineCount += 1
			
			print(path + " --- LineCount: " + str(fileLineCount))

print("Total Line Count: " + str(lineCount))