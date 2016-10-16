#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSOccProxy.h"


#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSOccProxy"

UMaterialExpressionOSSOccProxy::UMaterialExpressionOSSOccProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
		FText NAME_OSS;
        FConstructorStatics()
            : NAME_OSS(LOCTEXT("OSS", "OSS"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;

    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}


int32 UMaterialExpressionOSSOccProxy::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!ProxyPosRad.Expression)  return Compiler->Errorf(TEXT("Missing Proxy Position/Center"));
    if (!ProxyVis.Expression)  return Compiler->Errorf(TEXT("Missing Proxy Visibility"));

    const int32 nor = Compiler->PixelNormalWS();

    const int32 aInp = ProxyPosRad.Compile(Compiler);
    const int32 aVis = ProxyVis.Compile(Compiler);
    const int32 aCen = Compiler->ComponentMask( aInp, true,  true,  true,  false );
    const int32 aRad = Compiler->ComponentMask( aInp, false, false, false, true  );
    const int32 aPos = Compiler->WorldPosition( WPT_Default );
    const int32 aNor = Compiler->Div( nor, Compiler->Length(nor) );

    const int32 cp0d0 = Compiler->Constant(0.0f);
    const int32 cp0d5 = Compiler->Constant(0.5f);
    //const int32 cn1d0 = Compiler->Constant(-1.0f);
    const int32 cp1d0 = Compiler->Constant(1.0f);
    const int32 cp2d0 = Compiler->Constant(2.0f);
    const int32 cp3d0 = Compiler->Constant(3.0f);
    const int32 cp4d0 = Compiler->Constant(4.0f);

    const int32 d = Compiler->Sub(aCen, aPos);
    const int32 l = Compiler->Length( d );
    const int32 a = Compiler->Mul( aRad, cp0d5 );
    const int32 b = Compiler->Mul( aRad, cp4d0 );
    const int32 c = Compiler->Div( Compiler->Dot(aNor, d), l );

    const int32 x = Compiler->Clamp( Compiler->Div( Compiler->Sub(l,a), Compiler->Sub(b,a)), cp0d0, cp1d0 );

    const int32 o = Compiler->Mul( Compiler->Mul(x,x), Compiler->Sub(cp3d0, Compiler->Mul(cp2d0,x)) );

    const int32 g = Compiler->Clamp(c, cp0d0, cp1d0);
    const int32 f = Compiler->Sub(cp1d0, Compiler->Mul( Compiler->Sub(cp1d0,o), g ) );


    //const int32 f = Compiler->Lerp( o, cp1d0, Compiler->Clamp(c, cn1d0, cp1d0));

    return Compiler->Lerp( cp1d0, f, aVis);
}

void UMaterialExpressionOSSOccProxy::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("OcclusionProxy"));
}



