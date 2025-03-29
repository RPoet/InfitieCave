// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlowSystem.generated.h"


UENUM()
enum class EStateFlow : uint8
{
	EBootFlow,
	ELoginFlow,
	ELobbyFlow,
	EMathicFlow,
};


USTRUCT()
struct FConditionContext
{
	GENERATED_BODY()
	EStateFlow CurrentFlow;
};


UCLASS()
class INFINITECAVE_API AStateBase : public AActor
{
	GENERATED_BODY()
public:
	virtual bool Condition(const FConditionContext& Context) { return true; }
	virtual void Enter() {}
	virtual void Update(AFlowSystem* System) {}
	virtual void Exit() {}


	AStateBase* CheckStateTransition(const FConditionContext& Context)
	{
		for (int32 i = 0; i < SubStates.Num(); ++i)
		{
			if (SubStates[i] && SubStates[i]->Condition(Context))
			{
				return SubStates[i];
			}
		}

		return nullptr;
	}
protected:

	UPROPERTY(EditAnywhere, Category = State)
	TArray< AStateBase* > SubStates;
};


UCLASS()
class INFINITECAVE_API ABootFlow : public AStateBase
{
	GENERATED_BODY()
public:
	ABootFlow();

	virtual bool Condition(const FConditionContext& Context) override final 
	{ 
		return Context.CurrentFlow == EStateFlow::EBootFlow;
	}

	virtual void Enter() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Enter ABootFlow"));
	}

	virtual void Update(AFlowSystem* System) override final
	{
	}

	virtual void Exit() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Exit ABootFlow"));
	}

private:
};

UCLASS()
class INFINITECAVE_API ALoginFlow : public AStateBase
{
	GENERATED_BODY()
public:
	ALoginFlow();

	virtual bool Condition(const FConditionContext& Context) override final
	{
		return Context.CurrentFlow == EStateFlow::ELoginFlow;
	}

	virtual void Enter() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Enter ALoginFlow"));
	}

	virtual void Update(AFlowSystem* System) override final
	{
	}

	virtual void Exit() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Exit ALoginFlow"));
	}

private:
};

UCLASS()
class INFINITECAVE_API ALobbyFlow : public AStateBase
{
	GENERATED_BODY()
public:
	ALobbyFlow();

	virtual bool Condition(const FConditionContext& Context) override final
	{
		return Context.CurrentFlow == EStateFlow::ELobbyFlow;
	}


	virtual void Enter() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Enter ALobbyFlow"));
	}

	virtual void Update(AFlowSystem* System) override final
	{
	}

	virtual void Exit() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Exit ALobbyFlow"));
	}

private:
};

UCLASS()
class INFINITECAVE_API AMathcingFlow : public AStateBase
{
	GENERATED_BODY()
public:
	AMathcingFlow();

	virtual bool Condition(const FConditionContext& Context) override final
	{
		return Context.CurrentFlow == EStateFlow::EMathicFlow;
	}

	virtual void Enter() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Enter AMathcingFlow"));
	}

	virtual void Update(AFlowSystem* System) override final
	{
	}

	virtual void Exit() override final
	{
		UE_LOG(LogTemp, Log, TEXT("Exit AMathcingFlow"));
	}

private:
};



UCLASS()
class INFINITECAVE_API AFlowSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlowSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = State)
	EStateFlow CurrentFlow;

	UPROPERTY(EditAnywhere, Category = State)
	TArray<AStateBase*> States;

private:

	UPROPERTY()
	AStateBase* CurrentState;
};
