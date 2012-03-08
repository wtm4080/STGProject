'''
Created on 2011/03/14

@author: t

ディレクトリを走査して、.pycファイルを削除します
'''

import os

extList = [".pyc"]
def isTempFile(path):
	_, ext = os.path.splitext(path)
	for tempExt in extList:
		if ext == tempExt:
			return True
	return False

for dirpath, dirname, filenames in os.walk("./"):
	for file in filenames:
		path = os.path.join(dirpath, file)
		if isTempFile(path):
			os.remove(path)
			print("Removed: " + str(path))