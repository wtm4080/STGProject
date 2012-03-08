'''
Created on 2010/10/20

@author: t
'''

import STG.Ctrl as Ctrl

def register(stageSetPair, pauseView, *stagePairs):
	"""
	ステージセットとステージの登録を一括で行います
	
	@param stageSetPair: ステージセットの名前とコアモジュールのタプル
	@param pauseView: ポーズ画面のコアモジュール
	@param stagePairs: 複数のステージの名前とコアモジュールのタプル
	"""
	
	stageSetId = Ctrl.Conf.registerStageSet(
		stageSetPair[0], stageSetPair[1], pauseView)
	for pair in stagePairs:
		Ctrl.Conf.registerStage(stageSetId, 
			pair[0], pair[1])

def configurate():
	"""
	ステージ情報の構成を行います
	
	プログラムの起動時にシステムが実行します。
	"""
	
	from .Test import Core as Test
	import STG.Pause.Basic.Core as BasicPauseView
	from .Test.Stage1 import Core as TestStage1
	register(("PyTest", Test), BasicPauseView, 
		("Stage1", TestStage1), 
		)
	
	from .Hidamari.Regular import Core as HRegular
	import STG.Pause.Hidamari.Core as HPauseView
	from .Hidamari.Regular.Stage1 import Core as HRStage1
	register(("HidamariRegular", HRegular), HPauseView, 
		("Stage1", HRStage1), 
		)