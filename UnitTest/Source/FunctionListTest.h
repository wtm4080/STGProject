#pragma once


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace FunctionListTest
{
	class TestClass
	{
	public:
		bool SetFlag1()
		{
			flag1 = true;

			return retFlag1;
		}
		bool SetFlag2()
		{
			flag2 = true;

			return retFlag2;
		}

		bool GetFlag1() const { return flag1; }
		bool GetFlag2() const { return flag2; }

		void ClearFlags()
		{
			flag1 = false;
			flag2 = false;
		}

		void SetRetFlag1( bool flag ) { retFlag1 = flag; }
		void SetRetFlag2( bool flag ) { retFlag2 = flag; }

		bool DefaultFunc()
		{
			defaultFuncFlag = true;

			return defaultFuncRetFlag;
		}
		bool GetDefaultFuncFlag() const { return defaultFuncFlag; }
		void ClearDefaultFuncFlag() { defaultFuncFlag = false; }
		void SetDefaultFuncRetFlag( bool flag ) { defaultFuncRetFlag = flag; }

	private:
		bool
			flag1, 
			flag2, 
			retFlag1, 
			retFlag2, 
			defaultFuncFlag, 
			defaultFuncRetFlag;
	};
}