//
// Created by Víctor Navarro on 2/26/2019.
//

#ifndef ACTION_H
#define ACTION_H

#include "Delegate.h"

class Action : public Delegate<void()>
{
public:
	void Invoke()
	{
		for (const auto &function : functions) function();
	}
};


#endif ACTION_H
