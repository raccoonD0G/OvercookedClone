#include "Characters/StateAICharacter.h"
#include "Net/UnrealNetwork.h"

AStateAICharacter::AStateAICharacter()
{
	bReplicates = true;
}

void AStateAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AStateAICharacter, AIState);
}

AAIState* AStateAICharacter::GetAIState() const
{
	return AIState;
}

void AStateAICharacter::SetAIState(AAIState* NewAIState)
{
	AIState = NewAIState;
}
