'''
Created on 2011/09/08

@author: t
'''

#from .Basic.Core import Core as BasicTitle
#def getTitleInstance():
#	return BasicTitle()

from .Hidamari.Core import Core as HidamariTitle
def getTitleInstance():
	"""
	タイトル画面のコアモジュールを取得します
	
	STGタイトル画面起動時に、
	タイトル画面のコアモジュールを取得するために呼び出されます。
	"""
	
	return HidamariTitle()