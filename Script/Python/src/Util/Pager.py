'''
Created on 2010/10/11

@author: t
'''

class Pager:
	def __init__(self, _pageSize, elemList = []):
		self._pageSize = _pageSize
		self.elemList = elemList
	
	@property
	def pageSize(self):
		return self._pageSize
	@pageSize.setter
	def pageSize(self, size):
		if size != 0:
			self._pageSize = size
		else:
			self._pageSize = 1
	
	@property
	def pageNum(self):
		pageNum = len(self.elemList) // self.pageSize
		if len(self.elemList) % self.pageSize != 0:
			pageNum += 1
		return pageNum
	
	def getPage(self, page):
		if page >= self.pageNum:
			raise Exception("指定されたページは総ページ数を超えています")
		if page < 0:
			raise Exception("負数のページは指定できません")
		
		self.pageBegin = page * self.pageSize
		
		self.pageEnd = self.pageBegin + self.pageSize
		if self.pageEnd > len(self.elemList):
			self.pageEnd = len(self.elemList)
			return self._pageGenerator()
		else:
			return self._pageGenerator()
	def _pageGenerator(self):
		for i in range(self.pageBegin, self.pageEnd):
			yield self.elemList[i]