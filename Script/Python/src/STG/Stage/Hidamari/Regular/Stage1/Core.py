'''
Created on 2011/01/07

@author: t
'''

from STG.Stage.BaseStage import Base

from .Event.Ev01_Yuno import Ev01_Yuno
from ..ResultEvent import ResultEvent

class Core(Base):
	def __init__(self, _):
		super().__init__()
	def onInitialize(self):
		self.eventList.append(Ev01_Yuno(self))
		self.eventList.append(ResultEvent(self))
	
	def onUpdate(self):
		pass
	def onDraw(self):
		pass