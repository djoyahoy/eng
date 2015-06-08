#ifndef __PROP_STATE_H__
#define __PROP_STATE_H__

#include "stage/zone.h"
#include "hero/spirit.h"
#include "actor/spirit.h"

namespace prop
{
  struct PropState
  {
    virtual void enter(actor::Spirit&) { }
    virtual void exit(actor::Spirit&) { }
    virtual void update(actor::Spirit&,
			const stage::Zone&,
			hero::Spirit&) = 0;
  };

  typedef std::vector<std::unique_ptr<PropState>> PropStateVec;
}

#endif
