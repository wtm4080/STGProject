'''
Created on 2011/01/08

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.Enemy.BaseEnemy import Base

from .Behavior import Behavior
from .Drawing import Drawing
from .Face import Face
from .Move import Move
from .PrimalArmor import PrimalArmor
from .Side import Side

import STG.Regulation.Hidamari.Regular.Stage1.Yuno as Regulation

class Core(Base):
	SIZE = Std.Vector2DF(250, 200)
	MAX_HP = Regulation.hp
	
	def __init__(self, pos, resource, scoreManager):
		super().__init__(
			Std.Hit.RectI(pos, self.SIZE, True), self.MAX_HP)
		self.locator = Std.Locator.TraceF()
		self.locator.position = pos
		self.resource = resource
		self.drawing = Drawing(self)
		self.scoreManager = scoreManager
		
		self.sideL = Side(self, True)
		Ctrl.Actor.registerEnemy(self.sideL)
		self.sideR = Side(self, False)
		Ctrl.Actor.registerEnemy(self.sideR)
		
		self.hpGauge = Auxs.EnemyHPGauge(self.MAX_HP)
		self.hpGauge.appear()
		
		self.face = Face(self)
		self.move = Move(self)
		self.behavior = Behavior(self)
		self.primalArmor = PrimalArmor(self)
		
		#コア以外の敵オブジェクトを保持
		self.subEnemyObjList = []
		
		self.bulletDestructionFrameCount = 0
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	@property
	def paGenerated(self):
		return self.primalArmor.generated
	@property
	def maxPAAmount(self):
		return self.primalArmor.maxAmount
	@property
	def paAmount(self):
		return self.primalArmor.amount
	
	def onUpdate(self):
		self.behavior.update()
		self.move.update()
		self.face.update()
		self.primalArmor.update()
		
		self.hpGauge.value = self.hp
		self.hpGauge.update()
		
		self.drawing.sideL_valid = self.sideL.valid
		self.drawing.sideR_valid = self.sideR.valid
		self.drawing.update()
		
		for obj in self.subEnemyObjList:
			if not obj.valid:
				self.subEnemyObjList.remove(obj)
		
		if self.bulletDestructionFrameCount > 0:
			Auxs.destructBullets()
			self.bulletDestructionFrameCount -= 1
	def onDraw(self):
		self.hpGauge.draw()
		self.drawing.draw()
		self.primalArmor.draw()
	
	def onErase(self):
		pass
	def onDestructed(self):
		self.hp = 0
		self.valid = True
		self.scoreManager.addScore(self.maxHp)
	def onDamaged(self, damage):
		self.scoreManager.addRate(damage * 0.01)
	def onDestructedByDamage(self, damage):
		self.onDestructed()
	
	def destructBullets(self, frameNum = 30):
		self.bulletDestructionFrameCount = frameNum