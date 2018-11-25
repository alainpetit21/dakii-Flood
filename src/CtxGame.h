#ifndef CTX_GAME_H
#define CTX_GAME_H

#include "dfcContext.h"
#include "dfcEntity.h"
#include "dfc3DEntity.h"
#include "dfcLabel.h"

class CCtxGame : public CContext
{
public:
	CCtxGame(const char* p_pRes):CContext(p_pRes){};

	virtual void Init(void);
	virtual void Activate(void);
	virtual void Deactivate(void);
	virtual void Manage(unsigned long p_nTimeTick);
	virtual void Update(void);
	virtual void UpdatePercentage(void);

	void TimerFunction(void);

	CEntity		*m_pBucket[16];
	CLabel		*m_pFrameRate;
	CLabel		*m_pLblTime;
	CLabel		*m_pLblBucket[16];
	CLabel		*m_pLblPercentage;

	char		tickDiff[128];
	u8			m_delay;

	u8			m_colorPicked;
	SDL_Color	*m_palettes;
	SDL_Surface	*m_pImage;
	SDL_Surface	*m_pImageBackup;

	int			m_nLastOffsetOver;
	int			m_nLastOffsetClicked;

	int			m_delayPicture;
};

#endif //CTX_GAME_H
