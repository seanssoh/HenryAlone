#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSSmoothstep.h"


#define LOCTEXT_NAMESPACE "UOSSSmoothstep"

UMaterialExpressionOSSSmoothstep::UMaterialExpressionOSSSmoothstep(const FObjectInitializer& ObjectInitializer)
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
    mConstA = 0.0f;
    mConstB = 1.0f;

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSSmoothstep::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    const int32 x = X.Expression ? X.Compile(Compiler) : Compiler->Constant(mConstX);
    const int32 a = A.Expression ? A.Compile(Compiler) : Compiler->Constant(mConstA);
    const int32 b = B.Expression ? B.Compile(Compiler) : Compiler->Constant(mConstB);
    const int32 cte0 = Compiler->Constant(0.0f);
    const int32 cte1 = Compiler->Constant(1.0f);
    const int32 cte2 = Compiler->Constant(2.0f);
    const int32 cte3 = Compiler->Constant(3.0f);

    const int32 y = Compiler->Clamp( Compiler->Div(Compiler->Sub(x, a), Compiler->Sub(b, a)), cte0, cte1 );

    return Compiler->Mul(Compiler->Mul(y, y), Compiler->Sub(cte3, Compiler->Mul(cte2, y)));
}

void UMaterialExpressionOSSSmoothstep::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("Smoothstep");

    if (!A.Expression || !B.Expression || !X.Expression)
    {
        ret += TEXT("(");
        ret += A.Expression ? TEXT("A,") : FString::Printf(TEXT("%.4g,"), mConstA);
        ret += B.Expression ? TEXT("B,") : FString::Printf(TEXT("%.4g,"), mConstB);
        ret += X.Expression ? TEXT("X)") : FString::Printf(TEXT("%.4g)"), mConstX);
    }

    OutCaptions.Add(ret);
}



