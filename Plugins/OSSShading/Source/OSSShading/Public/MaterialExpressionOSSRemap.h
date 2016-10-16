// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSRemap.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSRemap : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSRemap(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'X' if not specified"))
        FExpressionInput X;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstMinIn' if not specified"))
        FExpressionInput MinIn;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstMaxIn' if not specified"))
        FExpressionInput MaxIn;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstMinOut' if not specified"))
        FExpressionInput MinOut;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstMaxOut' if not specified"))
        FExpressionInput MaxOut;

    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "X"))
        float ConstX;

    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "MinIn"))
        float ConstMinIn;

    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "MaxIn"))
        float ConstMaxIn;

    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "MinOut"))
        float ConstMinOut;

    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "MaxOut"))
        float ConstMaxOut;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Remap"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Remap"); OutToolTip.Add(ret); }
#endif

	
	
};
