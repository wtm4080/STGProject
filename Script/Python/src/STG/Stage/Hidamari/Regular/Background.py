'''
Created on 2011/01/07

@author: t
'''

import Std
import STG.Ctrl as Ctrl

class Background:
	MARGIN = 100
	
	def __init__(self, stageSet):
		self.stageSet = stageSet
		
		self.groundDrawParam = Std.Sprite.DrawParam()
		self.groundDrawParam.dst = Std.RectF(-self.MARGIN, -self.MARGIN, 
			Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x + self.MARGIN*2, 
			Std.Consts.ScreenSize.y + self.MARGIN*2)
		self.groundDrawParam.color = Std.ColorF(124/255, 194/255, 140/255)
		self.groundDrawParam.priority = Ctrl.DrawPriority.background
		
		self.treeList = []
		self.treeCreation = False
	
	def update(self):
		for tree in self.treeList:
			if not tree.valid:
				self.treeList.remove(tree)
		if self.treeCreation:
			self._createTree()
	def draw(self):
		Std.Sprite.draw(self.groundDrawParam)
		for tree in self.treeList:
			Std.Sprite.draw(tree.drawParam)
	
	def startTreeCreation(self):
		self.treeCreation = True
	def _createTree(self):
		rand = Ctrl.getRandom()
		
		pos = Std.Vector2DF()
		pos.x = rand.getFloat(
			-_Tree.VALID_SIZE.x/2, 
			Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x + _Tree.VALID_SIZE.x/2)
		pos.y = -_Tree.VALID_SIZE.y / 2
		
		tree = _Tree(pos, self.stageSet)
		Ctrl.Actor.registerActor(tree)
		self.treeList.insert(0, tree)

from STG.Actor.BaseActor import Base

class _Tree(Base):
	VALID_SIZE = Std.Vector2DF(116, 152)
	
	def __init__(self, pos, stageSet):
		super().__init__(
			Std.Hit.RectI(pos, self.VALID_SIZE, True))
		
		self.locator = Std.Locator.LinearF(pos)
		self.locator.speed.y = stageSet.scrollSpeed
		
		self.stageSet = stageSet
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = stageSet.resource.tree
		self.drawParam.src = Std.RectF(0, 0, 116, 152)
		self.drawParam.dst = pos.makeRect(self.VALID_SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.background2
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return Std.Vector2DF()
	
	def onUpdate(self):
		self.locator.speed.y = self.stageSet.scrollSpeed
		self.locator.update()
		self.drawParam.dst = self.locator.position.makeRect(
			self.VALID_SIZE, True)
	def onDraw(self):
		pass
	
	def onErase(self):
		pass