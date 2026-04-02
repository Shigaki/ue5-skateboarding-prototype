// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NGPTraversalViewModel.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class NGPUNREALDEVTASK_API UNGPTraversalViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
	/** Friends */
    friend class UNGPTraversalScoreComponent;
    friend class ANGPPlayerState;

    public:
        UFUNCTION(BlueprintPure, FieldNotify)
        int32 GetTotalScore() const;

        UFUNCTION(BlueprintPure, FieldNotify)
        int32 GetLastEarnedPoints() const;

        UFUNCTION(BlueprintPure, FieldNotify)
        int32 GetComboMultiplier() const;

        UFUNCTION(BlueprintPure, FieldNotify)
        float GetComboTimeRemaining() const;

        UFUNCTION(BlueprintPure, FieldNotify)
        bool GetIsComboActive() const;
            
        UFUNCTION(BlueprintPure, FieldNotify)
        float GetComboPercent() const;

	protected:
	    void SetTotalScore(int32 NewValue);

	    void SetLastEarnedPoints(int32 NewValue);

	    void SetComboMultiplier(int32 NewValue);

	    void SetComboTimeRemaining(float NewValue);

	    void SetComboTimeMax(float NewValue);

	private:
	    UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	    int32 TotalScore = 0;

	    UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	    int32 LastEarnedPoints = 0;

	    UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	    int32 ComboMultiplier = 1;

	    UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	    float ComboTimeRemaining = 0.f;

	    UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	    float ComboTimeMax = 0.f;
};
