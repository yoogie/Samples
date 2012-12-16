#include "entity.h"

//The namespaces in this file does not make much sense,
//their purpose is only to show inheritance between namespaces.
namespace Example
{
	namespace Alfa
	{

		BaseEntity::BaseEntity(const int unitId, const std::string& name) : mUnitId(unitId), mName(name)
		{
		}

		BaseEntity::~BaseEntity()
		{
		}

		std::string BaseEntity::getName() const
		{
			return mName;
		}
		
		int BaseEntity::getUnitId() const
		{
			return mUnitId;
		}
	}

	namespace ItterationOne
	{

		EntityImpl::EntityImpl(const int unitId, const std::string& name) : Alfa::BaseEntity(unitId, name)
		{
		}

		EntityImpl::~EntityImpl()
		{
		}
	}

	namespace ItterationTwo
	{

		EntityImpl::EntityImpl(const int unitId, const std::string& name) : Alfa::BaseEntity(unitId, name)
		{
		}

		EntityImpl::~EntityImpl()
		{
		}
	}
}
