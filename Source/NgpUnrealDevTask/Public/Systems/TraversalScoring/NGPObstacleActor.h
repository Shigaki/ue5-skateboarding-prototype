// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NGPObstacleInterface.h"
#include "GameFramework/Actor.h"
#include "NGPObstacleActor.generated.h"

UCLASS()
class NGPUNREALDEVTASK_API ANGPObstacleActor : public AActor, public INGPObstacleInterface
{
	GENERATED_BODY()

	public:
		ANGPObstacleActor();

		virtual int32 GetPoints_Implementation() const override;
		
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
		int32 Points = -1;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TObjectPtr<UStaticMeshComponent> ObstacleMesh;
};
