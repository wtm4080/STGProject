'''
Created on 2011/12/19

@author: t
'''

import Std
from Util.Misc import loadSE

class _Resource:
	def __init__(self):
		self.font_Common16 = Std.Font.load("Hidamari/Common16.sff")
		self.font_Common24 = Std.Font.load("Hidamari/Common24.sff")
		self.font_Common32 = Std.Font.load("Hidamari/Common32.sff")
		
		self.se_Select1 = loadSE("Hidamari/Select1.wav")
		self.se_Select2 = loadSE("Hidamari/Select2.wav")
		self.se_Select3 = loadSE("Hidamari/Select3.wav")
		self.se_Cancel = loadSE("Hidamari/Cancel.wav")

_resource = None
def getResource():
	global _resource
	if not _resource:
		_resource = _Resource()
	return _resource