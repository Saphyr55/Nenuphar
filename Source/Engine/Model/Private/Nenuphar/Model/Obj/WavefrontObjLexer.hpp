#pragma once

#include "Nenuphar/Common/Common.hpp"
#include <cstddef>
#include <unordered_map>

namespace Nenuphar
{

    struct WavefrontObjToken
    {

        //
        // Definition from https://www.fileformat.info/format/wavefrontobj/egff.htm
        //
        enum class Type
        {
            // Numbers:
            Integer,// Integer number.
            Float,  // Float number.
            Neg,    // Negative number: -x.

            // Vertex data:
            V,    // Geometric vertices. (v)
            VT,   // Texture vertices. (vt)
            VN,   // Vertex normals. (vn)
            VP,   // Parameter space vertices. (vp)
            Slash,// Separator for a face: f v1//n1 v2//n2 ... vn//nn

            // Free-form curve/surface attributes:
            Deg,    // Degree. (deg)
            BMatrix,// Basis matrix. (bmat)
            Step,   // Step size. (step)
            CSType, // Curve or surface type. (cstype)

            // Elements.
            Point,  // Point. (p)
            Line,   // Line. (l)
            Face,   // Face. (f)
            Curve,  // Curve. (curv)
            Curve2D,// 2D curve. (curv2)
            Surface,// Surface. (surf)

            // Free-form curve/surface body statements:
            Param,// Parameter values. (parm)
            Trim, // Outer trimming loop. (trim)
            Hole, // Inner trimming loop. (hole)
            SCRV, // Special curve. (scrv)
            SP,   // Special point. (sp)
            End,  // End statement. (end)

            // Connectivity between free-form surfaces:
            Connect,// Connect. (con)

            // Grouping:
            Group, // Group name, (g)
            SGroup,// Smoothing group. (s)
            MGroup,// Merging group. (mg)
            Object,// Object name. (o)

            // Display/render attributes:
            Bevel,      // Bevel interpolation
            C_interp,   // Color interpolation
            D_interp,   // Dissolve interpolation
            LoD,        // Level of detail
            USEMLT,     // Material name: usemtl materialname
            MaterialLib,// Material library: mtllib materiallibname.mtl
            ShadowObj,  //	Shadow casting
            TraceObj,   // Ray tracing
            Ctech,      // Curve approximation technique
            Stech,      // Surface approximation technique

            // Basic token type for the lexer.
            NewLine,   // New line (\n)
            Eos,       // End of file.
            Identifier,// Any identifier.
            Dot        // Dot. (.)
        };

        String Text;
        Type Kind;
    };

    
    class WavefrontObjLexer
    {
    public:
        std::vector<WavefrontObjToken> Scan();

    public:
        WavefrontObjLexer(StringView source);
        
    private:
        bool MatchWith(const char& c);
        void SkipComment();
        void NextToken();
        Char Peek();
        Char GetAndAdvance();
        Int GetPosAndNext();
        bool IsAtEnd();

        void AddToken(StringView, WavefrontObjToken::Type kind);
        void AddToken(WavefrontObjToken::Type kind);
        void AddDefaultToken(const char& current);
        void AddIdentifierToken();
        void AddNumberToken();

        void Report(StringView msg);

    private:
        String m_source;
        Int m_position = 0;
        Int m_start = 0;
        Int m_line = 1;
        Int m_col = 1;
        std::vector<WavefrontObjToken> m_tokens;
        static std::unordered_map<std::string, WavefrontObjToken::Type> Keywords;
    };

}
