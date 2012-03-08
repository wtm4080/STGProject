#pragma once

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Plugin
{
namespace File
{

//---------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------
/**
	@brief Cryptプラグインインターフェイス
	@author 葉迩倭
	@note
	独自の暗号プラグインを作成する場合は<BR>
	このインターフェイスクラスを継承して実装をして下さい。
*/
class ICrypt
{
protected:
	virtual ~ICrypt() { }

public:
	/**
		@brief 解放処理用
		@note
		内部で解放処理を行う<BR>
		DLL実装なので外からdeleteは出来ない。
	*/
	virtual void Release() = 0;
	/**
		@brief 暗号化
		@param pInput	[in] 暗号前元データ
		@param pOutput	[in] 暗号化データ出力先
		@param Size		[in] pInputで与えられたデータのサイズ
		@param Offset	[in] データの位置（ファイルの先頭からのオフセット）
		@note
		与えられたデータを元に暗号化します。
	*/
	virtual void Encrypt( const unsigned char* pInput, unsigned char* pOutput, unsigned long Size, unsigned long Offset ) = 0;
	/**
		@brief 暗号解除
		@param pInput	[in] 暗号化データ
		@param pOutput	[in] 暗号解除データ出力先
		@param Size		[in] pInputで与えられたデータのサイズ
		@param Offset	[in] データの位置（ファイルの先頭からのオフセット）
		@note
		与えられたデータを元に暗号を解除します。
	*/
	virtual void Decrypt( const unsigned char* pInput, unsigned char* pOutput, unsigned long Size, unsigned long Offset ) = 0;
};

//---------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------
typedef ICrypt* (__stdcall* CreateCryptInterfaceProc)( const char* );

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
}
}