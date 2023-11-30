#include "PCH.h"
#include "BTTaskNode_DetectPlayer.h"
#include "GameFramework/GameObject/Character.h"
#include <Assets/Scene/Scene.h>

BTTaskNode_DetectPlayer::BTTaskNode_DetectPlayer()
{
	DetectRange.AllowedTypes.push_back(EBlackBoardValType::Float);
}

BTTaskNode_DetectPlayer::BTTaskNode_DetectPlayer(const BTTaskNode_DetectPlayer& Other)
	:Super(Other)
	, DetectRange(Other.DetectRange)
{
}

BTTaskNode_DetectPlayer::~BTTaskNode_DetectPlayer()
{
}

ENodeStatus BTTaskNode_DetectPlayer::UpdateNode(float DeltaSeconds)
{
	float range = 0.f;
	DetectRange.GetBlackBoardValueAsFloat(m_Tree, OUT range);

	if (range != 0.f)
	{
		Character* Mon = m_Tree->GetControllerCharacter();
		Character* Player = Mon->GetOwningScene()->GetSceneInfo()->GetPlayerCharacter();
		float dist = SVector3::Distance(Mon->GetWorldLocationAsBottom(), Player->GetWorldLocationAsBottom());

		// Detect되었을 때 
		if (dist <= range)
			m_Status = ENodeStatus::Success;

		else
			m_Status = ENodeStatus::Failure;

	}
	else
		m_Status = ENodeStatus::Failure;

	return m_Status;
}