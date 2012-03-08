#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Selene
{
	typedef char					Sint8;					///< signed char 型の別定義
	typedef short					Sint16;					///< signed short 型の別定義
	typedef long					Sint32;					///< signed long 型の別定義
	typedef long long				Sint64;					///< signed long 型の別定義
	typedef unsigned char			Uint8;					///< unsigned char 型の別定義
	typedef unsigned short			Uint16;					///< unsigned short 型の別定義
	typedef unsigned long			Uint32;					///< unsigned long 型の別定義
	typedef unsigned long long		Uint64;					///< unsigned long long 型の別定義

	/**
		@brief ２次元座標
		@author 葉迩話
		@note ２次元の座標を示すクラス
	*/
	template <typename T>
	class Point2D;

	typedef Point2D<float>	Point2DF;
	typedef Point2D<Sint32>	Point2DI;

	/**
		@brief ３次元座標
		@author 葉迩話
		@note ３次元の座標を示すクラス
	*/
	template <typename T>
	class Point3D;

	typedef Point3D<float>	Point3DF;
	typedef Point3D<Sint32>	Point3DI;

	/**
		@brief 矩形定義
		@author 葉迩話
		@note 矩形の定義
	*/
	template <typename T>
	class Rect;

	typedef Rect<float>		RectF;
	typedef Rect<Sint32>	RectI;

	/**
		@brief 色定義
		@author 葉迩話
		@note 色の定義
	*/
	struct ColorU;

	/**
		@brief 色定義
		@author 葉迩話
		@note 色の定義
	*/
	struct ColorF;

	/**
		@brief インターフェイス
		@author 葉迩倭

		@note
		インターフェイスの基底クラス
	*/
	class Interface;

	/**
		@brief カーネル
	*/
	namespace Kernel
	{
		namespace Math
		{
			class Vector2;
			class Vector3;
			class Vector4;
			class VectorS;
			class Quaternion;
			class Matrix;
			class Camera;
		}

		namespace Collision
		{
			class AABB;
			class OBB;
			class Plane;
			class Sphere;
		}

		namespace File
		{
			class FileControl;
			class LogFile;
		}
	}

	/**
		@brief エンジン
	*/
	namespace Engine
	{
		class ICore;

		/**
			@brief ウィンドウ
		*/
		namespace Window
		{
			class IWindow;
		}

		/**
			@brief タスク
		*/
		namespace Task
		{
			class ITaskManager;
		}

		/**
			@brief ファイル
		*/
		namespace File
		{
			class IManager;
			class IPackFile;
			class IStreamFile;
			class IFile;
		}

		/**
			@brief グラフィック
		*/
		namespace Graphics
		{
			/**
				@brief バッファロックフラグ
			*/
			enum eLock;

			class IManager;

			/**
				@brief ステート
			*/
			namespace State
			{
				class IRenderState;
			}

			/**
				@brief シンプル
			*/
			namespace Simple
			{
				class ILineRenderer;
				class ISpriteRenderer;
				class ISpriteRenderer3D;
				class ITriangleRenderer;
				class ITextRenderer;
			}

			/**
				@brief リソース
			*/
			namespace Resource
			{
				class ITexture;
				class IShaderConstantBuffer;
				class IGeometryShader;
				class IVertexShader;
				class IVertexLayout;
				class IVertexBuffer;
				class IIndexBuffer;
				class IPixelShader;
				class IMaterialPlugin;
				class IMaterialListener;
				class IFileLoadListener;
				class IDrawObject;
				class IMaterial;
				class IRenderTable;
				class ILocalResource;
				class IRootMotion;

				/**
					@brief SMFモデル
				*/
				namespace SMF
				{
					class IConstraint;
					class INode;
					class IModel;
					class IModelController;
					class IMotion;
					class IMotionController;
					class IMotionScheduler;
				}

				/**
					@brief STMモデル
				*/
				namespace STM
				{
					class IModelController;
				}

				/**
					@brief テキスト
				*/
				namespace Text
				{
					class ITextData;
				}

				/**
					@brief ポリゴンライン
				*/
				namespace PolyLine
				{
					class IPolyLineController;
				}

				/**
					@brief スプライト
				*/
				namespace Sprite
				{
					class ISpriteController;
				}

				/**
					@brief プリミティブ
				*/
				namespace Primitive
				{
					class IPrimitiveController;
				}

				/**
					@brief パーティクル
				*/
				namespace Particle
				{
					struct SParameter;
					class IParticleController;
					class IVolumeParticleController;
					class IEnhancedParticleController;
				}
			}
		}

		/**
			@brief レンダラー
		*/
		namespace Renderer
		{
			class IManager;

			/**
				@brief 標準実装
			*/
			namespace Standard
			{
				struct SMaterialOption;
				class IRenderer;

				namespace Material
				{
					namespace Standard
					{
						class IMaterial;
					}

					namespace Water
					{
						class IMaterial;
					}
				}
			}
		}

		/**
			@brief サウンド
		*/
		namespace Sound
		{
			class IManager;

			namespace Resource
			{
				class IStaticSound;
				class IStreamSound;
			}
		}

		/**
			@brief 入力デバイス
		*/
		namespace Input
		{
			/**
				@brief ボタンの状態
				@author 葉迩倭
			*/
			enum eButtonState;

			/**
				@brief 仮想キーコード
				@author 葉迩倭
			*/
			enum eKeyCode;

			class IManager;
			class IInputController;
			class IJoystick;
			class IKeyboard;
			class IMouse;
		}

		/**
			@brief ネットワーク
		*/
		namespace Network
		{
			/**
				@brief	ホスト情報
				@author 葉迩倭
			*/
			struct SHostInfo;

			class IManager;

			/**
				@brief TCP通信
			*/
			namespace TCP
			{
				class IClient;
				class IServer;
				class IClientOfServer;
				class IServerReciver;
				class IServerSender;
			}

			/**
				@brief UDP通信
			*/
			namespace UDP
			{
				class IConnect;
			}
		}

		/**
			@brief 物理
		*/
		namespace Dynamics
		{
			class IManager;

			namespace Body
			{
				class IBody;
				class IDynamicsBody;
				class IBox;
				class ICapsule;
				class ICharaProxy;
				class ICharaProxySimple;
				class IPlane;
				class ISphere;
				class ITriMesh;
				class ITriggerBox;
				class ICompound;
				class ICollisionBody;
				class ICollisionSphere;
				class ICollisionCapsule;
				class ICollisionBox;
				class ICollisionTriMesh;
				class ISoftBody;
				class IRope;

				/**
					@brief キャラクタのボディの種類
					@author 少佐
				*/
				enum eProxyType;

				/**
					@brief ボディの種類
					@author 葉迩倭
				*/
				enum eBodyType;

				/**
					@brief 接触点情報
					@author 葉迩倭
				*/
				struct SContactInfo;

				/**
					@brief 複合オブジェクト
					@author 葉迩倭
				*/
				struct CompoundShape;

				/**
					@brief 複合オブジェクト球
					@author 葉迩倭
				*/
				struct CompoundShapeSphere;

				/**
					@brief 複合オブジェクトカプセル
					@author 葉迩倭
				*/
				struct CompoundShapeCapsule;

				/**
					@brief 複合オブジェクト箱
					@author 葉迩倭
				*/
				struct CompoundShapeBox;
			}

			/**
				@brief ジョイント
			*/
			namespace Joint
			{
				class IJoint;
				class ISliderJoint;
				class IHingeJoint;
				class IPointJoint;
				class IDofSpringJoint;
			}
		}

		/**
			@brief グラフィカルユーザーインターフェイス
		*/
		namespace GUI
		{
			class IManager;
			class IHelper;

			/**
				@brief GUIコントロール
			*/
			namespace Control
			{
				class IControl;
				class IIme;
				class IWindow;
				class IButton;
				class IProgressBar;
				class ISliderBar;
				class IScrollBar;
				class ILabel;
				class IGroupBox;
				class ICheckBox;
				class IListBox;
				class IComboBox;
				class IEditBox;
				class ITextBox;
				class IDialog;
				class IMenuBar;
				class IMenuButton;
				class IMenuList;
			}
		}
	}

	namespace Plugin
	{
		namespace File
		{
			/**
				@brief Cryptプラグインインターフェイス
				@author 葉迩倭
			*/
			class ICrypt;

			typedef ICrypt* (__stdcall* CreateCryptInterfaceProc)( const char* );
		}
	}
}