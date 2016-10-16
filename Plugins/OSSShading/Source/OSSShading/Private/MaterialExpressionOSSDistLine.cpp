#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSDistLine.h"

#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSDistLine"

UMaterialExpressionOSSDistLine::UMaterialExpressionOSSDistLine(const FObjectInitializer& ObjectInitializer)
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

    MenuCategories.Add(ConstructorStatics.NAME_Math);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

int32 UMaterialExpressionOSSDistLine::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if( !A.Expression ) return Compiler->Errorf(TEXT("Missing input A"));
    if( !B.Expression ) return Compiler->Errorf(TEXT("Missing input B"));
    if (!X.Expression)  return Compiler->Errorf(TEXT("Missing input X"));

    const int32 a = A.Compile(Compiler);
    const int32 b = B.Compile(Compiler);
    const int32 x = X.Compile(Compiler);

    /*
    // http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
    float sdLine(vec3 p, vec3 a, vec3 b)
    {
        vec3 pa = p - a, ba = b - a;
        float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
        return length(pa - ba*h);
    }
    */

    const int32 cte0 = Compiler->Constant(0.0f);
    const int32 cte1 = Compiler->Constant(1.0f);
    const int32 pa = Compiler->Sub(x, a);
    const int32 ba = Compiler->Sub( b, a );
    const int32 h = Compiler->Clamp( Compiler->Div(Compiler->Dot(pa, ba), Compiler->Dot(ba, ba)), cte0, cte1 );
    return Compiler->Length( Compiler->Sub(pa, Compiler->Mul(ba,h)) );
}

void UMaterialExpressionOSSDistLine::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("DistLine");
    OutCaptions.Add(ret);
}






