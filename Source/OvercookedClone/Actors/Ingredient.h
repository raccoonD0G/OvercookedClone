// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recipe.h"
#include "Ingredient.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AIngredient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Ingredient")
	void Server_SetIngredientState(EIngredientState NewIngredientState);

	FORCEINLINE EIngredientType GetIngredientType() const { return IngredientType; }
	FORCEINLINE EIngredientState GetIngredientState() const { return IngredientState; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UTextRenderComponent> TextComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EIngredientType IngredientType;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EIngredientState IngredientState;
	
};
