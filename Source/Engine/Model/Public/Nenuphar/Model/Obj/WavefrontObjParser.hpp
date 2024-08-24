#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Model/Obj/WavefrontObjLexer.hpp"
#include "Nenuphar/Model/Obj/WavefrontObjFile.hpp"
#include "Nenuphar/Model/Obj/WavefrontObjStmt.hpp"

#include <vector>

namespace Nenuphar
{
       
    class WavefrontObjExpr
    {
    public:
        virtual ~WavefrontObjExpr() = default;
    };
    
    class WavefrontObjParser
    {
    public:

        /**
         * @brief Parse a the content string to a Wavefront Obj File 
         * to represent the data.   
         * 
         * @param source
         * @return WavefrontObjFile 
         */
        WavefrontObjFile Parse(std::string_view source);

        /**
         * @brief Construct a new Wavefront Obj Parser object.
         * 
         */
        WavefrontObjParser();

    private:
        /**
         * @brief 
         * 
         * @return UniquePtr<WavefrontObjStmt> 
         */
        UniquePtr<WavefrontObjStmt> ParseVertex(); 
        
    private:
        const WavefrontObjToken& Consume(WavefrontObjToken::Type kind, String message); 

        Bool MatchWith(WavefrontObjToken::Type kind);

        Bool IsAtEnd();

        Bool Check(WavefrontObjToken::Type kind);

        const WavefrontObjToken& Peek();
            
        const WavefrontObjToken& Next();

    private:
        int m_position;
        WavefrontObjTokenVector m_tokens;
    };

}