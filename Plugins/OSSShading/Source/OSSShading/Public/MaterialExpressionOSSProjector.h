// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSProjector.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSProjector : public UMaterialExpression
{
	GENERATED_BODY()
	
	
    UMaterialExpressionOSSProjector(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's position"))
    FExpressionInput PrjC;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's U axis"))
    FExpressionInput PrjU;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's V axis"))
    FExpressionInput PrjV;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's Scale"))
    FExpressionInput Scale;

    /** only used if X is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSProjector, meta = (OverridingInputProperty = "Scale"))
    float ConstScale;

    UPROPERTY(EditAnywhere, Category = OSSProjector)
    uint32 RemapClampUnit : 1;

    UPROPERTY(EditAnywhere, Category = OSSProjector)
    uint32 Rotate180 : 1;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Projector"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Projector"); OutToolTip.Add(ret); }
#endif

	
};
