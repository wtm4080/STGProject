'''
Created on 2010/11/23

@author: t
'''

import STG.Ctrl as Ctrl
from STG.Stage.BaseEvent import Base
from Util.Coroutine import Coroutine

from ..Enemy.En01 import En01

class Ev02(Base):
	def __init__(self, stage):
		super().__init__(stage)
		self.eventCoroutine = Coroutine(self.updateEvent)
	
	def onUpdate(self):
		if self.eventCoroutine.alive:
			self.eventCoroutine.resume()
		else:
			self.end = True
	def updateEvent(self):
		enemy = En01(self.stage.resource, self.stageSetRef().scoreManager)
		Ctrl.Actor.registerEnemy(enemy)
		
		while enemy.valid: yield
		
		waitCount = 60 * 5
		while waitCount > 0:
			waitCount -= 1
			yield
	def onDraw(self):
		pass