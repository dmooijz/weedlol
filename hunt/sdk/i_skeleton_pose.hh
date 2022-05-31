#pragma once
#include "defenition.hh"
#include "../../utils/quat.hh"

class i_skeleton_pos
{
public:
	virtual void Function0() = 0;
	virtual void Function1() = 0;
	virtual void Function2() = 0;
	virtual void Function3() = 0;
	virtual void Function4() = 0;
	virtual void Function5() = 0;
	virtual void Function6() = 0;
	virtual void Function7() = 0;
	virtual void Function8() = 0;
	virtual void Function9() = 0;
	virtual void Function10() = 0;
	virtual void Function11() = 0;
	virtual void Function12() = 0;
	virtual void Function13() = 0;
	virtual void Function14() = 0;
	virtual void Function15() = 0;
	virtual void Function16() = 0;
	virtual void Function17() = 0;
	virtual void Function18() = 0;
	virtual void Function19() = 0;
	virtual void Function20() = 0;
	virtual void Function21() = 0;
	virtual void Function22() = 0;
	virtual void Function23() = 0;
	virtual const math::quat_t& get_abs_joint_by_id(int32 nJointID) const = 0;
	virtual const math::quat_t& get_rel_joint_by_id(int32 nJointID) const = 0;
};