#pragma once
#include "Engine/Reflection/Reflection.h"
#include "Engine/RawPointerTracker.h"
#include "Engine/Networking/NetworkEnums.h"

#include "mathfu/vector.h"

class BaseObject : public RawPointerTrackableObject
{
public:
	DefineClassMetaFunctionGetters(BaseObject)

	virtual bool Initialize() override { return RawPointerTrackableObject::Initialize(); }
	void InitializeNetworkID(unsigned int newNetworkID);
	void InitializeOwningClientID(unsigned int newClientID);
	void RegisterSelfAsNetworked();

	void RegisterNetworkedVariable(const AuthorityType authorityType, ClassMetaData<BaseObject>::MetaVariable* metaVariable, MetaFunction<BaseObject>* onRepMetaFunction = nullptr);
	unsigned int GetNetworkID() const { return networkID; }
	unsigned int GetOwningClientID() const { return owningClientID; }
	bool HasValidNetworkID() const { return networkID != 0; }
	bool HasValidOwningClientID() const { return owningClientID != 0; }

private:
	unsigned int networkID = 0;
	unsigned int owningClientID = 0;
};