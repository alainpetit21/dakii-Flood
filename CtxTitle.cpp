#include "lib.h"
#include "libTypes.h"
#include "libMacros.h"
#include "libMngInput.h"
#include "dfcApp.h"
#include "CtxTitle.h"
#include "AppFloodPuzz.h"


void 
CCtxTitle::Init(void)
{
	SetNbChilds(64);
}

void 
CCtxTitle::Activate(void)
{
	CContext::Activate();

	SetMouse((CEntity*)FindByID("EntCursor"));
}


void 
CCtxTitle::Deactivate(void)
{
	CContext::Deactivate();
}

void 
CCtxTitle::Manage(unsigned long p_nTimeTick)
{
CMngInput	*mngInput= GetMngInput();

	CContext::Manage(p_nTimeTick);

	//If MouseDown ... If over an entity Pick the color
	if(mngInput->IsMouseLogicKeyDown(0)){
		g_TheApp->SetCurContext(CTX_GAME);
	}
}

void 
CCtxTitle::Update(void)
{
	
	CContext::Update();
}
