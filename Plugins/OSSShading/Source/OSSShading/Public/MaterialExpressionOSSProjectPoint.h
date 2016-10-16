// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSProjectPoint.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSProjectPoint : public UMaterialExpression
{
	GENERATED_BODY()
	
	
    UMaterialExpressionOSSProjectPoint(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's position"))
    FExpressionInput PrjC;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's U axis"))
    FExpressionInput PrjU;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's V axis"))
    FExpressionInput PrjV;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Projector's W axis"))
    FExpressionInput PrjW;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Point to project"))
    FExpressionInput X;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("ProjectPoint"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("ProjectPoint"); OutToolTip.Add(ret); }
#endif

	
};
