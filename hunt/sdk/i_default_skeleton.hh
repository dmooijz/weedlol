#pragma once
#include "defenition.hh"

class i_default_skeleton
{
public:
	virtual ~i_default_skeleton() {}
	virtual uint32 get_joint_count() const = 0;
	virtual int32  get_joint_parent_id_by_id(int32 id) const = 0;
	virtual int32  get_controller_id_by_id(int32 id) const = 0;
	virtual int32  get_joint_children_count_by_id(int32 id) const = 0;
	virtual int32  get_joint_child_id_at_index_by_id(int32 id, uint32 childIndex) const = 0;
	virtual int32  get_joint_id_by_crc32(uint32 crc32) const = 0;
	virtual uint32 get_joint_crc32_by_id(int32 id) const = 0;
	virtual const char* get_joint_name_by_id(int32 id) const = 0;
	virtual int32 get_joint_id_by_name(const char* name) const = 0;
};