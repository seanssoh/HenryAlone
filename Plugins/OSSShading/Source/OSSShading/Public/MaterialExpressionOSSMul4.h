// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MaterialCompiler.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionOSSMul4.generated.h"

/**
*
*/
UCLASS()
class UMaterialExpressionOSSMul4 : public UMaterialExpression
{
    GENERATED_BODY()


    UMaterialExpressionOSSMul4(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstX' if not specified"))
        FExpressionInput A;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstM' if not specified"))
        FExpressionInput B;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstN' if not specified"))
        FExpressionInput C;

    UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstN' if not specified"))
        FExpressionInput D;

    /** only used if X is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "A"))
        float ConstA;

    /** only used if M is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "B"))
        float ConstB;

    /** only used if N is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "C"))
        float ConstC;

    /** only used if N is not hooked up */
    UPROPERTY(EditAnywhere, Category = OSSRemap, meta = (OverridingInputProperty = "D"))
        float ConstD;

    // Begin UMaterialExpression Interface
    virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;

#if WITH_EDITOR
    virtual FString GetDescription() const override { FString ret = TEXT("Mul4"); return ret; }
    virtual void GetExpressionToolTip(TArray<FString>& OutToolTip) override { FString ret = TEXT("Mul4"); OutToolTip.Add(ret); }
#endif



};