// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSDistRing10.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSDistRing10 : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSDistRing10(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P0"))
    FExpressionInput P0;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P1"))
    FExpressionInput P1;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P2"))
    FExpressionInput P2;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P3"))
    FExpressionInput P3;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P4"))
    FExpressionInput P4;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P5"))
    FExpressionInput P5;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P6"))
    FExpressionInput P6;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P7"))
    FExpressionInput P7;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P8"))
    FExpressionInput P8;
    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Segment Point P9"))
    FExpressionInput P9;

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Point X"))
    FExpressionInput X;

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Normal at X"))
    FExpressionInput N;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("DistRing10"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("DistRing10"); OutToolTip.Add(ret); }
#endif
};
