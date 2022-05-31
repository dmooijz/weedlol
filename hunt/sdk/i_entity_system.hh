#pragma once
#include "i_entity.hh"
#include "../cheat/addresses/addr.hh"

class i_entity_it {
public:
	virtual ~i_entity_it() {}
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual bool IsEnd() = 0;
	virtual i_entity* Next() = 0;
	virtual i_entity* This() = 0;
	virtual void MoveFirst() = 0;
};

class i_entity_system
{
public:
	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual void func7() = 0;
	virtual void func8() = 0;
	virtual void func9() = 0;
	virtual void func10() = 0;
	virtual void func11() = 0;
	virtual void func12() = 0;
	virtual void func13() = 0;
	virtual void func14() = 0;
	virtual void func15() = 0;
	virtual void func16() = 0;
	virtual void func17() = 0;
	virtual void func18() = 0;
	virtual void get_entity_iterator(i_entity_it**) = 0;
	static i_entity_system* get_i_entity_system() { return *reinterpret_cast<i_entity_system**>(addr::i_entity_system); };
};