'''
Created on 2010/11/23

@author: t
'''

import Std

class Resource:
	def __init__(self):
		self.icon1 = Std.Sprite.loadTexture("Icon1.dds")
		self.icon2 = Std.Sprite.loadTexture("Icon2.dds")
		self.icon3 = Std.Sprite.loadTexture("Icon3.dds")
		self.icon4 = Std.Sprite.loadTexture("Icon4.dds")
		
		self.bml_En01_01 = Std.BulletML.createParser("Script/BulletML/PyTest/Stage1/En01_01.xml")
		self.bml_En01_01.build()