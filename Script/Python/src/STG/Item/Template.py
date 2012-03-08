'''
Created on 2011/03/04

@author: t
'''

from STG.Item.BaseItem import Base

class Template(Base):
	def __init__(self, pos, angle = -90):
		super().__init__(pos, angle)
	
	def effect(self):
		pass