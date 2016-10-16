// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSSmoothstep.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSSmoothstep : public UMaterialExpression
{
	GENERATED_BODY()
	
	
    UMaterialExpressionOSSSmoothstep(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstX' if not specified"))
    FExpressionInput X;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstM' if not specified"))
    FExpressionInput A;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstN' if not specified"))
    FExpressionInput B;

    /** only used if X is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "X"))
    float mConstX;

    /** only used if M is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "A"))
    float mConstA;

    /** only used if N is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "B"))
    float mConstB;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Smoothstep"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Smoothstep"); OutToolTip.Add(ret); }
#endif

	
};
