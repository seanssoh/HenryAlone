// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSOccProxy.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSOccProxy : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSOccProxy(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Wire from a blueprint"))
    FExpressionInput ProxyPosRad;

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Wire from a blueprint"))
    FExpressionInput ProxyVis;

    //UPROPERTY(meta = (RequiredInput = "true", ToolTip = "World Space Position"))
    //FExpressionInput WorldSpacePos;

    //UPROPERTY(meta = (RequiredInput = "true", ToolTip = "World Space Normal"))
    //FExpressionInput WorldSpaceNor;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;


#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Occlusion Proxy"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Occlusion Proxy"); OutToolTip.Add(ret); }
#endif

	
	
};
