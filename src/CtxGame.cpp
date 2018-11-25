#include "lib.h"
#include "libTypes.h"
#include "libMacros.h"
#include "libMngResIO.h"
#include "libMngInput.h"
#include "dfcApp.h"
#include "CtxGame.h"


#include "AppFloodPuzz.h"

const char* pWorld[]=
{
	"CtxFloodPuzz01.context",
	"CtxFloodPuzz02.context",
	"CtxFloodPuzz03.context",
	"CtxFloodPuzz04.context",
	"CtxFloodPuzz05.context",
	"CtxFloodPuzz06.context",
	"CtxFloodPuzz07.context",
	"CtxFloodPuzz08.context",
	"CtxFloodPuzz09.context",
	"CtxFloodPuzz10.context",
};


void
CCtxGame::Init(void)
{
	SetNbChilds(64);
}

void
CCtxGame::Activate(void)
{
CMngGraphic	*pRenderer	= GetMngGraphic();
int			i;

	LoadInstance(pWorld[g_TheAppFloodPuzz->m_curLevel]);

	SetMouse((CEntity*)FindByID("EntCursor"));

	//Find Layer
	CBackgroundLayer	*pBackLayer= ((CBackgroundLayer*)FindByID("BkFloodPuzz_1"));

	m_pImage= (SDL_Surface*)pBackLayer->m_bitmap;
	SDL_SetColorKey(m_pImage, 0, 0);

	m_pImageBackup= (SDL_Surface*)pRenderer->NewBitmap(pBackLayer->m_size[0], pBackLayer->m_size[1], 1);
	pRenderer->DrawBitmap(m_pImageBackup, 0, 0, pBackLayer->m_size[0], pBackLayer->m_size[1], 0, 1.0, 1, m_pImage);

	//Find 16 color of the images
	m_palettes= m_pImage->format->palette->colors;

	//Create Bucket
	for(i= 0; i < 16; ++i){
		m_pBucket[i]= new CEntity;
		m_pBucket[i]->m_arFrames= new TRuntimeFrame[1];
		m_pBucket[i]->m_arFrames[0].nWidth	= 25;
		m_pBucket[i]->m_arFrames[0].nHeight	= 25;
		m_pBucket[i]->m_arFrames[0].nHotSpotX= 12;
		m_pBucket[i]->m_arFrames[0].nHotSpotY= 12;

		m_pBucket[i]->m_arFrames[0].pData	= pRenderer->NewBitmap(m_pBucket[i]->m_arFrames[0].nWidth, m_pBucket[i]->m_arFrames[0].nHeight, 1);
		pRenderer->FillBitmap(m_pBucket[i]->m_arFrames[0].pData, ((m_palettes[i].r)<<16)|((m_palettes[i].g)<<8)|((m_palettes[i].b)<<0));

		m_pBucket[i]->m_nbState= 1;
		m_pBucket[i]->m_arState= new TRuntimeFrame*[2];
		m_pBucket[i]->m_arState[0]	= &m_pBucket[i]->m_arFrames[0];
		m_pBucket[i]->m_arState[1]	= &m_pBucket[i]->m_arFrames[1];
		m_pBucket[i]->m_pCurAnim	= m_pBucket[i]->m_arState[m_pBucket[i]->m_curState= 0];
		m_pBucket[i]->m_indexFrame	= 0.0f;
		m_pBucket[i]->m_arSpeed		= new u32[2];
		m_pBucket[i]->m_speed		= 0;

		m_pBucket[i]->SetPos(250, -212 + i * 25, 110);

		char txtId[32];

		sprintf(txtId, "BUCKET");
		m_pBucket[i]->SetTextID(txtId);
		AddChild(m_pBucket[i], false);
	}

	//Create FPS Label
	m_pFrameRate= new CLabel;
	m_pFrameRate->SetPos(-512, -384, 0);
	m_pFrameRate->SetTextID("FPS");
	m_pFrameRate->SetText("0.0");
	m_pFrameRate->SetFont(CFont::Find("Font8.font"));
	AddChild(m_pFrameRate, false);

	//Create UI Labels
	for(i= 0; i < 16; ++i){
		char txtId[16];

		memset(txtId, 0, 16);
		sprintf(txtId, "BUCKET");

		m_pLblBucket[i]= new CLabel;
		m_pLblBucket[i]->SetPos(275, -212 + i * 25, 110);
		m_pLblBucket[i]->SetTextID(txtId);
		m_pLblBucket[i]->SetText("x 00");
		m_pLblBucket[i]->SetFont(CFont::Find("Font8.font"));
		AddChild(m_pLblBucket[i], false);
	}

	m_pLblTime= new CLabel;
	m_pLblTime->SetPos(-300, 212, 110);
	m_pLblTime->SetTextID("LBL_TIMER");
	m_pLblTime->SetText("00 00");
	m_pLblTime->SetFont(CFont::Find("Font8.font"));
	AddChild(m_pLblTime, false);

	m_pLblPercentage= new CLabel;
	m_pLblPercentage->SetPos(190, 212, 110);
	m_pLblPercentage->SetTextID("LBL_TIMER");
	m_pLblPercentage->SetText("00.00 ");
	m_pLblPercentage->SetFont(CFont::Find("Font8.font"));
	AddChild(m_pLblPercentage, false);

	memset(g_TheAppFloodPuzz->m_nbUseBucket, 0, sizeof(int)*16);
	m_delay= 0;
	m_nLastOffsetOver= -1;
	m_nLastOffsetClicked= 0;
	m_colorPicked= m_palettes[0].r;
	m_colorPicked|= m_palettes[0].g<<8;
	m_colorPicked|= m_palettes[0].b<<16;

	m_delayPicture= 100;
	g_TheAppFloodPuzz->m_nbSeconds= 0;

	UpdatePercentage();
	AddTimer(1000, (void (CContext::*)(void))&CCtxGame::TimerFunction);
}

void
CCtxGame::TimerFunction(void)
{
int nMinute;
int nSecondReminder;

	g_TheAppFloodPuzz->m_nbSeconds++;
	nMinute			= g_TheAppFloodPuzz->m_nbSeconds/60;
	nSecondReminder	= g_TheAppFloodPuzz->m_nbSeconds - (nMinute*60);
	m_pLblTime->Format("%02d %02d", nMinute, nSecondReminder);
}

void
CCtxGame::UpdatePercentage(void)
{
CMngGraphic	*pRenderer		= GetMngGraphic();
u8			*pLockedImage	= (u8*)pRenderer->LockSurface(m_pImage);
int			p				= pRenderer->GetLockedPitch();
int			nbOccurence[16];
int			highest			= -1;
int			i, j, k;

	memset(nbOccurence, 0, sizeof(int)*16);

	//Search each color for how many occurrence
	for(i= 0; i < 66; ++i){
		for(j= 0; j < 50; ++j){
			nbOccurence[pLockedImage[(j<<3)*p+(i<<3)]]++;
		}
	}

	pRenderer->UnLockSurface(m_pImage, (u32*)pLockedImage);

	//Find highest
	for(k= 0; k < 16; ++k){
		if(nbOccurence[k] > highest)
			highest		= nbOccurence[k];
	}

	//Calculate Percentage
	m_pLblPercentage->Format("%02.2f", float(highest/(66.0f*50.0f)*100.0f));

	//Congratulation
	if(highest == 66*50){
		;
	}
}

void
CCtxGame::Deactivate(void)
{
CMngGraphic	*pRenderer		= GetMngGraphic();

	pRenderer->FreeBitmap((void**)&m_pImageBackup);
	pRenderer->FreeBitmap((void**)&m_pImage);

	CContext::Deactivate();
}

void
CCtxGame::Manage(unsigned long p_nTimeTick)
{
CMngGraphic	*pRenderer	= GetMngGraphic();
CMngInput	*mngInput= GetMngInput();
s32			mouseX, mouseY;

	if(!(m_delayPicture--)){
		((CBackgroundLayer*)FindByID("BkFloodPuzz_2"))->Hide();

	}

	if(mngInput->IsLogicKeyDown(IK_ESCAPE))
		System_Quit();

	if(mngInput->IsLogicKeyDown(IK_ADD))
	{
		if(++g_TheAppFloodPuzz->m_curLevel > 9)
			g_TheAppFloodPuzz->m_curLevel= 9;

		g_TheApp->SetCurContext(g_TheApp->GetCurContextID());
	}
	if(mngInput->IsLogicKeyDown(IK_SUBTRACT))
	{
		if(--g_TheAppFloodPuzz->m_curLevel < 0)
			g_TheAppFloodPuzz->m_curLevel= 0;

		g_TheApp->SetCurContext(g_TheApp->GetCurContextID());
	}


	//If over a Entity ... calculate its offset .. Get the color .. and make all color in image inverted
	mngInput->GetMousePos(mouseX, mouseY);

	if((mouseX > 235) && (mouseX < 265)){
		if((mouseY > -225) && (mouseY <175)){
			int offset= (mouseY - (-225)) / 25;
			if(m_nLastOffsetOver != offset){

				if(m_nLastOffsetOver != -1){
					m_palettes[m_nLastOffsetOver].r= 0xFF - m_palettes[m_nLastOffsetOver].r;
					m_palettes[m_nLastOffsetOver].g= 0xFF - m_palettes[m_nLastOffsetOver].g;
					m_palettes[m_nLastOffsetOver].b= 0xFF - m_palettes[m_nLastOffsetOver].b;
				}

				m_palettes[offset].r= 0xFF - m_palettes[offset].r;
				m_palettes[offset].g= 0xFF - m_palettes[offset].g;
				m_palettes[offset].b= 0xFF - m_palettes[offset].b;

//				SDL_SetColors(m_pImage, m_palettes, 0, 16);
				SDL_SetPaletteColors(m_pImage->format->palette, m_palettes, 0, 16);
				m_nLastOffsetOver= offset;
			}
		//else put back original Image
		}else if(m_nLastOffsetOver != -1){
			m_palettes[m_nLastOffsetOver].r= 0xFF - m_palettes[m_nLastOffsetOver].r;
			m_palettes[m_nLastOffsetOver].g= 0xFF - m_palettes[m_nLastOffsetOver].g;
			m_palettes[m_nLastOffsetOver].b= 0xFF - m_palettes[m_nLastOffsetOver].b;
//			SDL_SetColors(m_pImage, m_palettes, 0, 16);
			SDL_SetPaletteColors(m_pImage->format->palette, m_palettes, 0, 16);
			m_nLastOffsetOver= -1;
		}
	}
	else if(m_nLastOffsetOver != -1){
		m_palettes[m_nLastOffsetOver].r= 0xFF - m_palettes[m_nLastOffsetOver].r;
		m_palettes[m_nLastOffsetOver].g= 0xFF - m_palettes[m_nLastOffsetOver].g;
		m_palettes[m_nLastOffsetOver].b= 0xFF - m_palettes[m_nLastOffsetOver].b;
//		SDL_SetColors(m_pImage, m_palettes, 0, 16);
		SDL_SetPaletteColors(m_pImage->format->palette, m_palettes, 0, 16);
		m_nLastOffsetOver= -1;
	}

	//If MouseDown ... If over an entity Pick the color
	if(mngInput->IsMouseLogicKeyDown(0)){
		if(m_nLastOffsetOver != -1){
			m_colorPicked= m_nLastOffsetClicked= m_nLastOffsetOver;
		}else if((mouseX > -306) && (mouseX < 220) &&
			     (mouseY > -226) && (mouseY < 172)){
			int xConv= mouseX + 320 - 16 + 1;
			int yConv= mouseY + 240 - 16 + 1;

			pRenderer->FloodFill(m_pImage, s32(xConv), s32(yConv), m_colorPicked);
			pRenderer->DrawBitmap(m_pImageBackup, 0, 0, 528, 400, 0, 1.0, 1, m_pImage);

			UpdatePercentage();

			g_TheAppFloodPuzz->m_nbUseBucket[m_nLastOffsetClicked]++;
			m_pLblBucket[m_nLastOffsetClicked]->Format("x %02d", g_TheAppFloodPuzz->m_nbUseBucket[m_nLastOffsetClicked]);
		}
	}
	CContext::Manage(p_nTimeTick);
}

void
CCtxGame::Update(void)
{

	CContext::Update();
}
