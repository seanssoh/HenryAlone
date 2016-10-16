#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSColorPalette.h"

#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSColorPalette"

UMaterialExpressionOSSColorPalette::UMaterialExpressionOSSColorPalette(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
		FText NAME_Color;
		FText NAME_OSS;
        FConstructorStatics()
            : NAME_Color(LOCTEXT("Color", "Color"))
            , NAME_OSS(LOCTEXT("OSS", "OSS"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;


    ConstA = FLinearColor(0.50f, 0.50f, 0.50f, 1.0f);
    ConstB = FLinearColor(0.50f, 0.50f, 0.50f, 1.0f);
    ConstC = FLinearColor(1.00f, 1.00f, 1.00f, 1.0f);
    ConstD = FLinearColor(0.00f, 0.33f, 0.66f, 0.0f);

    MenuCategories.Add(ConstructorStatics.NAME_Color);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

int32 UMaterialExpressionOSSColorPalette::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if( !X.Expression ) return Compiler->Errorf(TEXT("Missing Color Input"));

    const int32 x =  X.Compile(Compiler);

    const int32 tau = Compiler->Constant(6.28318f);

    const int32 a = Compiler->Constant3(ConstA.R, ConstA.G, ConstA.B);
    const int32 b = Compiler->Constant3(ConstB.R, ConstB.G, ConstB.B);
    const int32 c = Compiler->Constant3(ConstC.R, ConstC.G, ConstC.B);
    const int32 d = Compiler->Constant3(ConstD.R, ConstD.G, ConstD.B);

    //
    // more info here: http://iquilezles.org/www/articles/palettes/palettes.htm
    //
    return Compiler->Add(a, Compiler->Mul(b, Compiler->Cosine(Compiler->Mul(tau,Compiler->Add(Compiler->Mul(c, x), d)))));
}

void UMaterialExpressionOSSColorPalette::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("ColorPalette");
    OutCaptions.Add(ret);
}






