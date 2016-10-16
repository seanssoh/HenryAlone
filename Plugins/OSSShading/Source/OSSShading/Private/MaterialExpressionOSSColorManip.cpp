#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSColorManip.h"

#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSColorManip"

UMaterialExpressionOSSColorManip::UMaterialExpressionOSSColorManip(const FObjectInitializer& ObjectInitializer)
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


    ConstDesat = 0.0f;
    ConstGamma = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ConstTint  = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ConstBias  = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);

    MenuCategories.Add(ConstructorStatics.NAME_Color);
    MenuCategories.Add(ConstructorStatics.NAME_OSS);
}

#if 0
int32 rgb2hsv_Compile( class FMaterialCompiler* Compiler, int32 col )
{
    // vec3 hsv2rgb(in vec3 c)
    // {
    //     vec3 rgb = clamp(abs(mod(c.x*6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);
    //     return c.z * mix(vec3(1.0), rgb, c.y);
    // }

    const int32 x = Compiler->ComponentMask( col, true,  false, false, false );
    const int32 y = Compiler->ComponentMask( col, false, true,  false, false );
    const int32 z = Compiler->ComponentMask( col, false, false, true,  false );

    const int32 k1 = Compiler->Constant3( 0.0f, 4.0f, 2.0f );
    const int32 k2 = Compiler->Constant3( 1.0f, 1.0f, 1.0f );

    const int32 cte0 = Compiler->Constant( 0.0f );
    const int32 cte1 = Compiler->Constant( 1.0f );
    const int32 cte3 = Compiler->Constant( 3.0f );
    const int32 cte6 = Compiler->Constant( 6.0f );

    const int32 rgb = Compiler->Clamp( Compiler->Sub( Compiler->Abs( Compiler->Sub( Compiler->Fmod( Compiler->Add( Compiler->Mul(x, cte6), k1), cte6), cte3)), cte1), cte0, cte1);

    return Compiler->Mul( z, Compiler->Lerp( k2, rgb, y) );

}

int32 hsv2rgb_Compile(class FMaterialCompiler* Compiler, int32 col)
{
    // vec3 rgb2hsv(in vec3 c)
    // {
    //     vec4 q = mix(vec4(c.zy, -6.0, 4.0), vec4(c.yz, 0.0, -2.0), step(c.z, c.y));
    //     vec4 r = mix(vec4(q.xyw, c.x), vec4(c.x, q.yzx), step(q.x, c.x));
    //     float d = r.x - min(r.w, r.y);
    //     return vec3(abs(r.z + (r.w - r.y) / (d + 1.0e-10)) / 6.0, d / (r.x + 1.0e-10), r.x);
    // }

    const int32 cx = Compiler->ComponentMask(col, true, false, false, false);
    const int32 cy = Compiler->ComponentMask(col, false, true, false, false);
    const int32 cz = Compiler->ComponentMask(col, false, false, true, false);

    const int32 ctn6d0 = Compiler->Constant( -6.0f );
    const int32 ctn2d0 = Compiler->Constant( -2.0f );
    const int32 ctp0d0 = Compiler->Constant(  0.0f );
    const int32 ctp4d0 = Compiler->Constant(  4.0f );
    const int32 ctp6d0 = Compiler->Constant(  6.0f);
    const int32 ctpeps = Compiler->Constant( 1.0e-10);

    const int32 q1 = Compiler->AppendVector( Compiler->AppendVector(Compiler->AppendVector(cz, cy), ctn6d0), ctp4d0 );
    const int32 q2 = Compiler->AppendVector( Compiler->AppendVector(Compiler->AppendVector(cy, cz), ctp0d0), ctn2d0 );

    const int32 q = Compiler->If( cz, cy, q1, q1, q2, ctp0d0 );

    const int32 qx = Compiler->ComponentMask( q, true,  false, false, false );
    const int32 qy = Compiler->ComponentMask( q, false, true,  false, false );
    const int32 qz = Compiler->ComponentMask( q, false, false, true,  false );
    const int32 qw = Compiler->ComponentMask( q, false, false, false, true  );

    const int32 r1 = Compiler->AppendVector( Compiler->AppendVector(Compiler->AppendVector(qx,qy), qw), cx );
    const int32 r2 = Compiler->AppendVector( Compiler->AppendVector(Compiler->AppendVector(cx,qy), qz), qx );

    const int32 r = Compiler->If( qx, cx, r1, r1, r2, ctp0d0 );

    const int32 rx = Compiler->ComponentMask(r, true, false, false, false);
    const int32 ry = Compiler->ComponentMask(r, false, true, false, false);
    const int32 rz = Compiler->ComponentMask(r, false, false, true, false);
    const int32 rw = Compiler->ComponentMask(r, false, false, false, true);

    const int32 d = Compiler->Sub(rx, Compiler->Min(rw, ry));

    const int32 h = Compiler->Div(Compiler->Abs( Compiler->Div(rz + (rw - ry), Compiler->Add(d, ctpeps))), ctp6d0);
    const int32 s = Compiler->Div(d, Compiler->Add(rx, ctpeps));
    const int32 v = rx;

    return Compiler->AppendVector(h, Compiler->AppendVector(s,v));
}
#endif

int32 desat_Compile(class FMaterialCompiler* Compiler, int32 col, int amount )
{
    const int32 k = Compiler->Constant3(0.3333f, 0.3333f, 0.3333f);
    const int32 g = Compiler->Dot( col, k );
    const int32 gre = Compiler->AppendVector(Compiler->AppendVector(g,g),g);
    return Compiler->Lerp( col, gre, amount );
}

int32 UMaterialExpressionOSSColorManip::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if (!ColorIn.Expression) return Compiler->Errorf(TEXT("Missing Color Input"));

    const int32 col =  ColorIn.Compile(Compiler);

    const int32 desat = Desat.Expression ? Desat.Compile(Compiler) : Compiler->Constant(  ConstDesat );
    const int32 gamma = Gamma.Expression ? Gamma.Compile(Compiler) : Compiler->Constant3( ConstGamma.R, ConstGamma.G, ConstGamma.B );
    const int32 tint  = Tint.Expression  ? Tint.Compile( Compiler) : Compiler->Constant3( ConstTint.R,  ConstTint.G,  ConstTint.B  );
    const int32 bias  = Bias.Expression  ? Bias.Compile( Compiler) : Compiler->Constant3( ConstBias.R,  ConstBias.G,  ConstBias.B  );

    const int32 a = desat_Compile( Compiler, col, desat );

    return Compiler->Add(bias, Compiler->Mul(Compiler->Power(a, gamma), tint));
}

void UMaterialExpressionOSSColorManip::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("ColorManip");
    OutCaptions.Add(ret);
}






