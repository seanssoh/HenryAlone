#include "OSSShadingPrivatePCH.h"

#include "MaterialExpressionOSSDistRing10.h"

#define LOCTEXT_NAMESPACE "UMaterialExpressionOSSDistRing10"

UMaterialExpressionOSSDistRing10::UMaterialExpressionOSSDistRing10(const FObjectInitializer& ObjectInitializer)
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


// Distance estimation to smooth PN-tesselated segment ring
// More info here:   https://www.shadertoy.com/view/MlsGWS

static int32 sdLine(class FMaterialCompiler* com, const int32 x, const int32 a, const int32 b)
{
    const int32 cte0 = com->Constant(0.0f);
    const int32 cte1 = com->Constant(1.0f);
    const int32 pa = com->Sub(x, a);
    const int32 ba = com->Sub(b, a);
    const int32 h = com->Clamp(com->Div(com->Dot(pa, ba), com->Dot(ba, ba)), cte0, cte1);
    return com->Length(com->Sub(pa, com->Mul(ba, h)));
}

static int32 normalize(class FMaterialCompiler* com, const int32 v)
{
//  return v / sqrt(dot(v,v));
    return com->Div(v, com->SquareRoot(com->Dot(v, v)));
}

static int32 project(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 n)
{
//  return a + n*dot(n,b-a)/dot(n,n);
    return com->Add(a, com->Div(com->Mul(n, com->Dot(n, com->Sub(b, a))), com->Dot(n, n)));
}

/*
vec2 cubic_0d000(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return a; }
vec2 cubic_0d125(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return (a*343.0 + b*147.0 + c*21.0 + d) / 512.0; }
vec2 cubic_0d250( in vec2 a, in vec2 b, in vec2 c, in vec2 d ) { return (a*27.0 + b*27.0 + c*9.0 + d)/64.0; }
vec2 cubic_0d375( in vec2 a, in vec2 b, in vec2 c, in vec2 d ) { return (a*125.0 + b*225.0 + c*135.0 + d*27.0)/512.0; }
vec2 cubic_0d500(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return (a + b*3.0 + c*3.0 + d) / 8.0; }
vec2 cubic_0d625(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return (a*27.0 + b*135.0 + c*225.0 + d*125.0) / 512.0; }
vec2 cubic_0d750(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return (a + b*9.0 + c*27.0 + d*27.0) / 64.0; }
vec2 cubic_0d875(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return (a + b*21.0 + c*147.0 + d*343.0) / 512.0; }
vec2 cubic_1d000(in vec2 a, in vec2 b, in vec2 c, in vec2 d) { return d; }
*/

static int32 cubic_0d000(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { return a; }
//static int32 cubic_0d125(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { return (a*343.0 + b*147.0 + c*21.0 + d) / 512.0; }
static int32 cubic_0d250(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) {
    const int32 ct27 = com->Constant(27.0f);
    const int32 ct09 = com->Constant(9.0f);
    const int32 ct64 = com->Constant(64.0f);
    return com->Div( com->Add(com->Add(com->Mul(a, ct27), com->Mul(b, ct27)), com->Add(com->Mul(c, ct09), d)), ct64);
}
//static int32 cubic_0d375(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { return (a*125.0 + b*225.0 + c*135.0 + d*27.0) / 512.0; }
static int32 cubic_0d500(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { 
    const int32 ct03 = com->Constant(3.0f);
    const int32 ct08 = com->Constant(8.0f);
    return com->Div(com->Add(a, com->Add(com->Mul(b, ct03), com->Add(com->Mul(c, ct03), d))), ct08);
}
//static int32 cubic_0d625(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { return (a*27.0 + b*135.0 + c*225.0 + d*125.0) / 512.0; }
static int32 cubic_0d750(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) {
    const int32 ct27 = com->Constant(27.0f);
    const int32 ct09 = com->Constant(9.0f);
    const int32 ct64 = com->Constant(64.0f);
    return com->Div(com->Add(com->Add(a, com->Mul(b, ct09)), com->Add(com->Mul(c, ct27), com->Mul(d,ct27))), ct64);
}
//static int32 cubic_0d875(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { return (a + b*21.0 + c*147.0 + d*343.0) / 512.0; }
static int32 cubic_1d000(class FMaterialCompiler* com, const int32 a, const int32 b, const int32 c, const int32 d) { return d; }


static int32 sdSegment_2(class FMaterialCompiler* com, const int32 p, const int32 a, const int32 d, const int32 na, const int32 nd)
{
#if 0
    return sdLine( com, p, a, d);
#endif

#if 1
    const int32 ct2d0 = com->Constant(2.0f);
    const int32 ct3d0 = com->Constant(3.0f);
    const int32 ct8d0 = com->Constant(8.0f);

    // secondary points
    // vec2 b = (a*2.0 + d) / 3.0; b = a + na*dot(na, b - a) / dot(na, na);
    // vec2 c = (d*2.0 + a) / 3.0; c = d + nd*dot(nd, c - d) / dot(nd, nd);
    int32 b = com->Div( com->Add(com->Mul(a, ct2d0), d), ct3d0); b = project(com, a, b, na);
    int32 c = com->Div( com->Add(com->Mul(d, ct2d0), a), ct3d0); c = project(com, d, c, nd);

    // middle point
    // vec2 k = (a + b*3.0 + c*3.0 + d) / 8.0;
    const int32 k = com->Div(com->Add(a, com->Add(d, com->Add(com->Mul(b, ct3d0), com->Mul(c, ct3d0)))), ct8d0);

    return com->Min(sdLine(com, p, a, k), sdLine(com, p, k, d));
#endif

#if 0
    const int32 ct2d0 = com->Constant(2.0f);
    const int32 ct3d0 = com->Constant(3.0f);
    const int32 ct8d0 = com->Constant(8.0f);

    // secondary points
    // vec2 b = (a*2.0 + d) / 3.0; b = a + na*dot(na, b - a) / dot(na, na);
    // vec2 c = (d*2.0 + a) / 3.0; c = d + nd*dot(nd, c - d) / dot(nd, nd);
    int32 b = com->Div(com->Add(com->Mul(a, ct2d0), d), ct3d0); b = project(com, a, b, na);
    int32 c = com->Div(com->Add(com->Mul(d, ct2d0), a), ct3d0); c = project(com, d, c, nd);

    // middle points
    //vec2 k0 = cubic_0d000(a, b, c, d);
    //vec2 k1 = cubic_0d250(a, b, c, d);
    //vec2 k2 = cubic_0d500(a, b, c, d);
    //vec2 k3 = cubic_0d750(a, b, c, d);
    //vec2 k4 = cubic_1d000(a, b, c, d);
    const int32 k0 = cubic_0d000(com, a, b, c, d);
    const int32 k1 = cubic_0d250(com, a, b, c, d);
    const int32 k2 = cubic_0d500(com, a, b, c, d);
    const int32 k3 = cubic_0d750(com, a, b, c, d);
    const int32 k4 = cubic_1d000(com, a, b, c, d);

    return com->Min(com->Min(sdLine(com, p, k0, k1), sdLine(com, p, k1, k2)), com->Min(sdLine(com, p, k2, k3), sdLine(com, p, k3, k4)));
#endif

}

int32 UMaterialExpressionOSSDistRing10::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, int32 MultiplexIndex)
{
    if( !P0.Expression ) return Compiler->Errorf(TEXT("Missing input P0"));
    if( !P1.Expression ) return Compiler->Errorf(TEXT("Missing input P1"));
    if( !P2.Expression ) return Compiler->Errorf(TEXT("Missing input P2"));
    if( !P3.Expression ) return Compiler->Errorf(TEXT("Missing input P3"));
    if( !P4.Expression ) return Compiler->Errorf(TEXT("Missing input P4"));
    if( !P5.Expression ) return Compiler->Errorf(TEXT("Missing input P5"));
    if( !P6.Expression ) return Compiler->Errorf(TEXT("Missing input P6"));
    if( !P7.Expression ) return Compiler->Errorf(TEXT("Missing input P7"));
    if( !P8.Expression ) return Compiler->Errorf(TEXT("Missing input P8"));
    if( !P9.Expression ) return Compiler->Errorf(TEXT("Missing input P9"));
    if( ! X.Expression)  return Compiler->Errorf(TEXT("Missing input X" ));
    if (! N.Expression)  return Compiler->Errorf(TEXT("Missing input N"));

    const int32 e = Compiler->Constant(0.0001f);
  
    const int32 p = X.Compile(Compiler);
    const int32 n = N.Compile(Compiler);

    const int32 ep = Compiler->Mul( n, e );

    const int32 p0 = Compiler->Add( P0.Compile(Compiler), ep );
    const int32 p1 = Compiler->Add( P1.Compile(Compiler), ep );
    const int32 p2 = Compiler->Add( P2.Compile(Compiler), ep );
    const int32 p3 = Compiler->Add( P3.Compile(Compiler), ep );
    const int32 p4 = Compiler->Add( P4.Compile(Compiler), ep );
    const int32 p5 = Compiler->Add( P5.Compile(Compiler), ep );
    const int32 p6 = Compiler->Add( P6.Compile(Compiler), ep );
    const int32 p7 = Compiler->Add( P7.Compile(Compiler), ep );
    const int32 p8 = Compiler->Add( P8.Compile(Compiler), ep );
    const int32 p9 = Compiler->Add( P9.Compile(Compiler), ep );


    const int32 n01 = normalize( Compiler, Compiler->Sub(p1, p0) );
    const int32 n12 = normalize( Compiler, Compiler->Sub(p2, p1) );
    const int32 n23 = normalize( Compiler, Compiler->Sub(p3, p2) );
    const int32 n34 = normalize( Compiler, Compiler->Sub(p4, p3) );
    const int32 n45 = normalize( Compiler, Compiler->Sub(p5, p4) );
    const int32 n56 = normalize( Compiler, Compiler->Sub(p6, p5) );
    const int32 n67 = normalize( Compiler, Compiler->Sub(p7, p6) );
    const int32 n78 = normalize( Compiler, Compiler->Sub(p8, p7) );
    const int32 n89 = normalize( Compiler, Compiler->Sub(p9, p8) );
    const int32 n90 = normalize( Compiler, Compiler->Sub(p0, p9) );

    const int32 t0 = Compiler->Add( n90, n01 );
    const int32 t1 = Compiler->Add( n01, n12 );
    const int32 t2 = Compiler->Add( n12, n23 );
    const int32 t3 = Compiler->Add( n23, n34 );
    const int32 t4 = Compiler->Add( n34, n45 );
    const int32 t5 = Compiler->Add( n45, n56 );
    const int32 t6 = Compiler->Add( n56, n67 );
    const int32 t7 = Compiler->Add( n67, n78 );
    const int32 t8 = Compiler->Add( n78, n89 );
    const int32 t9 = Compiler->Add( n89, n90 );

    const int32 d0 = sdSegment_2( Compiler, p, p0, p1, t0, t1 );
    const int32 d1 = sdSegment_2( Compiler, p, p1, p2, t1, t2 );
    const int32 d2 = sdSegment_2( Compiler, p, p2, p3, t2, t3 );
    const int32 d3 = sdSegment_2( Compiler, p, p3, p4, t3, t4 );
    const int32 d4 = sdSegment_2( Compiler, p, p4, p5, t4, t5 );
    const int32 d5 = sdSegment_2( Compiler, p, p5, p6, t5, t6 );
    const int32 d6 = sdSegment_2( Compiler, p, p6, p7, t6, t7 );
    const int32 d7 = sdSegment_2( Compiler, p, p7, p8, t7, t8 );
    const int32 d8 = sdSegment_2( Compiler, p, p8, p9, t8, t9 );
    const int32 d9 = sdSegment_2( Compiler, p, p9, p0, t9, t0 );

    return Compiler->Min(d0, Compiler->Min(d1, Compiler->Min(d2, Compiler->Min(d3, Compiler->Min(d4, Compiler->Min(d5, Compiler->Min(d6, Compiler->Min(d7, Compiler->Min(d8,d9)))))))));
}

void UMaterialExpressionOSSDistRing10::GetCaption(TArray<FString>& OutCaptions) const
{
    FString ret = TEXT("DistRing10");
    OutCaptions.Add(ret);
}






