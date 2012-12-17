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
        //Haveing this class declared both in ItterationOne and 
        //ItterationTwo namespaces makes no sence. Only done to 
        //show that it is fully possible to have the same class
        //or function declarations in different namspaces. That
        //the namespace makes each declaration unique.
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