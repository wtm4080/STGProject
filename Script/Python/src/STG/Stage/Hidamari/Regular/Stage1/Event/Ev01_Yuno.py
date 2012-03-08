'''
Created on 2011/01/08

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from STG.Stage.BaseEvent import Base
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

from ..Enemy.Mikan import Mikan
from ..Enemy.Moushiwake import Moushiwake
from ..Enemy.Yuno.Core import Core as Yuno

class Ev01_Yuno(Base):
	def __init__(self, stage):
		super().__init__(stage)
		self.eventCoroutine = Coroutine(self.updateEvent)
		self.resource = self.stageSetRef().resource
		self.scoreManager = self.stageSetRef().scoreManager
		self.scrolledEnemyList = []
		
		appearPos = Std.Vector2DF(0, -140)
		self.appearLocator = Std.Locator.LinearF(appearPos)
		self.appearLocator.speed.y = self.stageSetRef().scrollSpeed
		
		appearDrawParam = Std.Sprite.DrawParam()
		appearDrawParam.src = Std.RectF(0, 0, 440, 332)
		appearDrawParam.dst = self.appearLocator.position.makeRect(440, 332, False)
		appearDrawParam.priority = Ctrl.DrawPriority.background2
		self.appearAnimation = createSequenceAnimation(
			self.resource.st1_AppearTexList, appearDrawParam, 2)
		
		warningPos = Std.Vector2DF(220, 150)
		warningSize = Std.Vector2DF(400, 128) * 1.2
		warningDrawParam = Std.Sprite.DrawParam()
		warningDrawParam.src = Std.RectF(0, 0, 400, 128)
		warningDrawParam.dst = warningPos.makeRect(warningSize, True)
		warningDrawParam.priority = Ctrl.DrawPriority.warning
		self.warningAnimation = createSequenceAnimation(
			self.resource.warningTexList, warningDrawParam, 2)
	
	def onUpdate(self):
		if self.appearLocator.position.y <= Std.Consts.ScreenSize.y:
			if self.appearAnimation.playing:
				self.appearAnimation.update()
			self.appearLocator.speed.y = self.stageSetRef().scrollSpeed
			self.appearLocator.update()
			updateDst(self.appearAnimation, 
				self.appearLocator.position, Std.Vector2DF(440, 332), False)
		
		if self.warningAnimation.playing:
			self.warningAnimation.update()
		
		self.scrolledEnemyList = [enemy for enemy in self.scrolledEnemyList if enemy.valid]
		for enemy in self.scrolledEnemyList:
			enemy.speed = self.stageSetRef().scrollSpeed
		
		if self.eventCoroutine.alive:
			self.eventCoroutine.resume()
		else:
			self.end = True
	def updateEvent(self):
		self.resource.bgm_Stage1.play()
		
		width = Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x
		height = Std.Consts.ScreenSize.y
		mikan = Mikan(self.resource, self.stageSetRef().scoreManager, 
			Std.Vector2DF(width/3, height/2), self.stageSetRef().scrollSpeed)
		Ctrl.Actor.registerEnemy(mikan)
		self.scrolledEnemyList.append(mikan)
		
		moushiwake = Moushiwake(self.resource, self.stageSetRef().scoreManager, 
			Std.Vector2DF(width/3 * 2, height/2), self.stageSetRef().scrollSpeed)
		Ctrl.Actor.registerEnemy(moushiwake)
		self.scrolledEnemyList.append(moushiwake)
		
		wait = createWait(120)
		while wait(): yield
		self.resource.bgm_Stage1.fadeOut(4)
		
		wait = createWait(60 * 4.2)
		while wait(): yield
		self.resource.se_BossAlert.play()
		self.warningAnimation.play()
		self.scoreManager.pause = True
		
		while self.appearLocator.position.y < -47: yield
		self.appearAnimation.play()
		self.resource.bgm_Boss1.play(
			#self.resource.bgm_Boss1_PlayBlocks
			)
		self.resource.bgm_Stage1.stop()
		yield
		
		wait = createWait(199 * 2)
		while wait(): yield
		
		yuno = Yuno(
			Std.Vector2DF(220, self.appearLocator.position.y + 90), 
			self.resource, self.scoreManager)
		Ctrl.Actor.registerEnemy(yuno)
		self.scoreManager.pause = False
		
		self.stageSetRef().background.startTreeCreation()
		while self.stageSetRef().scrollSpeed < 6:
			self.stageSetRef().scrollSpeed += 0.05
			yield
		else:
			self.stageSetRef().scrollSpeed = 6
		
		while yuno.hp > 0: yield
		self.resource.bgm_Boss1.stop()
		myShip = Ctrl.Actor.myShip
		myShip.setShotForbidFlag(True)
		myShip.setSpecialAttackForbidFlag(True)
		self.scoreManager.pause = True
		self.stageSetRef().createScoreRateDrawer(
			yuno.position + Std.Vector2DF(-32, 0))
		
		while yuno.valid: yield
	
	def onDraw(self):
		if self.appearLocator.position.y <= Std.Consts.ScreenSize.y:
			self.appearAnimation.draw()
		if self.warningAnimation.playing:
			self.warningAnimation.draw()