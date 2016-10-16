#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSRemap.h"

#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSRemap"

UMaterialExpressionOSSRemap::UMaterialExpressionOSSRemap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
		FText NAME_Math;
		FText NAME_OSS;
        FConstructorStatics()
            : NAME_Math(LOCTEXT("Math", "Math"))
            , NAME_OSS(LOCTEXT("OSS", "OSS"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;

    ConstMinIn = 0.0f;
    ConstMaxIn = 1.0f;
    ConstMinOut = 0.0f;
    ConstMaxOut = 1.0f;
    ConstX = 0.0f;

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

int32 UMaterialExpressionOSSRemap::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    const int32 x   =      X.Expression ?      X.Compile(Compiler) : Compiler->Constant(ConstX);
    const int32 mii =  MinIn.Expression ?  MinIn.Compile(Compiler) : Compiler->Constant(ConstMinIn);
    const int32 mai =  MaxIn.Expression ?  MaxIn.Compile(Compiler) : Compiler->Constant(ConstMaxIn);
    const int32 mio = MinOut.Expression ? MinOut.Compile(Compiler) : Compiler->Constant(ConstMinOut);
    const int32 mao = MaxOut.Expression ? MaxOut.Compile(Compiler) : Compiler->Constant(ConstMaxOut);

    const int32 cte0 = Compiler->Constant(0.0f);
    const int32 cte1 = Compiler->Constant(1.0f);

    const int32 y = Compiler->Clamp(Compiler->Div(Compiler->Sub(x, mii), Compiler->Sub(mai, mii)), cte0, cte1);

    return Compiler->Add(mio, Compiler->Mul(Compiler->Sub(mao, mio), y));
}

void UMaterialExpressionOSSRemap::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Remap");

    if (!X.Expression || !MinIn.Expression || !MaxIn.Expression || !MinOut.Expression || !MaxOut.Expression)
    {
        ret += TEXT("(");
        ret +=      X.Expression ? TEXT("X,")      : FString::Printf(TEXT("%.4g,"), ConstX);
        ret +=  MinIn.Expression ? TEXT("MinIn,")  : FString::Printf(TEXT("%.4g,"), ConstMinIn);
        ret +=  MaxIn.Expression ? TEXT("MaxIn,")  : FString::Printf(TEXT("%.4g,"), ConstMaxIn);
        ret += MinOut.Expression ? TEXT("MinOut)") : FString::Printf(TEXT("%.4g)"), ConstMinOut);
        ret += MaxOut.Expression ? TEXT("MaxOut)") : FString::Printf(TEXT("%.4g)"), ConstMaxOut);
    }

    OutCaptions.Add(ret);
}






