'''
Created on 2011/02/02

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from .Launcher import Phase1_1
from .Launcher import Phase1_2
from .Launcher import Phase1_3
from .Launcher import Phase2_1
from .Launcher import Phase2_2

import STG.Regulation.Hidamari.Regular.Stage1.Yuno as Regulation

class Behavior:
	def __init__(self, core):
		self.core = core
		self.main = Coroutine(self._main)
		self.rankCarryOver = None
	
	def update(self):
		if self.main.alive:
			self.main.resume()
	
	def _main(self):
		phase1 = Coroutine(self._phase1)
		while self.core.hp > Regulation.phase2Threshold and phase1.alive:
			phase1.resume()
			yield
		else:
			self._explode()
			for obj in self.core.subEnemyObjList:
				obj.erase()
		
		phase2 = Coroutine(self._phase2)
		while self.core.hp > 0 and phase2.alive:
			phase2.resume()
			yield
		else:
			for obj in self.core.subEnemyObjList:
				obj.erase()
			
			destruct = Coroutine(self._destruct)
			while destruct.alive:
				destruct.resume()
				yield
	
	def _phase1(self):
		rank = Regulation.initialRank
		self.rankCarryOver = rank - Regulation.initialRank
		
		while True:
			sideLRandom = Phase1_1.SideRandom(True, self.core, rank)
			sideRRandom = Phase1_1.SideRandom(False, self.core, rank)
			chainGun = Phase1_1.ChainGun(self.core, rank)
			wait = createWait(60 * 6)
			while wait() or chainGun.shooting:
				if self.core.sideL.valid:
					sideLRandom.update()
				if self.core.sideR.valid:
					sideRRandom.update()
				chainGun.update()
				yield
			
			regulation_Phase1_2 = Regulation.Phase1_2(rank)
			wait = createWait(regulation_Phase1_2.firstWait)
			while wait(): yield
			
			missileHolder = Phase1_2.MissileHolder(self.core, rank)
			while not missileHolder.end:
				missileHolder.update()
				yield
			
			regulation_Phase1_3 = Regulation.Phase1_3(rank)
			wait = createWait(regulation_Phase1_3.firstWait)
			while wait(): yield
			
			chainGun = Phase1_3.ChainGun(self.core, rank)
			crossCircle = Phase1_3.CrossCircle(self.core, rank)
			while not crossCircle.end or chainGun.shooting:
				chainGun.update()
				crossCircle.update()
				yield
			
			wait = createWait(90)
			while wait(): yield
			
			rank += Regulation.rankIncrement
			self.rankCarryOver = rank - Regulation.initialRank
			yield
	def _explode(self):
		self.core.destructBullets()
		if self.core.sideL.valid: 
			self.core.sideL.destruct()
		if self.core.sideR.valid:
			self.core.sideR.destruct()
		self.core.face.destruction()
		Std.Sprite.setShake(15, 0.3)
		expObjList = self.core.drawing.createExplosion(
			Ctrl.DrawPriority.enemy4, 
			15, 
			Std.Vector2DF(
				self.core.locator.position.x, 
				self.core.locator.position.y - 20), 
			256, 
			2, 
			Std.Vector2DF(150, 60), 
			0.3)
		for expObj in expObjList:
			expObj.locator.speed.y = 3
		
		self.core.resource.se_Explode2.play()
	def _phase2(self):
		rank = Regulation.initialRank + self.rankCarryOver*Regulation.rankCarryOverRate
		
		wait = createWait(90)
		while wait(): yield
		
		while True:
			bitManager = Phase2_1.BitManager(self.core, rank)
			while not bitManager.end:
				bitManager.update()
				yield
			
			crossLauncher = Phase2_2.CrossLauncher(self.core, rank)
			chainGun = Phase2_2.ChainGun(self.core, rank)
			while crossLauncher.shooting or not chainGun.end:
				crossLauncher.update()
				chainGun.update()
				yield
			
			rank += Regulation.rankIncrement
			yield
	def _destruct(self):
		self.core.destructBullets()
		self.core.move.controlFlag = False
		self.core.locator.tracing = False
		self.core.locator.accel *= 0
		self.core.locator.speed = Std.Vector2DF(0, 0.2)
		self.core.primalArmor.enabled = False
		
		self.core.resource.se_BossDestruction1_1.play()
		for i in range(60 * 4 + 52): 
			if i % 2 == 0:
				expObjList = self.core.drawing.createExplosion(
					Ctrl.DrawPriority.enemy4, 
					1, 
					self.core.locator.position, 
					96, 
					0.7, 
					Std.Vector2DF(100, 80), 
					0.3)
				for expObj in expObjList:
					angle = self.core.locator.position.getAngle(
						expObj.position)
					rand = Ctrl.getRandom()
					speed = rand.getFloat(0, 3)
					expObj.locator.speed.setUnitVector(angle)
					expObj.locator.speed *= speed
			yield
		
		self.core.resource.se_BossDestruction1_1.stop()
		self.core.resource.se_BossDestruction1_2.play()
		self.core.drawing.createExplosion(
			Ctrl.DrawPriority.enemy4, 
			50, 
			self.core.locator.position, 
			384, 
			4, 
			Std.Vector2DF(200, 150), 
			0.3)
		Std.Sprite.setShake(20, 0.2)
		self.core.valid = False