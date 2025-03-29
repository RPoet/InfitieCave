// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowSystem.h"


static TAutoConsoleVariable<int32> CVarFlowIndex(
	TEXT("g.FlowIndex"),
	-1,
	TEXT(""),
	ECVF_Default
);

ABootFlow::ABootFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}


ALoginFlow::ALoginFlow()
{
	PrimaryActorTick.bCanEverTick = false;
}


ALobbyFlow::ALobbyFlow()
{
	PrimaryActorTick.bCanEverTick = false;
}

AMathcingFlow::AMathcingFlow()
{
	PrimaryActorTick.bCanEverTick = false;
}

AFlowSystem::AFlowSystem()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlowSystem::BeginPlay()
{
	Super::BeginPlay();

	CurrentFlow = EStateFlow::EBootFlow;

	FConditionContext Context;
	Context.CurrentFlow = this->CurrentFlow;

	for (int32 i = 0; i < States.Num(); ++i)
	{
		if (!States[i])
		{
			continue;
		}

		const bool bCondition = States[i]->Condition(Context);

		if (bCondition)
		{
			CurrentState = States[i];
			CurrentState->Enter();
		}
	}
}


// Called every frame
void AFlowSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const int32 FlowCVar = CVarFlowIndex.GetValueOnGameThread();

	if (FlowCVar > 0)
	{
		CurrentFlow = (EStateFlow)FlowCVar;
	}

	FConditionContext Context;
	Context.CurrentFlow = this->CurrentFlow;

	check(CurrentState);
	
	// First check state transition
	if (CurrentState)
	{
		if (auto NewState = CurrentState->CheckStateTransition(Context))
		{
			CurrentState->Exit();
			NewState->Enter();
			CurrentState = NewState;
		}
	
		CurrentState->Update(this);
	}

	CVarFlowIndex->Set(INDEX_NONE, ECVF_SetByConsole);
}

