#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSSmoothMin.h"


#define LOCTEXT_NAMESPACE "UOSSSmoothMin"

UMaterialExpressionOSSSmoothMin::UMaterialExpressionOSSSmoothMin(const FObjectInitializer& ObjectInitializer)
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
    ConstB = 1.0f;
    ConstK = 0.1f;

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

/*
float smin( float a, float b, float k )
{
    float h = clamp(0.5 + 0.5*(b - a) / k, 0.0, 1.0);
    return mix(b, a, h) - k*h*(1.0 - h);
}
*/
int32 UMaterialExpressionOSSSmoothMin::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    const int32 a = A.Expression ? A.Compile(Compiler) : Compiler->Constant(ConstA);
    const int32 b = B.Expression ? B.Compile(Compiler) : Compiler->Constant(ConstB);
    const int32 k = K.Expression ? K.Compile(Compiler) : Compiler->Constant(ConstK);

    const int32 cte0 = Compiler->Constant(0.0f);
    const int32 cte1 = Compiler->Constant(1.0f);
    const int32 cte2 = Compiler->Constant(0.5f);

    const int32 h = Compiler->Clamp( Compiler->Add(cte2, Compiler->Mul(cte2,Compiler->Div(Compiler->Sub(b, a), k))), cte0, cte1);

    return Compiler->Sub( Compiler->Lerp(a,b,h), Compiler->Mul(Compiler->Mul(k, h),Compiler->Sub(cte1,h)) );
}

void UMaterialExpressionOSSSmoothMin::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("SMin");

    if (!A.Expression || !B.Expression || !K.Expression)
    {
        ret += TEXT("(");
        ret += A.Expression ? TEXT("A,") : FString::Printf(TEXT("%.4g,"), ConstA);
        ret += B.Expression ? TEXT("B,") : FString::Printf(TEXT("%.4g,"), ConstB);
        ret += K.Expression ? TEXT("K)") : FString::Printf(TEXT("%.4g)"), ConstK);
    }

    OutCaptions.Add(ret);
}

