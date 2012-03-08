'''
Created on 2010/11/22

@author: t
'''

from STG.Stage.BaseStage import Base

from .Resource import Resource
from .Event.Ev01 import Ev01
from .Event.Ev02 import Ev02

class Core(Base):
	def __init__(self, _):
		super().__init__()
		self.resource = Resource()
	
	def onInitialize(self):
		self.eventList.append(Ev01(self))
		self.eventList.append(Ev02(self))
	
	def onUpdate(self):
		pass
	def onDraw(self):
		pass