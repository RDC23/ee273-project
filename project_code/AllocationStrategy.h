#pragma once
class Database; //forward declare the database to prevent circular dependency

//encapsulates different allocate strategies for runtime flexibility for admin class + decoupling of algorithm from class that uses 
//https://refactoring.guru/design-patterns/strategy/cpp/example

class AllocationStrategy {

public:
	enum Strategy {    //enum used for saving the strategy to csv. Analagous to using a unique ID for the other classes.
		GALESHAPELY,
		SIMPLE,
	};

	virtual void allocate(Database* db) = 0;
};

class galesShapely : public AllocationStrategy {

public:
	void allocate(Database* db) override;   //implement this complex algorithm if time permits
};

class simpleAllocate : public AllocationStrategy {

public:
	void allocate(Database* db) override;
};