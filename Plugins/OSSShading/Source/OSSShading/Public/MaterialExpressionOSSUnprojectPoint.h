// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSUnprojectPoint.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSUnprojectPoint : public UMaterialExpression
{
	GENERATED_BODY()
	
	
    UMaterialExpressionOSSUnprojectPoint(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "X"))
    FExpressionInput X;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's position"))
    FExpressionInput PrjC;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's U axis"))
    FExpressionInput PrjU;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's V axis"))
    FExpressionInput PrjV;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's W axis"))
    FExpressionInput PrjW;


    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("UnorojectPoint"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("UnorojectPoint"); OutToolTip.Add(ret); }
#endif

	
};
