// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/TraversalScoring/NGPObstacleActor.h"

#include "Systems/TraversalScoring/NGPTraversalDeveloperSettings.h"

#define NGP_OBSTACLE_CHANNEL ECC_GameTraceChannel1


ANGPObstacleActor::ANGPObstacleActor()
{
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	SetRootComponent(ObstacleMesh);

	ObstacleMesh->SetCollisionObjectType(ECC_WorldDynamic);
	ObstacleMesh->SetCollisionResponseToChannel(NGP_OBSTACLE_CHANNEL, ECR_Overlap);
}

int32 ANGPObstacleActor::GetPoints_Implementation() const
{
	if (Points > 0)
	{
		return Points;
	}
	
	const UNGPTraversalDeveloperSettings* Settings = GetDefault<UNGPTraversalDeveloperSettings>();
	return Settings->DefaultObstaclePoints;
}
