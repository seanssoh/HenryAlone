// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSColorManip.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSColorManip : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSColorManip(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Input Color"))
        FExpressionInput ColorIn;

    //UPROPERTY(meta = (RequiredInput = "false", ToolTip = "HSV Color Shift"))
    //    FExpressionInput HsvDelta;
    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Desat Color"))
            FExpressionInput Desat;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "RGB Gamma"))
        FExpressionInput Gamma;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "RGB Tint"))
        FExpressionInput Tint;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "RGB Bias"))
        FExpressionInput Bias;

    //UPROPERTY(EditAnywhere, Category = OSSColorManip, meta = (OverridingInputProperty = "HsvDelta"))
    //    float ConstHsvDelta;
    UPROPERTY(EditAnywhere, Category = OSSColorManip, meta = (OverridingInputProperty = "Desat"))
    float ConstDesat;

    UPROPERTY(EditAnywhere, Category = OSSColorManip, meta = (OverridingInputProperty = "Gamma"))
    FLinearColor ConstGamma;

    UPROPERTY(EditAnywhere, Category = OSSColorManip, meta = (OverridingInputProperty = "Tint"))
    FLinearColor ConstTint;

    UPROPERTY(EditAnywhere, Category = OSSColorManip, meta = (OverridingInputProperty = "Bias"))
    FLinearColor ConstBias;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("ColorManip"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("ColorManip"); OutToolTip.Add(ret); }
#endif

	
	
};
