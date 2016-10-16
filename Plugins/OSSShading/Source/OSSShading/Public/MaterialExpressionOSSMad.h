// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSMad.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSMad : public UMaterialExpression
{
	GENERATED_BODY()
	

    UMaterialExpressionOSSMad(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstX' if not specified"))
        FExpressionInput X;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstM' if not specified"))
        FExpressionInput M;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstN' if not specified"))
        FExpressionInput N;

    /** only used if X is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "X"))
        float mConstX;

    /** only used if M is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "M"))
        float mConstM;

    /** only used if N is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "N"))
        float mConstN;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Mad"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Mad"); OutToolTip.Add(ret); }
#endif

	
	
};
