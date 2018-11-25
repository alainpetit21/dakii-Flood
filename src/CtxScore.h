#ifndef CTX_SCORE_H
#define CTX_SCORE_H

#include "dfcContext.h"
#include "dfcEntity.h"
#include "dfc3DEntity.h"
#include "dfcLabel.h"

class CCtxScore : public CContext
{
public:
	CCtxScore(const char* p_pRes):CContext(p_pRes){};

	virtual void Init(void);
	virtual void Activate(void);
	virtual void Deactivate(void);
	virtual void Manage(unsigned long p_nTimeTick);
	virtual void Update(void);

};

#endif //CTX_SCORE_H
