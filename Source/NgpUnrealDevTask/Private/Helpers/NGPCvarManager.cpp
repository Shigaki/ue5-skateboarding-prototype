#include "Helpers/NGPCvarManager.h"

TAutoConsoleVariable<bool> CVarTraversalDebug(
	TEXT("NGP.Debug.Traversal"),
	false,
	TEXT("Enable Traversal debug."),
	ECVF_Cheat
);