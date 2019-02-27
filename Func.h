//
// Created by Víctor Navarro on 2/26/2019.
//

#ifndef FUNC_H
#define FUNC_H

#include "Delegate.h"

template<typename ... Args>
class Func : public Delegate<void(Args...)>
{
};

#endif
