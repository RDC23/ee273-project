#pragma once
#include "User.h"

//https://refactoring.guru/design-patterns/strategy/cpp/example
//encapsulates different allocate strategies for runtime flexibility for admin class

class AllocationStrategy {

public:
	virtual void allocate() = 0;
};


class galesShapely : public AllocationStrategy {

public:
	void allocate() override {};   //implement this complex algorithm if time permits

};

class simpleAllocate : public AllocationStrategy {

public:
	void allocate() override {};

};