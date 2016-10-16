// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSReflect.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSReflect : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSReflect(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Incident vector"))
        FExpressionInput I;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Surface normal"))
        FExpressionInput N;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Reflect"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Reflect"); OutToolTip.Add(ret); }
#endif

	
	
};
