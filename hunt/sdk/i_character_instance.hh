#pragma once
#include "i_skeleton_pose.hh"
#include "i_default_skeleton.hh"

class i_character_instance
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
	virtual i_skeleton_pos* get_i_skeleton_pose() = 0;
	virtual void Function17() = 0; //virtual ISkeletonPose* GetISkeletonPose() = 0;
	virtual const i_skeleton_pos* get_i_skeleton_pose() const = 0;
	virtual void Function19() = 0;
	virtual i_default_skeleton& get_i_defualt_skeleton() = 0;
	virtual const i_default_skeleton& get_i_default_skeleton() const = 0;
};