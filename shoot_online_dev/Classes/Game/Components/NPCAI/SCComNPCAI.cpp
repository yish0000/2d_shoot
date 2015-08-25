#include "SCComNPCAI.h"
#include "../SCComProperty.h"

bool SCComNPCAI::IsZombie()
{
    SCComProperty* pProperty = dynamic_cast<SCComProperty*>(m_pGameObj->getComponent(SC_COMPONENT_PROPERTY));
    return pProperty->IsZombie();
}