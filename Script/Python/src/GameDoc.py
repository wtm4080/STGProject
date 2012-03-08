'''
Created on 2010/10/31

@author: t

Gameモジュールに対するhelp()の結果をGameDoc.txtに書き出します
'''

import Game
import Std; print(Std)
import STG.Ctrl as Ctrl; print(Ctrl)
import STG.Auxs as Auxs; print(Auxs)

if __name__ == "__main__":
	file = open("GameDoc.txt", "w", encoding = "utf-8")
	import sys
	sys.stdout = file
	help(Game)
	#file.close()