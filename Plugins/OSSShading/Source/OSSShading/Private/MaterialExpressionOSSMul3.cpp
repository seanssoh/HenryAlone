#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSMul3.h"


#define LOCTEXT_NAMESPACE "UOSSMul3"

UMaterialExpressionOSSMul3::UMaterialExpressionOSSMul3(const FObjectInitializer& ObjectInitializer)
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

    ConstA = 0.0f;
    ConstB = 0.0f;
    ConstC = 0.0f;

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSMul3::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    const int32 ia = A.Expression ? A.Compile(Compiler) : Compiler->Constant(ConstA);
    const int32 ib = B.Expression ? B.Compile(Compiler) : Compiler->Constant(ConstB);
    const int32 ic = C.Expression ? C.Compile(Compiler) : Compiler->Constant(ConstC);

    return Compiler->Mul(Compiler->Mul(ia, ib), ic);
}

void UMaterialExpressionOSSMul3::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Mul");

    if( !A.Expression || !B.Expression || !C.Expression )
    {
        ret += TEXT("(");
        ret += A.Expression ? TEXT("A,") : FString::Printf(TEXT("%.4g,"), ConstA);
        ret += B.Expression ? TEXT("B,") : FString::Printf(TEXT("%.4g,"), ConstB);
        ret += C.Expression ? TEXT("C)") : FString::Printf(TEXT("%.4g)"), ConstC);
    }

    OutCaptions.Add(ret);
}

