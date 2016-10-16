// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSSmoothMin.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSSmoothMin : public UMaterialExpression
{
	GENERATED_BODY()
	

    UMaterialExpressionOSSSmoothMin(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstA' if not specified"))
        FExpressionInput A;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstB' if not specified"))
        FExpressionInput B;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstK' if not specified"))
        FExpressionInput K;

    /** only used if A is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSSMin, meta = (OverridingInputProperty = "A"))
    float ConstA;

    /** only used if B is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSSMin, meta = (OverridingInputProperty = "B"))
    float ConstB;

    /** only used if K is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSSMin, meta = (OverridingInputProperty = "K"))
    float ConstK;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("SMin"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("SMin"); OutToolTip.Add(ret); }
#endif

	
	
};
