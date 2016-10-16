#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSMad.h"


#define LOCTEXT_NAMESPACE "UOSSMad"

UMaterialExpressionOSSMad::UMaterialExpressionOSSMad(const FObjectInitializer& ObjectInitializer)
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

    mConstX = 0.0f;
    mConstM = 1.0f;
    mConstN = 0.0f;

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSMad::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    int32 Arg1 = X.Expression ? X.Compile(Compiler) : Compiler->Constant(mConstX);
    int32 Arg2 = M.Expression ? M.Compile(Compiler) : Compiler->Constant(mConstM);
    int32 Arg3 = N.Expression ? N.Compile(Compiler) : Compiler->Constant(mConstN);

    return Compiler->Add(Compiler->Mul(Arg1, Arg2), Arg3);
}

void UMaterialExpressionOSSMad::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Mad");

    if (!X.Expression || !M.Expression || !N.Expression)
    {
        ret += TEXT("(");
        ret += M.Expression ? TEXT("M,") : FString::Printf(TEXT("%.4g,"), mConstM);
        ret += X.Expression ? TEXT("X,") : FString::Printf(TEXT("%.4g,"), mConstX);
        ret += N.Expression ? TEXT("N)") : FString::Printf(TEXT("%.4g)"), mConstN);
    }

    OutCaptions.Add(ret);
}

