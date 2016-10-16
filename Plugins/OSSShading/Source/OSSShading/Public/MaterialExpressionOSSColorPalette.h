// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSColorPalette.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionOSSColorPalette : public UMaterialExpression
{
	GENERATED_BODY()
	
    UMaterialExpressionOSSColorPalette(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "true", ToolTip = "Input Parameter"))
    FExpressionInput X;
    
    UPROPERTY(EditAnywhere, Category = OSSColorPalette)
    FLinearColor ConstA;

    UPROPERTY(EditAnywhere, Category = OSSColorPalette)
    FLinearColor ConstB;

    UPROPERTY(EditAnywhere, Category = OSSColorPalette)
    FLinearColor ConstC;

    UPROPERTY(EditAnywhere, Category = OSSColorPalette)
    FLinearColor ConstD;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("ColorPalette"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("ColorPalette"); OutToolTip.Add(ret); }
#endif

	
	
};
