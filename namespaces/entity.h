#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <sstream>

//The namespaces in this file does not make much sense,
//their purpose is only to show inheritance between namespaces.
namespace Example
{
	namespace Alfa
	{
		class BaseEntity
		{
		public: 
			BaseEntity(const int unitId, const std::string& name);
			virtual ~BaseEntity();
			std::string getName() const;
			int getUnitId() const;

		protected:
			int mUnitId;
			std::string mName;

		private:
			BaseEntity(); //private default ctor to avoid compiler created one
			BaseEntity(const BaseEntity& be); //private copy ctor to avoid compiler created one
			BaseEntity& operator=(const BaseEntity& rhs); //private assignement operator to avoid compiler created one
		};
	}

	namespace ItterationOne
	{
		class EntityImpl : public Alfa::BaseEntity
		{
		public:
			EntityImpl(const int unitId, const std::string& name);
			virtual ~EntityImpl();
		};
	}

	namespace ItterationTwo
	{
		class EntityImpl : public Alfa::BaseEntity
		{
		public:
			EntityImpl(const int unitId, const std::string& name);
			virtual ~EntityImpl();
		};		
	}
}

#endif