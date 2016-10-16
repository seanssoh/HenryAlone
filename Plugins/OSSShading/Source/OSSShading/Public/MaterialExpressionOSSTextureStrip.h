// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSTextureStrip.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSTextureStrip : public UMaterialExpression
{
	GENERATED_BODY()
	
	
    UMaterialExpressionOSSTextureStrip(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "UV"))
    FExpressionInput UV;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Texture ID"))
    FExpressionInput ID;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Number of textures"))
    FExpressionInput Num;

    UPROPERTY(EditAnywhere, Category = OSSTextureStrip, meta = (OverridingInputProperty = "ID"))
    float ConstID;

    UPROPERTY(EditAnywhere, Category = OSSTextureStrip, meta = (OverridingInputProperty = "Num"))
    float ConstNum;

    UPROPERTY(EditAnywhere, Category = OSSTextureStrip)
    int32 ConstTileOffset;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("TextureStrip"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("TextureStrip"); OutToolTip.Add(ret); }
#endif

	
};
