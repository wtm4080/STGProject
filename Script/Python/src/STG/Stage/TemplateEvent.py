'''
Created on 2011/03/04

@author: t
'''

from STG.Stage.BaseEvent import Base

class Template(Base):
	def __init__(self, stage):
		super().__init__(stage)
	
	def onUpdate(self):
		pass
	def onDraw(self):
		pass