#include "PCH.h"
#include "Finalizer.h"

#include "Ctrl/STG/Configuration/Manager.h"

using namespace Game;
using namespace Ctrl::Scene;


void Finalizer::Finalize()
{
	Ctrl::STG::Configuration::Manager::Release();
}