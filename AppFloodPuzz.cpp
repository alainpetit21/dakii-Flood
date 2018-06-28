#include "lib.h"
#include "libTypes.h"
#include "libMacros.h"
#include "AppFloodPuzz.h"

#include "CtxTitle.h"
#include "CtxGame.h"
#include "CtxScore.h"

CAppFloodPuzz	*g_TheAppFloodPuzz;

CAppFloodPuzz::CAppFloodPuzz():
CApp("AppFloodPuzz.application")
{

}

void
CAppFloodPuzz::OnPostCreate(void)
{
	Init(MAX_CTX);

	RegisterContext(CTX_TITLE, new CCtxTitle("CtxTitle.context"));
	RegisterContext(CTX_GAME, new CCtxGame(0));
	RegisterContext(CTX_SCORE, new CCtxScore("CtxScore.context"));

	m_curLevel= 0;

	SetCurContext(CTX_TITLE);

	CApp::OnPostCreate();
}

CApp*
newGameApp(void)
{
	return g_TheAppFloodPuzz= new CAppFloodPuzz();
}


ENTRY_POINT("Flood Puzz!");
