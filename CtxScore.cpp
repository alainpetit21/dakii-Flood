#include "lib.h"
#include "libTypes.h"
#include "libMacros.h"
#include "libMngInput.h"
#include "dfcApp.h"
#include "CtxScore.h"

void 
CCtxScore::Init(void)
{
	SetNbChilds(64);
}

void 
CCtxScore::Activate(void)
{
	CContext::Activate();
}


void 
CCtxScore::Deactivate(void)
{
	CContext::Deactivate();
}

void 
CCtxScore::Manage(unsigned long p_nTimeTick)
{
	CContext::Manage(p_nTimeTick);
}

void 
CCtxScore::Update(void)
{
	
	CContext::Update();
}
