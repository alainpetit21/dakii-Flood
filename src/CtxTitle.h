#ifndef CTX_TITLE_H
#define CTX_TITLE_H

#include "dfcContext.h"
#include "dfcEntity.h"
#include "dfc3DEntity.h"
#include "dfcLabel.h"

class CCtxTitle : public CContext
{
public:
	CCtxTitle(const char* p_pRes):CContext(p_pRes){};

	virtual void Init(void);
	virtual void Activate(void);
	virtual void Deactivate(void);
	virtual void Manage(unsigned long p_nTimeTick);
	virtual void Update(void);
};

#endif //CTX_TITLE_H
