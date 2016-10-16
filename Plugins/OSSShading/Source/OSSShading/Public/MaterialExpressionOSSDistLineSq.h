// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSDistLineSq.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSDistLineSq : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSDistLineSq(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Segment Point A"))
    FExpressionInput A;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Segment Point B"))
    FExpressionInput B;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Point X"))
   FExpressionInput X;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("DistLineSq"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("DistLineSq"); OutToolTip.Add(ret); }
#endif
};
