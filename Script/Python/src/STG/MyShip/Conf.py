'''
Created on 2010/10/20

@author: t
'''

import STG.Ctrl as Ctrl

def configurate():
	"""
	自機情報の構成を行います
	
	プログラムの起動時にシステムが実行します。
	"""
	
	import STG.MyShip.TestShip.Core as TestShip
	Ctrl.Conf.registerMyShip("PyTestShip", TestShip)
	
	import STG.MyShip.Hidamari.Nazuna.Core as Nazuna
	Ctrl.Conf.registerMyShip("Nazuna", Nazuna)
	import STG.MyShip.Hidamari.Nori.Core as Nori
	Ctrl.Conf.registerMyShip("Nori", Nori)